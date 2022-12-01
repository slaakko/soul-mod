// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.bound.node;
import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.function.group.symbol;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.operation.repository;
import otava.symbols.symbol.table;
import otava.symbols.conversion.table;
import otava.symbols.templates;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.argument.conversion.table;
import otava.symbols.function.templates;
import util.unicode;

namespace otava::symbols {

struct ArgumentMatch
{
    ArgumentMatch();
    FunctionSymbol* conversionFun;
    ConversionKind conversionKind;
    int32_t distance;
    OperationFlags preConversionFlags;
    OperationFlags postConversionFlags;
};

int32_t ArgumentConversionValue(const ArgumentMatch& match)
{
    int32_t argumentConversionValue = 0;
    if (match.conversionFun)
    {
        argumentConversionValue = 100;
        if (match.conversionKind == ConversionKind::explicitConversion)
        {
            argumentConversionValue += 10;
        }
        argumentConversionValue += match.distance;
    }
    return argumentConversionValue;
}

struct FunctionMatch
{
    FunctionMatch(FunctionSymbol* function_);
    FunctionSymbol* function;
    std::vector<ArgumentMatch> argumentMatches;
    int numConversions;
    int numQualifyingConversions;
    std::map<TemplateParameterSymbol*, TypeSymbol*> templateParameterMap;
};

ArgumentMatch::ArgumentMatch() : 
    conversionFun(nullptr), 
    conversionKind(ConversionKind::implicitConversion), 
    distance(0), 
    preConversionFlags(OperationFlags::none),
    postConversionFlags(OperationFlags::none)
{
}

struct BetterArgumentMatch
{
    bool operator()(const ArgumentMatch& left, const ArgumentMatch& right) const;
};

bool BetterArgumentMatch::operator()(const ArgumentMatch& left, const ArgumentMatch& right) const
{
    if (left.conversionFun == nullptr && right.conversionFun != nullptr) return true;
    if (right.conversionFun == nullptr && left.conversionFun != nullptr) return false;
    if (left.conversionKind == ConversionKind::implicitConversion && right.conversionKind == ConversionKind::explicitConversion) return true;
    if (left.conversionKind == ConversionKind::explicitConversion && right.conversionKind == ConversionKind::implicitConversion) return false;
    if (left.distance < right.distance) return true;
    if (left.distance > right.distance) return false;
    return false;
}

FunctionMatch::FunctionMatch(FunctionSymbol* function_) : function(function_), numConversions(0), numQualifyingConversions(0)
{
}

struct BetterFunctionMatch
{
    bool operator()(const FunctionMatch& left, const FunctionMatch& right) const;
};

bool BetterFunctionMatch::operator()(const FunctionMatch& left, const FunctionMatch& right) const
{
    BetterArgumentMatch betterArgumentMatch;
    int leftBetterArgumentMatches = 0;
    int rightBetterArgumentMatches = 0;
    int n = std::max(int(left.argumentMatches.size()), int(right.argumentMatches.size()));
    for (int i = 0; i < n; ++i)
    {
        ArgumentMatch leftMatch;
        if (i < int(left.argumentMatches.size()))
        {
            leftMatch = left.argumentMatches[i];
        }
        ArgumentMatch rightMatch;
        if (i < int(right.argumentMatches.size()))
        {
            rightMatch = right.argumentMatches[i];
        }
        if (betterArgumentMatch(leftMatch, rightMatch))
        {
            ++leftBetterArgumentMatches;
        }
        else if (betterArgumentMatch(rightMatch, leftMatch))
        {
            ++rightBetterArgumentMatches;
        }
    }
    if (leftBetterArgumentMatches > rightBetterArgumentMatches)
    {
        return true;
    }
    if (rightBetterArgumentMatches > leftBetterArgumentMatches)
    {
        return false;
    }
    int leftValue = 0;
    int rightValue = 0;
    for (int i = 0; i < n; ++i)
    {
        ArgumentMatch leftMatch;
        if (i < int(left.argumentMatches.size()))
        {
            leftMatch = left.argumentMatches[i];
        }
        ArgumentMatch rightMatch;
        if (i < int(right.argumentMatches.size()))
        {
            rightMatch = right.argumentMatches[i];
        }
        leftValue += ArgumentConversionValue(leftMatch);
        rightValue += ArgumentConversionValue(rightMatch);
    }
    if (leftValue < rightValue)
    {
        return true;
    }
    if (leftValue > rightValue)
    {
        return false;
    }
    if (left.numConversions < right.numConversions)
    {
        return true;
    }
    if (left.numConversions > right.numConversions)
    {
        return false;
    }
    if (left.numQualifyingConversions < right.numQualifyingConversions)
    {
        return true;
    }
    if (left.numQualifyingConversions > right.numQualifyingConversions)
    {
        return false;
    }
    if (left.function->IsFunctionDefinitionSymbol() && !right.function->IsFunctionDefinitionSymbol())
    {
        return true;
    }
    if (!left.function->IsFunctionDefinitionSymbol() && right.function->IsFunctionDefinitionSymbol())
    {
        return false;
    }
    if (left.function->IsSpecialization() && !right.function->IsSpecialization())
    {
        return true;
    }
    if (!left.function->IsSpecialization() && right.function->IsSpecialization())
    {
        return false;
    }
    return false;
}

BoundExpressionNode* MakeLvalueExpression(BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (arg->IsLvalueExpression()) return arg;
    BoundVariableNode* backingStore = nullptr;
    if (context->GetBoundFunction())
    {
        backingStore = new BoundVariableNode(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(arg->GetType()), sourcePos);
    }
    return new BoundTemporaryNode(arg, backingStore, sourcePos);
}

std::unique_ptr<BoundFunctionCallNode> CreateBoundFunctionCall(const FunctionMatch& functionMatch, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall(new BoundFunctionCallNode(functionMatch.function, sourcePos));
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i].release();
        if (i == 0 && !functionMatch.function->IsMemberFunction() && 
            (functionMatch.function->Name() == U"@constructor" || functionMatch.function->Name() == U"operator=" || functionMatch.function->Name() == U"operator->"))
        {
            if (arg->IsBoundAddressOfNode())
            {
                BoundAddressOfNode* addrOfNode = static_cast<BoundAddressOfNode*>(arg);
                BoundExpressionNode* subject = addrOfNode->ReleaseSubject();
                args[i].reset(subject);
                arg = args[i].release();
            }
        }
        const ArgumentMatch& argumentMatch = functionMatch.argumentMatches[i];
        if (argumentMatch.preConversionFlags == OperationFlags::addr)
        {
            arg = new BoundAddressOfNode(MakeLvalueExpression(arg, sourcePos, context), sourcePos);
        }
        else if (argumentMatch.preConversionFlags == OperationFlags::deref)
        {
            arg = new BoundDereferenceNode(arg, sourcePos);
        }
        if (argumentMatch.conversionFun)
        {
            arg = new BoundConversionNode(arg, argumentMatch.conversionFun, sourcePos);
        }
        if (argumentMatch.postConversionFlags == OperationFlags::addr)
        {
            arg = new BoundAddressOfNode(MakeLvalueExpression(arg, sourcePos, context), sourcePos);
        }
        else if (argumentMatch.postConversionFlags == OperationFlags::deref)
        {
            arg = new BoundDereferenceNode(arg, sourcePos);
        }
        boundFunctionCall->AddArgument(arg);
    }
    return boundFunctionCall;
}

bool FindQualificationConversion(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, ArgumentMatch& argumentMatch)
{
    int distance = 0;
    if (argumentMatch.conversionFun)
    {
        argumentMatch.conversionKind = argumentMatch.conversionFun->GetConversionKind();
        distance = argumentMatch.conversionFun->ConversionDistance();
    }
    if (paramType->IsRValueRefType() && !argType->IsRValueRefType())
    {
        ++functionMatch.numQualifyingConversions;
    }
    if (argType->IsConstType())
    {
        if (paramType->IsConstType() || !paramType->IsReferenceType())
        {
            ++distance;
        }
        else
        {
            distance = 255;
        }
    }
    else
    {
        if (paramType->IsConstType())
        {
            distance += 2;
        }
        else
        {
            distance += 3;
        }
    }
    if (argType->IsReferenceType() && !paramType->IsReferenceType())
    {
        argumentMatch.postConversionFlags = OperationFlags::deref;
        argumentMatch.distance = distance;
        ++functionMatch.numQualifyingConversions;
        return true;
    }
    else if (!argType->IsReferenceType() && paramType->IsReferenceType())
    {
        argumentMatch.postConversionFlags = OperationFlags::addr;
        argumentMatch.distance = distance;
        ++functionMatch.numQualifyingConversions;
        return true;
    }
    else if (argType->IsConstType() && !paramType->IsConstType())
    {
        ++functionMatch.numQualifyingConversions;
        ++distance;
        if (argType->IsLValueRefType() && paramType->IsRValueRefType())
        {
            ++distance;
            ++functionMatch.numQualifyingConversions;
        }
        argumentMatch.distance = distance;
        return true;
    }
    else if (!argType->IsConstType() && paramType->IsConstType())
    {
        ++functionMatch.numQualifyingConversions;
        ++distance;
        if (argType->IsLValueRefType() && paramType->IsRValueRefType())
        {
            ++distance;
            ++functionMatch.numQualifyingConversions;
        }
        argumentMatch.distance = distance;
        return true;
    }
    else if (argType->IsLValueRefType() && paramType->IsRValueRefType())
    {
        ++distance;
        ++functionMatch.numQualifyingConversions;
        argumentMatch.distance = distance;
        return true;
    }
    else if (argType->IsRValueRefType() && paramType->IsLValueRefType())
    {
        ++distance;
        ++functionMatch.numQualifyingConversions;
        argumentMatch.distance = distance;
        return true;
    }
    else if (argumentMatch.conversionFun)
    {
        argumentMatch.distance = distance;
        return true;
    }
    return false;
}

bool FindTemplateParameterMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, Context* context)
{
    if (!paramType->GetBaseType()->IsTemplateParameterSymbol()) return false;
    TemplateParameterSymbol* templateParameter = static_cast<TemplateParameterSymbol*>(paramType->GetBaseType());
    TypeSymbol* templateArgumentType = nullptr;
    auto it = functionMatch.templateParameterMap.find(templateParameter);
    if (it == functionMatch.templateParameterMap.cend())
    {
        templateArgumentType = argType->RemoveDerivations(paramType->GetDerivations(), context);
        if (templateArgumentType)
        {
            functionMatch.templateParameterMap[templateParameter] = templateArgumentType;
        }
        else
        {
            return false;
        }
    }
    else
    {
        templateArgumentType = it->second;
    }
    paramType = paramType->Unify(templateArgumentType, context);
    if (!paramType)
    {
        return false;
    }
    if (TypesEqual(argType, paramType))
    {
        functionMatch.argumentMatches.push_back(ArgumentMatch());
        return true;
    }
    else
    {
        bool qualificationConversionMatch = false;
        ArgumentMatch argumentMatch;
        if (TypesEqual(argType->PlainType(), paramType->PlainType()))
        {
            qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return true;
            }
            else
            {
                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(paramType, argType, context);
                if (conversionFun)
                {
                    ++functionMatch.numConversions;
                    argumentMatch.conversionFun = conversionFun;
                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                    {
                        if (FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (FindQualificationConversion(conversionFun->ConversionArgType(), paramType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool FindConversions(FunctionMatch& functionMatch, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, Context* context)
{
    int arity = args.size();
    int n = std::min(arity, functionMatch.function->MemFunArity());
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i].get();
        TypeSymbol* argType = arg->GetType();
        ParameterSymbol* parameter = functionMatch.function->MemFunParameters()[i];
        TypeSymbol* paramType = parameter->GetReferredType();
        if (TypesEqual(argType, paramType))
        {
            functionMatch.argumentMatches.push_back(ArgumentMatch());
        }
        else
        {
            bool qualificationConversionMatch = false;
            ArgumentMatch argumentMatch;
            if (TypesEqual(argType->PlainType(), paramType->PlainType()))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
                if (qualificationConversionMatch)
                {
                    functionMatch.argumentMatches.push_back(argumentMatch);
                }
            }
            if (!qualificationConversionMatch)
            {
                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(paramType, argType, context);
                if (conversionFun)
                {
                    argumentMatch.conversionFun = conversionFun;
                    ++functionMatch.numConversions;
                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                    {
                        if (FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (FindQualificationConversion(conversionFun->ConversionArgType(), paramType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    if (functionMatch.function->IsTemplate())
                    {
                        if (FindTemplateParameterMatch(argType, paramType, arg, functionMatch, context))
                        {
                            continue;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

FunctionMatch SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    std::vector<FunctionMatch> functionMatches;
    for (FunctionSymbol* viableFunction : viableFunctions)
    {
        FunctionMatch functionMatch(viableFunction);
        if (FindConversions(functionMatch, args, context))
        {
            functionMatches.push_back(functionMatch);
        }
    }
    if (functionMatches.size() == 1)
    {
        return functionMatches.front();
    }
    else if (functionMatches.size() > 1)
    {
        std::sort(functionMatches.begin(), functionMatches.end(), BetterFunctionMatch());
        if (BetterFunctionMatch()(functionMatches[0], functionMatches[1]))
        {
            return functionMatches.front();
        }
        else
        {
            ex = Exception("ambiguous function call", sourcePos, context);
            return FunctionMatch(nullptr);
        }
    }
    else
    {
        ex = Exception("no matching function found for function call", sourcePos, context);
        return FunctionMatch(nullptr);
    }
}

Scope* GetArgumentScope(BoundExpressionNode* arg)
{
    TypeSymbol* type = arg->GetType();
    return type->GetBaseType()->GetScope();
}

void AddArgumentScopes(std::vector<std::pair<Scope*, ScopeLookup>>& scopeLookups, const std::vector<std::unique_ptr<BoundExpressionNode>>& args)
{
    for (const auto& arg : args)
    {
        Scope* scope = GetArgumentScope(arg.get());
        if (scope)
        {
            std::pair<Scope*, ScopeLookup> scopeLookup = std::make_pair(scope, ScopeLookup::thisAndBaseScopes);
            if (std::find(scopeLookups.begin(), scopeLookups.end(), scopeLookup) == scopeLookups.end())
            {
                scopeLookups.push_back(scopeLookup);
            }
        }
    }
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags)
{
    std::vector<FunctionSymbol*> viableFunctions;
    FunctionSymbol* operation = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
    if (operation)
    {
        viableFunctions.push_back(operation);
    }
    else
    {
        std::vector<std::pair<Scope*, ScopeLookup>> scopeLookups;
        scopeLookups.push_back(std::make_pair(scope, ScopeLookup::allScopes));
        AddArgumentScopes(scopeLookups, args);
        context->GetSymbolTable()->CollectViableFunctions(scopeLookups, groupName, args.size(), viableFunctions, context);
    }
    FunctionMatch bestMatch = SelectBestMatchingFunction(viableFunctions, args, sourcePos, context, ex);
    if (!bestMatch.function) return std::unique_ptr<BoundFunctionCallNode>();
    if ((bestMatch.function->Qualifiers() & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
    {
        ex = Exception("attempt to call a deleted function", sourcePos, context);
        return std::unique_ptr<BoundFunctionCallNode>();
    }
    bool instantiate = (flags & OverloadResolutionFlags::dontInstantiate) == OverloadResolutionFlags::none;
    if (instantiate && bestMatch.function->IsTemplate())
    {
        bestMatch.function = InstantiateFunctionTemplate(bestMatch.function, bestMatch.templateParameterMap, sourcePos, context);
    }
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = CreateBoundFunctionCall(bestMatch, args, sourcePos, context);
    return boundFunctionCall;
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    return ResolveOverload(scope, groupName, args, sourcePos, context, ex, OverloadResolutionFlags::none);
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    Exception ex;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
    if (!boundFunctionCall)
    {
        ThrowException(ex);
    }
    return boundFunctionCall;
}

} // namespace otava::symbols
