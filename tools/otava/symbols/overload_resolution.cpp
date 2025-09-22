// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.function.group.symbol;
import otava.symbols.function.symbol;
import otava.symbols.function.type.symbol;
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
import otava.symbols.variable.symbol;
import otava.symbols.type_compare;
import otava.symbols.inline_functions;
import otava.symbols.enums;
import otava.opt;
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

std::int32_t ArgumentConversionValue(const ArgumentMatch& match)
{
    std::int32_t argumentConversionValue = 0;
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
    if (left.fundamentalTypeDistance < right.fundamentalTypeDistance) return true;
    if (left.fundamentalTypeDistance > right.fundamentalTypeDistance) return false;
    return false;
}

FunctionMatch::FunctionMatch() : function(nullptr), numConversions(0), numQualifyingConversions(0), specialization(nullptr)
{
}

FunctionMatch::FunctionMatch(FunctionSymbol* function_, Context* context_) : 
    function(function_), context(context_), numConversions(0), numQualifyingConversions(0), specialization(nullptr)
{
}

FunctionMatch& FunctionMatch::operator=(const FunctionMatch& that)
{
    function = that.function;
    context = that.context;
    argumentMatches = that.argumentMatches;
    numConversions = that.numConversions;
    numQualifyingConversions = that.numQualifyingConversions;
    templateParameterMap = that.templateParameterMap;
    specialization = that.specialization;
    return *this;
}

bool BetterFunctionMatch::operator()(const FunctionMatch& left, const FunctionMatch& right) const
{
    if (left.function->IsTemplate() && !right.function->IsTemplate())
    {
        return true;
    }
    if (!left.function->IsTemplate() && right.function->IsTemplate())
    {
        return false;
    }
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
    if (!left.function->IsSpecialization() && right.function->IsSpecialization())
    {
        return true;
    }
    if (left.function->IsSpecialization() && !right.function->IsSpecialization())
    {
        return false;
    }
    if ((left.function->IsTemplate() || left.function->IsMemFnOfClassTemplate()) && !(right.function->IsTemplate() || right.function->IsMemFnOfClassTemplate()))
    {
        return true;
    }
    if (!(left.function->IsTemplate() || left.function->IsMemFnOfClassTemplate()) && (right.function->IsTemplate() || right.function->IsMemFnOfClassTemplate()))
    {
        return false;
    }
    if (left.function->IsConst() && !right.function->IsConst())
    {
        return true;
    }
    if (!left.function->IsConst() && right.function->IsConst())
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
    const soul::ast::SourcePos& sourcePos, Exception& ex, Context* context)
{
    TypeSymbol* type = functionMatch.function->ReturnType();
    if (type)
    {
        type = type->DirectType(context)->FinalType(sourcePos, context);
    }
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall(new BoundFunctionCallNode(functionMatch.function, sourcePos, type));
    int n = args.size();
    int m = functionMatch.defaultArgs.size();
    int count = n + m;
    for (int i = 0; i < count; ++i)
    {
        BoundExpressionNode* arg = nullptr;
        if (i >= n)
        {
            arg = functionMatch.defaultArgs[i - n].release();
        }
        else
        {
            arg = args[i].release();
        }
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
        ArgumentMatch& argumentMatch = functionMatch.argumentMatches[i];
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
            if (conversionFun->GetConversionKind() == ConversionKind::explicitConversion && !context->GetFlag(ContextFlags::suppress_warning))
            {
                ex = Exception("warning: ", "conversion from '" + util::ToUtf8(conversionFun->ConversionArgType()->FullName()) + "' to '" +
                    util::ToUtf8(conversionFun->ConversionParamType()->FullName()) + "' without a cast", sourcePos, context);
                ex.SetWarning();
            }
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
            else if (conversionFun->GetFunctionKind() == FunctionKind::constructor)
            {
                VariableSymbol* temporary = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(conversionFun->ConversionParamType());
                BoundVariableNode* boundTemporary = new BoundVariableNode(temporary, sourcePos);
                BoundFunctionCallNode* constructorCall = new BoundFunctionCallNode(conversionFun, sourcePos, nullptr);
                BoundAddressOfNode* temporaryArg = new BoundAddressOfNode(boundTemporary, sourcePos, temporary->GetType()->AddPointer(context));
                constructorCall->AddArgument(temporaryArg);
                if (argumentMatch.preConversionFlags == OperationFlags::addr)
                {
                    arg = new BoundAddressOfNode(MakeLvalueExpression(arg, sourcePos, context), sourcePos, arg->GetType()->AddPointer(context));
                }
                else if (argumentMatch.preConversionFlags == OperationFlags::deref)
                {
                    arg = new BoundDereferenceNode(arg, sourcePos, arg->GetType()->RemoveReference(context));
                }
                constructorCall->AddArgument(arg);
                BoundExpressionNode* boundTemporary2 = new BoundVariableNode(temporary, sourcePos);
                if (argumentMatch.postConversionFlags == OperationFlags::addr)
                {
                    boundTemporary2 = new BoundAddressOfNode(MakeLvalueExpression(boundTemporary2, sourcePos, context), sourcePos, boundTemporary2->GetType()->AddPointer(context));
                }
                else if (argumentMatch.postConversionFlags == OperationFlags::deref)
                {
                    boundTemporary2 = new BoundDereferenceNode(boundTemporary2, sourcePos, boundTemporary2->GetType()->RemoveReference(context));
                }
                argumentMatch.postConversionFlags = OperationFlags::none;
                BoundConstructTemporaryNode* constructTemporary = new BoundConstructTemporaryNode(constructorCall, boundTemporary2, sourcePos);
                arg = constructTemporary;
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
    return boundFunctionCall;
}

bool FindQualificationConversion(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, ArgumentMatch& argumentMatch)
{
    int distance = 0;
    int fundamentalTypeDistance = 0;
    if (paramType->IsFundamentalTypeSymbol())
    {
        FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<FundamentalTypeSymbol*>(paramType);
        fundamentalTypeDistance = static_cast<std::int32_t>(fundamentalTypeSymbol->GetFundamentalTypeKind());
        argumentMatch.fundamentalTypeDistance = fundamentalTypeDistance;
    }
    if (argumentMatch.conversionFun)
    {
        argumentMatch.conversionKind = argumentMatch.conversionFun->GetConversionKind();
        distance = argumentMatch.conversionFun->ConversionDistance();
    }
    if (paramType->IsRValueRefType())
    {
        if (!argType->IsRValueRefType())
        {
            ++functionMatch.numQualifyingConversions;
            distance += 5;
        }
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
        else if (!paramType->IsRValueRefType())
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
        if (paramType->IsRValueRefType() && arg->BindToRvalueRef())
        {
            argumentMatch.distance = 0;
            return true;
        }
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
        ArgumentMatch argumentMatch;
        if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
        {
            argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
        }
        functionMatch.argumentMatches.push_back(argumentMatch);
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
                paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
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
                    if (FindQualificationConversion(conversionFun->ConversionParamType(), paramType, arg, functionMatch, argumentMatch))
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

bool FindClassTemplateMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!paramType->GetBaseType()->IsClassTypeSymbol()) return false;
    ClassTypeSymbol* paramClassType = static_cast<ClassTypeSymbol*>(paramType->GetBaseType());
    if (!paramClassType->IsTemplate()) return false;
    TemplateDeclarationSymbol* paramTemplateDeclaration = paramClassType->ParentTemplateDeclaration();
    int n = 0;
    int arity = paramTemplateDeclaration->Arity();
    int numArgumentMatches = functionMatch.argumentMatches.size();
    if (argType->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* sourceClassTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(argType->GetBaseType());
        int m = sourceClassTemplateSpecialization->TemplateArguments().size();
        n = std::min(arity, m);
        for (int i = 0; i < n; ++i)
        {
            TypeSymbol* sourceArgumentType = nullptr;
            Symbol* sourceArgumentSymbol = sourceClassTemplateSpecialization->TemplateArguments()[i];
            if (sourceArgumentSymbol->IsTypeSymbol())
            {
                sourceArgumentType = static_cast<TypeSymbol*>(sourceArgumentSymbol);
            }
            else
            {
                return false;
            }
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
            else if (FindClassTemplateMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context))
            {
                continue;
            }
            else if (FindClassTemplateSpecializationMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    if (n == 0)
    {
        return false;
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
        TypeSymbol* templateArgumentType = targetArgumentType->UnifyTemplateArgumentType(functionMatch.templateParameterMap, context);
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
        ArgumentMatch argumentMatch;
        if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
        {
            argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
        }
        functionMatch.argumentMatches.push_back(argumentMatch);
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
                paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
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
                    if (FindQualificationConversion(conversionFun->ConversionParamType(), paramType, arg, functionMatch, argumentMatch))
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

bool PlainTemplateArgsEqual(const std::vector<Symbol*>& sourceTemplateArguments, const std::vector<Symbol*>& targetTemplateArguments, Context* context)
{
    int n = sourceTemplateArguments.size();
    int m = targetTemplateArguments.size();
    if (n != m) return false;
    for (int i = 0; i < n; ++i)
    {
        Symbol* sourceTemplateArg = sourceTemplateArguments[i];
        Symbol* targetTemplateArg = targetTemplateArguments[i];
        if (!sourceTemplateArg->IsTypeSymbol() || !targetTemplateArg->IsTypeSymbol()) return false;
        if (!TypesEqual(static_cast<TypeSymbol*>(sourceTemplateArg)->PlainType(context), static_cast<TypeSymbol*>(targetTemplateArg)->PlainType(context)))
        {
            return false;
        }
    }
    return true;
}

bool FindClassTemplateSpecializationMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!paramType->GetBaseType()->IsClassTypeSymbol()) return false;
    ClassTypeSymbol* paramClassType = static_cast<ClassTypeSymbol*>(paramType->GetBaseType());
    ClassTemplateSpecializationSymbol* paramSpecializationType = nullptr;
    if (paramClassType->IsClassTemplateSpecializationSymbol())
    {
        paramSpecializationType = static_cast<ClassTemplateSpecializationSymbol*>(paramClassType);
    }
    else
    {
        return false;
    }
    int n = paramSpecializationType->TemplateArguments().size();
    int numArgumentMatches = functionMatch.argumentMatches.size();
    std::vector<Symbol*> sourceTemplateArguments;
    if (argType->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* sourceClassTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(argType->GetBaseType());
        int m = sourceClassTemplateSpecialization->TemplateArguments().size();
        if (n != m) return false;
        sourceTemplateArguments = sourceClassTemplateSpecialization->TemplateArguments();
        for (int i = 0; i < n; ++i)
        {
            Symbol* sourceArgumentSymbol = sourceClassTemplateSpecialization->TemplateArguments()[i];
            TypeSymbol* sourceArgumentType = nullptr;
            if (sourceArgumentSymbol->IsTypeSymbol())
            {
                sourceArgumentType = static_cast<TypeSymbol*>(sourceArgumentSymbol);
            }
            else
            {
                return false;
            }
            Symbol* targetArgumentSymbol = paramSpecializationType->TemplateArguments()[i];
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
            else if (FindClassTemplateMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context))
            {
                continue;
            }
            else if (FindClassTemplateSpecializationMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        functionMatch.argumentMatches.resize(numArgumentMatches);
        std::vector<Symbol*> targetTemplateArguments;
        for (int i = 0; i < n; ++i)
        {
            Symbol* templateArgumentSymbol = paramSpecializationType->TemplateArguments()[i];
            TypeSymbol* templateArgumentType = nullptr;
            if (templateArgumentSymbol->IsTypeSymbol())
            {
                templateArgumentType = static_cast<TypeSymbol*>(templateArgumentSymbol);
            }
            templateArgumentType = templateArgumentType->UnifyTemplateArgumentType(functionMatch.templateParameterMap, context);
            if (templateArgumentType)
            {
                targetTemplateArguments.push_back(templateArgumentType);
            }
            else
            {
                return false;
            }
        }
        TypeSymbol* plainTargetType = context->GetSymbolTable()->MakeClassTemplateSpecialization(paramSpecializationType->ClassTemplate(), targetTemplateArguments);
        TypeSymbol* compoundParamType = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
        if (TypesEqual(argType, compoundParamType))
        {
            ArgumentMatch argumentMatch;
            if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
            {
                argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
            }
            functionMatch.argumentMatches.push_back(argumentMatch);
            return true;
        }
        else
        {
            ArgumentMatch argumentMatch;
            bool qualificationConversionMatch = false;
            if (TypesEqual(argType->PlainType(context), compoundParamType->PlainType(context)))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch);
            }
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return true;
            }
            else
            {
                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    compoundParamType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
                if (conversionFun)
                {
                    ++functionMatch.numConversions;
                    argumentMatch.conversionFun = conversionFun;
                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                    {
                        if (FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch))
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
                        if (FindQualificationConversion(conversionFun->ConversionParamType(), compoundParamType, arg, functionMatch, argumentMatch))
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
                else
                {
                    bool plainTemplateArgsEqual = PlainTemplateArgsEqual(sourceTemplateArguments, targetTemplateArguments, context);
                    if (plainTemplateArgsEqual)
                    {
                        ++functionMatch.numConversions;
                        plainTargetType = context->GetSymbolTable()->MakeClassTemplateSpecialization(paramSpecializationType->ClassTemplate(), sourceTemplateArguments);
                        compoundParamType = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
                        if (TypesEqual(argType, compoundParamType))
                        {
                            functionMatch.argumentMatches.push_back(ArgumentMatch());
                            return true;
                        }
                        else
                        {
                            ArgumentMatch argumentMatch;
                            if (TypesEqual(argType->PlainType(context), compoundParamType->PlainType(context)))
                            {
                                qualificationConversionMatch = FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch);
                            }
                            if (qualificationConversionMatch)
                            {
                                functionMatch.argumentMatches.push_back(argumentMatch);
                                return true;
                            }
                            else
                            {
                                FunctionSymbol* conversionFun = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                                    compoundParamType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
                                if (conversionFun)
                                {
                                    ++functionMatch.numConversions;
                                    argumentMatch.conversionFun = conversionFun;
                                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                                    {
                                        if (FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch))
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
                                        if (FindQualificationConversion(conversionFun->ConversionParamType(), compoundParamType, arg, functionMatch, argumentMatch))
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

bool FindConversions(FunctionMatch& functionMatch, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    int arity = args.size();
    int n = functionMatch.function->MemFunArity(context);
    for (int i = 0; i < n; ++i)
    {
        context->SetArgIndex(i);
        BoundExpressionNode* arg = nullptr;
        TypeSymbol* argType = nullptr;
        std::unique_ptr<BoundExpressionNode> defaultArg;
        if (i >= arity)
        {
            ParameterSymbol* parameter = functionMatch.function->MemFunParameters(context)[i];
            if (parameter->DefaultValue())
            {
                context->GetSymbolTable()->CurrentScope()->PushParentScope(functionMatch.function->GetScope());
                defaultArg.reset(BindExpression(parameter->DefaultValue(), context));
                context->GetSymbolTable()->CurrentScope()->PopParentScope();
                arg = defaultArg.get();
                argType = arg->GetType()->DirectType(context)->FinalType(sourcePos, context);
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
        context->PushSetFlag(ContextFlags::resolveDependentTypes | ContextFlags::resolveNestedTypes);
        context->PushTemplateParameterMap(&functionMatch.templateParameterMap);
        context->SetSourcePos(sourcePos);
        TypeSymbol* paramType = parameter->GetReferredType(context)->FinalType(sourcePos, context);
        context->PopTemplateParameterMap();
        context->PopFlags();
        if (TypesEqual(argType, paramType))
        {
            ArgumentMatch argumentMatch;
            if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
            {
                argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
            }
            functionMatch.argumentMatches.push_back(argumentMatch);
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
                    paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
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
                        TypeSymbol* conversionParamType = conversionFun->ConversionParamType();
                        if (FindQualificationConversion(conversionParamType, paramType, arg, functionMatch, argumentMatch))
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
                        if (FindClassTemplateMatch(argType, paramType, arg, functionMatch, sourcePos, context))
                        {
                            continue;
                        }
                        if (FindClassTemplateSpecializationMatch(argType, paramType, arg, functionMatch, sourcePos, context))
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

void SetTemplateArgs(FunctionSymbol* viableFunction, std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, 
    const std::vector<TypeSymbol*>& templateArgs)
{
    if (viableFunction->IsTemplate())
    {
        TemplateDeclarationSymbol* templateDeclaration = viableFunction->ParentTemplateDeclaration();
        if (templateDeclaration)
        {
            int n = templateArgs.size();
            if (templateDeclaration->Arity() >= n)
            {
                for (int i = 0; i < n; ++i)
                {
                    TypeSymbol* templateArg = templateArgs[i];
                    TemplateParameterSymbol* templateParam = templateDeclaration->TemplateParameters()[i];
                    templateParameterMap[templateParam] = templateArg;
                }
            }
        }
    }
}

std::unique_ptr<FunctionMatch> SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<TypeSymbol*>& templateArgs, 
    const std::vector<std::unique_ptr<BoundExpressionNode>>& args, const std::u32string& groupName, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    std::vector<std::unique_ptr<FunctionMatch>> functionMatches;
    std::set<FunctionSymbol*> viableFunctionSet;
    std::set<std::u32string> viableFunctionFullNameSet;
    int n = viableFunctions.size();
    for (int i = 0; i < n; ++i)
    {
        FunctionSymbol* viableFunction = viableFunctions[i];
        if (viableFunctionSet.find(viableFunction) != viableFunctionSet.end())
        {
            continue;
        }
        if (viableFunction->IsFunctionDefinitionSymbol() && viableFunctionFullNameSet.find(viableFunction->FullName()) != viableFunctionFullNameSet.end())
        {
            continue;
        }
        viableFunctionSet.insert(viableFunction);
        if (viableFunction->IsFunctionDefinitionSymbol())
        {
            viableFunctionFullNameSet.insert(viableFunction->FullName());
        }
        std::unique_ptr<FunctionMatch> functionMatch(new FunctionMatch(viableFunction, context));
        SetTemplateArgs(viableFunction, functionMatch->templateParameterMap, templateArgs);
        if (FindConversions(*functionMatch, args, sourcePos, context))
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
            std::string message = "ambiguous function call, " + std::to_string(viableFunctions.size()) + " viable functions examined:";
            bool first = true;
            for (const auto& functionMatch : functionMatches)
            {
                if (BetterFunctionMatch()(functionMatches[0], functionMatch)) break;
                if (first)
                {
                    first = false;
                }
                else
                {
                    message.append(" or \n");
                }
                message.append(util::ToUtf8(functionMatch->function->FullName()));
            }
            ex = Exception(message);
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
        Scope* second = first->GetNamespaceScope();
        if (second)
        {
            scopes.push_back(second);
        }
        if (type->GetBaseType()->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(type->GetBaseType());
            Scope* third = sp->ClassTemplate()->GetScope()->GetNamespaceScope();
            scopes.push_back(third);
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
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> ioManipFnCall = ResolveOverload(scope, functionGroupType->FunctionGroup()->Name(), templateArgs, 
            ioManipFnArgs, sourcePos, context, ex, flags);
        if (ioManipFnCall)
        {
            FunctionTypeSymbol* functionType = ioManipFnCall->GetFunctionSymbol()->GetFunctionType(context);
            Derivations derivations;
            derivations.vec.push_back(Derivation::pointerDerivation);
            TypeSymbol* functionPtrType = context->GetSymbolTable()->MakeCompoundType(functionType, derivations);
            std::unique_ptr<BoundExpressionNode> ioManipArg(new BoundAddressOfNode(ioManipFnCall.release(), sourcePos, functionPtrType));
            std::vector<std::unique_ptr<BoundExpressionNode>> operatorPutOrGetArgs;
            BoundExpressionNode* arg = args[0]->Clone();
            operatorPutOrGetArgs.push_back(std::unique_ptr<BoundExpressionNode>(arg));
            operatorPutOrGetArgs.push_back(std::unique_ptr<BoundExpressionNode>(ioManipArg.release()));
            std::unique_ptr<BoundFunctionCallNode> operatorPutOrGetCall = ResolveOverload(
                scope, groupName, templateArgs, operatorPutOrGetArgs, sourcePos, context, ex, flags);
            if (operatorPutOrGetCall)
            {
                return operatorPutOrGetCall;
            }
        }
    }
    return std::unique_ptr<BoundFunctionCallNode>();
}

void MakeFinalDirectArgs(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    for (auto& arg : args)
    {
        arg->ModifyTypes(sourcePos, context);
    }
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, FunctionMatch& functionMatch, 
    OverloadResolutionFlags flags)
{
    MakeFinalDirectArgs(args, sourcePos, context);
    std::vector<FunctionSymbol*> viableFunctions;
    if (groupName == U"@destructor")
    {
        if (args.size() == 1)
        {
            BoundExpressionNode* arg = args[0].get();
            if (arg->GetType()->GetBaseType()->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(arg->GetType()->GetBaseType());
                Symbol* destructor = GenerateDestructor(specialization, sourcePos, context);
                viableFunctions.push_back(static_cast<FunctionSymbol*>(destructor));
            }
        }
    }
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
            scopeLookups.push_back(std::make_pair(scope, ScopeLookup::thisAndBaseScopes));
        }
        else
        {
            scopeLookups.push_back(std::make_pair(scope, ScopeLookup::allScopes));
            AddArgumentScopes(scopeLookups, args);
        }
        context->GetSymbolTable()->CollectViableFunctions(scopeLookups, groupName, templateArgs, args.size(), viableFunctions, context);
    }
    std::unique_ptr<FunctionMatch> bestMatch = SelectBestMatchingFunction(viableFunctions, templateArgs, args, groupName, sourcePos, context, ex);
    if (!bestMatch)
    {
        context->ResetFlag(ContextFlags::ignoreClassTemplateSpecializations);
        FunctionSymbol* operation = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
        if (operation)
        {
            viableFunctions.clear();
            viableFunctions.push_back(operation);
            bestMatch = SelectBestMatchingFunction(viableFunctions, templateArgs, args, groupName, sourcePos, context, ex);
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
    context->ResetFlag(ContextFlags::noPtrOps);
    functionMatch = *bestMatch;
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
                if (!bestMatch->function->IsStatic())
                {
                    TypeSymbol* arg0Type = args[0]->GetType()->GetBaseType();
                    if (arg0Type->IsClassTemplateSpecializationSymbol())
                    {
                        classTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(arg0Type);
                    }
                }
            }
            bestMatch->function = InstantiateMemFnOfClassTemplate(bestMatch->function, classTemplateSpecialization, bestMatch->templateParameterMap, sourcePos, context);
        }
        else if (bestMatch->function->IsInline() && context->ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining))
        {
            bestMatch->function = InstantiateInlineFunction(bestMatch->function, sourcePos, context);
        }
    }
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = CreateBoundFunctionCall(*bestMatch, args, sourcePos, ex, context);
    return boundFunctionCall;
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags)
{
    FunctionMatch functionMatch;
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, ex, functionMatch, flags);
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, FunctionMatch& functionMatch)
{
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, ex, functionMatch, OverloadResolutionFlags::none);
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex)
{
    FunctionMatch functionMatch;
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, ex, functionMatch, OverloadResolutionFlags::none);
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags)
{
    Exception ex;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, ex, flags);
    if (!boundFunctionCall)
    {
        ThrowException(ex);
    }
    return boundFunctionCall;
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return ResolveOverloadThrow(scope, groupName, templateArgs, args, sourcePos, context, OverloadResolutionFlags::none);
}

} // namespace otava::symbols
