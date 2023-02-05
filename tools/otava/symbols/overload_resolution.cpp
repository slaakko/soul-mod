// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.classes;
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
import otava.symbols.class_templates;
import otava.symbols.class_group.symbol;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.expression.binder;
import otava.symbols.fundamental.type.symbol;
import util.unicode;

namespace otava::symbols {

ArgumentMatch::ArgumentMatch() :
    conversionFun(nullptr),
    conversionKind(ConversionKind::implicitConversion),
    distance(0),
    fundamentalTypeDistance(0),
    preConversionFlags(OperationFlags::none),
    postConversionFlags(OperationFlags::none)
{
}

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
    ClassTemplateSpecializationSymbol* specialization;
    std::vector<std::unique_ptr<BoundExpressionNode>> defaultArgs;
};

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

FunctionMatch::FunctionMatch(FunctionSymbol* function_) : function(function_), numConversions(0), numQualifyingConversions(0), specialization(nullptr)
{
}

struct BetterFunctionMatch
{
    bool operator()(const std::unique_ptr<FunctionMatch>& left, const std::unique_ptr<FunctionMatch>& right) const;
};

bool BetterFunctionMatch::operator()(const std::unique_ptr<FunctionMatch>& left, const std::unique_ptr<FunctionMatch>& right) const
{
    BetterArgumentMatch betterArgumentMatch;
    int leftBetterArgumentMatches = 0;
    int rightBetterArgumentMatches = 0;
    int n = std::max(int(left->argumentMatches.size()), int(right->argumentMatches.size()));
    for (int i = 0; i < n; ++i)
    {
        ArgumentMatch leftMatch;
        if (i < int(left->argumentMatches.size()))
        {
            leftMatch = left->argumentMatches[i];
        }
        ArgumentMatch rightMatch;
        if (i < int(right->argumentMatches.size()))
        {
            rightMatch = right->argumentMatches[i];
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
        if (i < int(left->argumentMatches.size()))
        {
            leftMatch = left->argumentMatches[i];
        }
        ArgumentMatch rightMatch;
        if (i < int(right->argumentMatches.size()))
        {
            rightMatch = right->argumentMatches[i];
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
    if (left->numConversions < right->numConversions)
    {
        return true;
    }
    if (left->numConversions > right->numConversions)
    {
        return false;
    }
    if (left->numQualifyingConversions < right->numQualifyingConversions)
    {
        return true;
    }
    if (left->numQualifyingConversions > right->numQualifyingConversions)
    {
        return false;
    }
    if (left->function->IsFunctionDefinitionSymbol() && !right->function->IsFunctionDefinitionSymbol())
    {
        return true;
    }
    if (!left->function->IsFunctionDefinitionSymbol() && right->function->IsFunctionDefinitionSymbol())
    {
        return false;
    }
    if (left->function->IsSpecialization() && !right->function->IsSpecialization())
    {
        return true;
    }
    if (!left->function->IsSpecialization() && right->function->IsSpecialization())
    {
        return false;
    }
    int leftFundamentalTypeDistance = 0;
    int rightFundamentalTypeDistance = 0;
    for (int i = 0; i < n; ++i)
    {
        leftFundamentalTypeDistance += left->argumentMatches[i].fundamentalTypeDistance;
        rightFundamentalTypeDistance += right->argumentMatches[i].fundamentalTypeDistance;
    }
    if (leftFundamentalTypeDistance < rightFundamentalTypeDistance)
    {
        return true;
    }
    if (leftFundamentalTypeDistance > rightFundamentalTypeDistance)
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

std::unique_ptr<BoundFunctionCallNode> CreateBoundFunctionCall(FunctionMatch& functionMatch, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* type = functionMatch.function->ReturnType();
    if (type)
    {
        type = type->DirectType(context);
    }
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall(new BoundFunctionCallNode(functionMatch.function, sourcePos, type));
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i].release();
        if (i == 0 && !functionMatch.function->IsMemberFunction() && functionMatch.function->IsCtorAssignmentOrArrow())
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
            arg = MakeLvalueExpression(arg, sourcePos, context);
            TypeSymbol* type = nullptr;
            if (arg->GetType()->IsClassTypeSymbol() && arg->GetFlag(BoundExpressionFlags::bindToRvalueRef))
            {
                type = arg->GetType()->AddRValueRef(context);
            }
            else
            {
                type = arg->GetType()->AddLValueRef(context);
            }
            arg = new BoundAddressOfNode(arg, sourcePos, type); 
        }
        else if (argumentMatch.preConversionFlags == OperationFlags::deref)
        {
            arg = new BoundDereferenceNode(arg, sourcePos, arg->GetType()->RemoveReference(context));
        }
        if (argumentMatch.conversionFun)
        {
            TypeSymbol* argType = arg->GetType();
            FunctionSymbol* conversionFun = argumentMatch.conversionFun;
            if (conversionFun->GetFunctionKind() == FunctionKind::conversionMemFn && argType->PlainType(context)->IsClassTypeSymbol())
            {
                if (argType->IsReferenceType())
                {
                    arg = new BoundRefToPtrNode(arg, sourcePos, argType->RemoveReference(context)->AddPointer(context));
                }
                else
                {
                    arg = new BoundAddressOfNode(arg, sourcePos, argType->GetBaseType()->AddPointer(context));
                }
                BoundFunctionCallNode* functionCall = new BoundFunctionCallNode(conversionFun, sourcePos, conversionFun->ReturnType());
                functionCall->AddArgument(arg);
                arg = functionCall;
            }
            else
            {
                arg = new BoundConversionNode(arg, conversionFun, sourcePos);
            }
        }
        if (argumentMatch.postConversionFlags == OperationFlags::addr)
        {
            arg = new BoundAddressOfNode(MakeLvalueExpression(arg, sourcePos, context), sourcePos, arg->GetType()->AddPointer(context));
        }
        else if (argumentMatch.postConversionFlags == OperationFlags::deref)
        {
            arg = new BoundDereferenceNode(arg, sourcePos, arg->GetType()->RemoveReference(context));
        }
        boundFunctionCall->AddArgument(arg);
    }
    int m = functionMatch.defaultArgs.size();
    for (int i = 0; i < m; ++i)
    {
        BoundExpressionNode* arg = functionMatch.defaultArgs[i].release();
        boundFunctionCall->AddArgument(arg);
    }
    return boundFunctionCall;
}

bool FindQualificationConversion(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, ArgumentMatch& argumentMatch)
{
    int distance = 0;
    int fundamentalTypeDistance = 0;
    if (paramType->IsFundamentalTypeSymbol())
    {
        FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<FundamentalTypeSymbol*>(paramType);
        fundamentalTypeDistance = static_cast<int32_t>(fundamentalTypeSymbol->GetFundamentalTypeKind());
        argumentMatch.fundamentalTypeDistance = fundamentalTypeDistance;
    }
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

bool FindTemplateParameterMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, 
    Context* context)
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
        if (TypesEqual(argType->PlainType(context), paramType->PlainType(context)))
        {
            qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return true;
            }
        }
        else
        {
            FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                paramType, argType, sourcePos, argumentMatch, context);
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
    return false;
}

bool FindClassTemplateSpecializationMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, 
    const soul::ast::SourcePos& sourcePos, Context* context, bool dontResolveDefaultTemplateArguments)
{
    if (!paramType->GetBaseType()->IsClassTypeSymbol()) return false;
    ClassTypeSymbol* paramClassType = static_cast<ClassTypeSymbol*>(paramType->GetBaseType());
    if (paramClassType->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* paramSpecializationType = static_cast<ClassTemplateSpecializationSymbol*>(paramClassType);
        paramClassType = paramSpecializationType->ClassTemplate();
    }
    if (!paramClassType->IsTemplate()) return false;
    TemplateDeclarationSymbol* paramTemplateDeclaration = paramClassType->ParentTemplateDeclaration();
    int n = paramTemplateDeclaration->Arity();
    int numArgumentMatches = functionMatch.argumentMatches.size();
    if (argType->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* sourceClassTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(argType->GetBaseType());
        sourceClassTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
        std::vector<Symbol*> allTemplateArguments;
        int m = sourceClassTemplateSpecialization->TemplateArguments().size();
        if (m > n)
        {
            return false;
        }
        else if (n > m)
        {
            if (dontResolveDefaultTemplateArguments)
            {
                return false;
            }
        }
        InstantiationScope instantiationScope(sourceClassTemplateSpecialization->GetScope());
        sourceClassTemplateSpecialization->GetScope()->AddParentScope(sourceClassTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope());
        std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
        for (int i = 0; i < n; ++i)
        {
            TemplateParameterSymbol* templateParameter = paramTemplateDeclaration->TemplateParameters()[i];
            TypeSymbol* sourceArgumentType = nullptr;
            if (i >= m)
            {
                otava::ast::Node* defaultTemplateArgNode = templateParameter->DefaultTemplateArg();
                if (defaultTemplateArgNode)
                {
                    context->GetSymbolTable()->BeginScope(&instantiationScope);
                    sourceArgumentType = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context, TypeResolverFlags::dontThrow | TypeResolverFlags::dontInstantiate);
                    context->GetSymbolTable()->EndScope();
                    if (sourceArgumentType)
                    {
                        allTemplateArguments.push_back(sourceArgumentType);
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                Symbol* sourceArgumentSymbol = sourceClassTemplateSpecialization->TemplateArguments()[i];
                if (sourceArgumentSymbol->IsTypeSymbol())
                {
                    sourceArgumentType = static_cast<TypeSymbol*>(sourceArgumentSymbol);
                }
                else
                {
                    return false;
                }
                allTemplateArguments.push_back(sourceArgumentType);
            }
            BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
            boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
            boundTemplateParameter->SetBoundSymbol(sourceArgumentType);
            boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
            instantiationScope.Install(boundTemplateParameter);
            Symbol* targetArgumentSymbol = paramTemplateDeclaration->TemplateParameters()[i];
            TypeSymbol* targetArgumentType = nullptr;
            if (targetArgumentSymbol->IsTypeSymbol())
            {
                targetArgumentType = static_cast<TypeSymbol*>(targetArgumentSymbol);
            }
            else
            {
                return false;
            }
            if (FindTemplateParameterMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context))
            {
                continue;
            }
            else if (FindClassTemplateSpecializationMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context, true))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        if (n > m)
        {
            sourceClassTemplateSpecialization = context->GetSymbolTable()->MakeClassTemplateSpecialization(sourceClassTemplateSpecialization->ClassTemplate(), allTemplateArguments);
            functionMatch.specialization = sourceClassTemplateSpecialization;
            argType = context->GetSymbolTable()->MakeCompoundType(sourceClassTemplateSpecialization, argType->GetDerivations());
        }
        functionMatch.argumentMatches.resize(numArgumentMatches);
        std::vector<Symbol*> targetTemplateArguments;
        for (int i = 0; i < n; ++i)
        {
            Symbol* targetArgumentSymbol = paramTemplateDeclaration->TemplateParameters()[i];
            TypeSymbol* targetArgumentType = nullptr;
            if (targetArgumentSymbol->IsTypeSymbol())
            {
                targetArgumentType = static_cast<TypeSymbol*>(targetArgumentSymbol);
            }
            else
            {
                return false;
            }
            TypeSymbol* templateArgumentType = targetArgumentType->GetBaseType()->UnifyTemplateArgumentType(functionMatch.templateParameterMap, context);
            if (templateArgumentType)
            {
                targetTemplateArguments.push_back(templateArgumentType);
            }
            else
            {
                return false;
            }
        }
        TypeSymbol* plainTargetType = context->GetSymbolTable()->MakeClassTemplateSpecialization(paramClassType, targetTemplateArguments);
        paramType = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
        if (TypesEqual(argType, paramType))
        {
            functionMatch.argumentMatches.push_back(ArgumentMatch());
            return true;
        }
        else
        {
            bool qualificationConversionMatch = false;
            ArgumentMatch argumentMatch;
            if (TypesEqual(argType->PlainType(context), paramType->PlainType(context)))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
            }
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return true;
            }
            else
            {
                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    paramType, argType, sourcePos, argumentMatch, context);
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

bool FindConversions(FunctionMatch& functionMatch, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context,
    bool constructor)
{
    int arity = args.size();
    int n = functionMatch.function->MemFunArity(context);
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = nullptr;
        TypeSymbol* argType = nullptr;
        std::unique_ptr<BoundExpressionNode> defaultArg;
        if (i >= arity)
        {
            ParameterSymbol* parameter = functionMatch.function->MemFunParameters(context)[i];
            if (parameter->DefaultValue())
            {
                defaultArg.reset(BindExpression(parameter->DefaultValue(), context));
                arg = defaultArg.get();
                argType = arg->GetType();
                functionMatch.defaultArgs.push_back(std::move(defaultArg));
            }
            else
            {
                return false;
            }
        }
        else
        {
            arg = args[i].get();
            argType = arg->GetType();
        }
        ParameterSymbol* parameter = functionMatch.function->MemFunParameters(context)[i];
        TypeSymbol* paramType = parameter->GetReferredType(context);
        if (TypesEqual(argType, paramType))
        {
            functionMatch.argumentMatches.push_back(ArgumentMatch());
        }
        else
        {
            bool qualificationConversionMatch = false;
            ArgumentMatch argumentMatch;
            if (TypesEqual(argType->PlainType(context), paramType->PlainType(context)))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
                if (qualificationConversionMatch)
                {
                    functionMatch.argumentMatches.push_back(argumentMatch);
                }
            }
            if (!qualificationConversionMatch)
            {
                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    paramType, argType, sourcePos, argumentMatch, context);
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
                        TypeSymbol* conversionArgType = conversionFun->ConversionArgType();
                        if (!conversionArgType)
                        {
                            conversionArgType = argType;
                        }
                        if (FindQualificationConversion(conversionArgType, paramType, arg, functionMatch, argumentMatch))
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
                    if (functionMatch.function->IsTemplate() || functionMatch.function->IsMemFnOfClassTemplate())
                    {
                        if (FindTemplateParameterMatch(argType, paramType, arg, functionMatch, sourcePos, context))
                        {
                            continue;
                        }
                        if (FindClassTemplateSpecializationMatch(argType, paramType, arg, functionMatch, sourcePos, context, constructor))
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

std::unique_ptr<FunctionMatch> SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const std::u32string& groupName, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    bool constructor = groupName == U"@constructor";
    std::vector<std::unique_ptr<FunctionMatch>> functionMatches;
    int n = viableFunctions.size();
    for (int i = 0; i < n; ++i)
    {
        FunctionSymbol* viableFunction = viableFunctions[i];
        std::unique_ptr<FunctionMatch> functionMatch(new FunctionMatch(viableFunction));
        if (FindConversions(*functionMatch, args, sourcePos, context, constructor))
        {
            functionMatches.push_back(std::move(functionMatch));
        }
    }
    if (functionMatches.size() == 1)
    {
        return std::move(functionMatches.front());
    }
    else if (functionMatches.size() > 1)
    {
        std::sort(functionMatches.begin(), functionMatches.end(), BetterFunctionMatch());
        if (BetterFunctionMatch()(functionMatches[0], functionMatches[1]))
        {
            return std::move(functionMatches.front());
        }
        else
        {
            ex = Exception("ambiguous function call, " + std::to_string(viableFunctions.size()) + " viable functions examined.", sourcePos, context);
            return std::unique_ptr<FunctionMatch>(nullptr);
        }
    }
    else
    {
        ex = Exception("overload resolution failed: overload in function group '" + util::ToUtf8(groupName) + "' not found, " + 
            "or there are no acceptable conversions for all argument types. " + std::to_string(viableFunctions.size()) + " viable functions examined.", sourcePos, context);
        return std::unique_ptr<FunctionMatch>(nullptr);
    }
}

std::vector<Scope*> GetArgumentScopes(BoundExpressionNode* arg)
{
    std::vector<Scope*> scopes;
    TypeSymbol* type = arg->GetType();
    if (type)
    {
        Scope* first = type->GetBaseType()->GetScope();
        scopes.push_back(first);
        if (type->GetBaseType()->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(type->GetBaseType());
            Scope* second = sp->ClassTemplate()->GetScope()->GetNamespaceScope();
            scopes.push_back(second);
        }
    }
    return scopes;
}

void AddArgumentScopes(std::vector<std::pair<Scope*, ScopeLookup>>& scopeLookups, const std::vector<std::unique_ptr<BoundExpressionNode>>& args)
{
    for (const auto& arg : args)
    {
        std::vector<Scope*> scopes = GetArgumentScopes(arg.get());
        for (auto scope : scopes)
        {
            std::pair<Scope*, ScopeLookup> scopeLookup = std::make_pair(scope, ScopeLookup::thisAndBaseScopes);
            if (std::find(scopeLookups.begin(), scopeLookups.end(), scopeLookup) == scopeLookups.end())
            {
                scopeLookups.push_back(scopeLookup);
            }
        }
    }
}

std::unique_ptr<BoundFunctionCallNode> ResolveIOManipFn(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags)
{
    if ((groupName == U"operator<<" || groupName == U"operator>>") && args.size() == 2 && args[1]->GetType()->IsFunctionGroupTypeSymbol())
    {
        FunctionGroupTypeSymbol* functionGroupType = static_cast<FunctionGroupTypeSymbol*>(args[1]->GetType());
        BoundExpressionNode* arg = args[0]->Clone();
        std::vector<std::unique_ptr<BoundExpressionNode>> ioManipFnArgs;
        ioManipFnArgs.push_back(std::unique_ptr<BoundExpressionNode>(arg));
        std::unique_ptr<BoundFunctionCallNode> ioManipFnCall = ResolveOverload(scope, functionGroupType->FunctionGroup()->Name(), ioManipFnArgs, sourcePos, context, ex, flags);
        if (ioManipFnCall)
        {
            return ioManipFnCall;
        }
    }
    return std::unique_ptr<BoundFunctionCallNode>();
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags)
{
    std::unique_ptr<BoundFunctionCallNode> ioManipFn = ResolveIOManipFn(scope, groupName, args, sourcePos, context, ex, flags);
    if (ioManipFn)
    {
        return ioManipFn;
    }
    std::vector<FunctionSymbol*> viableFunctions;
    context->PushSetFlag(ContextFlags::ignoreClassTemplateSpecializations);
    FunctionSymbol* operation = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
    context->PopFlags();
    if (operation)
    {
        viableFunctions.push_back(operation);
    }
    else
    {
        std::vector<std::pair<Scope*, ScopeLookup>> scopeLookups;
        if ((flags & OverloadResolutionFlags::dontSearchArgumentScopes) != OverloadResolutionFlags::none)
        {
            scopeLookups.push_back(std::make_pair(scope, ScopeLookup::thisScope));
        }
        else
        {
            scopeLookups.push_back(std::make_pair(scope, ScopeLookup::allScopes));
            AddArgumentScopes(scopeLookups, args);
        }
        context->GetSymbolTable()->CollectViableFunctions(scopeLookups, groupName, args.size(), viableFunctions, context);
    }
    std::unique_ptr<FunctionMatch> bestMatch = SelectBestMatchingFunction(viableFunctions, args, groupName, sourcePos, context, ex);
    if (!bestMatch)
    {
        FunctionSymbol* operation = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
        if (operation)
        {
            viableFunctions.clear();
            viableFunctions.push_back(operation);
            bestMatch = SelectBestMatchingFunction(viableFunctions, args, groupName, sourcePos, context, ex);
        }
        if (!bestMatch)
        {
            return std::unique_ptr<BoundFunctionCallNode>();
        }
    }
    if ((bestMatch->function->Qualifiers() & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
    {
        ex = Exception("attempt to call a deleted function", sourcePos, context);
        return std::unique_ptr<BoundFunctionCallNode>();
    }
    bool instantiate = (flags & OverloadResolutionFlags::dontInstantiate) == OverloadResolutionFlags::none;
    if (instantiate)
    {
        if (bestMatch->function->IsTemplate())
        {
            bestMatch->function = InstantiateFunctionTemplate(bestMatch->function, bestMatch->templateParameterMap, sourcePos, context);
        }
        else if (bestMatch->function->IsMemFnOfClassTemplate())
        {
            ClassTemplateSpecializationSymbol* classTemplateSpecialization = nullptr;
            if (bestMatch->specialization)
            {
                classTemplateSpecialization = bestMatch->specialization;
            }
            else
            {
                TypeSymbol* arg0Type = args[0]->GetType()->GetBaseType();
                if (arg0Type->IsClassTemplateSpecializationSymbol())
                {
                    classTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(arg0Type);
                }
                else
                {
                    ex = Exception("function argument 0 is expected to be a class template specialization", sourcePos, context);
                    return std::unique_ptr<BoundFunctionCallNode>();
                }
            }
            bestMatch->function = InstantiateMemFnOfClassTemplate(bestMatch->function, classTemplateSpecialization, sourcePos, context);
        }
    }
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = CreateBoundFunctionCall(*bestMatch, args, sourcePos, context);
    return boundFunctionCall;
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    return ResolveOverload(scope, groupName, args, sourcePos, context, ex, OverloadResolutionFlags::none);
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags)
{
    Exception ex;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex, flags);
    if (!boundFunctionCall)
    {
        ThrowException(ex);
    }
    return boundFunctionCall;
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    return ResolveOverloadThrow(scope, groupName, args, sourcePos, context, OverloadResolutionFlags::none);
}

} // namespace otava::symbols
