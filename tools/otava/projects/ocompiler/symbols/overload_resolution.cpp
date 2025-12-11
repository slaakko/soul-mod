// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.classes;
import otava.symbols.error;
import otava.symbols.function.group.symbol;
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

FunctionMatch& FunctionMatch::operator=(const FunctionMatch& that) : defaultArgs()
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

std::expected<BoundExpressionNode*, int> MakeLvalueExpression(BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (arg->IsLvalueExpression()) return arg;
    BoundVariableNode* backingStore = nullptr;
    if (context->GetBoundFunction())
    {
        std::expected<VariableSymbol*, int> trv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(arg->GetType());
        if (!trv) return std::unexpected<int>(trv.error());
        backingStore = new BoundVariableNode(*trv, sourcePos);
    }
    return std::expected<BoundExpressionNode*, int>(new BoundTemporaryNode(arg, backingStore, sourcePos));
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> CreateBoundFunctionCall(FunctionMatch& functionMatch, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* type = functionMatch.function->ReturnType();
    if (type)
    {
        std::expected<TypeSymbol*, int> dt = type->DirectType(context);
        if (!dt) return std::unexpected<int>(dt.error());
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> trv = directType->FinalType(sourcePos, context);
        if (!trv) return std::unexpected<int>(trv.error());
        type = *trv;
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
            std::expected<BoundExpressionNode*, int> rv = MakeLvalueExpression(arg, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            arg = *rv;
            TypeSymbol* type = nullptr;
            if (arg->GetType()->IsClassTypeSymbol() && arg->GetFlag(BoundExpressionFlags::bindToRvalueRef))
            {
                std::expected<TypeSymbol*, int> pt = arg->GetType()->AddRValueRef(context);
                if (!pt) return std::unexpected<int>(pt.error());
                type = *pt;
            }
            else
            {
                std::expected<TypeSymbol*, int> pt = arg->GetType()->AddLValueRef(context);
                if (!pt) return std::unexpected<int>(pt.error());
                type = *pt;
            }
            arg = new BoundAddressOfNode(arg, sourcePos, type);
        }
        else if (argumentMatch.preConversionFlags == OperationFlags::deref)
        {
            std::expected<TypeSymbol*, int> pt = arg->GetType()->RemoveReference(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* type = *pt;
            arg = new BoundDereferenceNode(arg, sourcePos, type);
        }
        if (argumentMatch.conversionFun)
        {
            TypeSymbol* argType = arg->GetType();
            FunctionSymbol* conversionFun = argumentMatch.conversionFun;
            if (conversionFun->GetConversionKind() == ConversionKind::explicitConversion && !context->GetFlag(ContextFlags::suppress_warning))
            {
                std::expected<std::u32string, int> afname = conversionFun->ConversionArgType()->FullName();
                if (!afname) return std::unexpected<int>(afname.error());
                std::expected<std::string, int> asfname = util::ToUtf8(*afname);
                if (!asfname) return std::unexpected<int>(asfname.error());
                std::expected<std::u32string, int> pfname = conversionFun->ConversionParamType()->FullName();
                if (!pfname) return std::unexpected<int>(pfname.error());
                std::expected<std::string, int> psfname = util::ToUtf8(*pfname);
                if (!psfname) return std::unexpected<int>(psfname.error());
                std::string warningMessage = "conversion from '" + *asfname + "' to '" + *psfname + "' without a cast";
                std::unexpected<int> w = Warning(warningMessage, sourcePos, context);
                functionMatch.warning = util::GetErrorMessage(w.error());
            }
            std::expected<TypeSymbol*, int> pt = argType->PlainType(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* plainType = *pt;
            if (conversionFun->GetFunctionKind() == FunctionKind::conversionMemFn && plainType->IsClassTypeSymbol())
            {
                if (argType->IsReferenceType())
                {
                    pt = argType->RemoveReference(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* type = *pt;
                    pt = type->AddPointer(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    type = *pt;
                    arg = new BoundRefToPtrNode(arg, sourcePos, type);
                }
                else
                {
                    pt = argType->GetBaseType()->AddPointer(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* type = *pt;
                    arg = new BoundAddressOfNode(arg, sourcePos, type);
                }
                BoundFunctionCallNode* functionCall = new BoundFunctionCallNode(conversionFun, sourcePos, conversionFun->ReturnType());
                functionCall->AddArgument(arg);
                arg = functionCall;
            }
            else if (conversionFun->GetFunctionKind() == FunctionKind::constructor)
            {
                std::expected<VariableSymbol*, int> trv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(conversionFun->ConversionParamType());
                if (!trv) return std::unexpected<int>(trv.error());
                VariableSymbol* temporary = *trv;
                BoundVariableNode* boundTemporary = new BoundVariableNode(temporary, sourcePos);
                BoundFunctionCallNode* constructorCall = new BoundFunctionCallNode(conversionFun, sourcePos, nullptr);
                pt = temporary->GetType()->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* ptrType = *pt;
                BoundAddressOfNode* temporaryArg = new BoundAddressOfNode(boundTemporary, sourcePos, ptrType);
                constructorCall->AddArgument(temporaryArg);
                if (argumentMatch.preConversionFlags == OperationFlags::addr)
                {
                    std::expected<BoundExpressionNode*, int> brv = MakeLvalueExpression(arg, sourcePos, context);
                    if (!brv) return std::unexpected<int>(brv.error());
                    pt = arg->GetType()->AddPointer(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* ptrType = *pt;
                    arg = new BoundAddressOfNode(*brv, sourcePos, ptrType);
                }
                else if (argumentMatch.preConversionFlags == OperationFlags::deref)
                {
                    pt = arg->GetType()->RemoveReference(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* type = *pt;
                    arg = new BoundDereferenceNode(arg, sourcePos, type);
                }
                constructorCall->AddArgument(arg);
                BoundExpressionNode* boundTemporary2 = new BoundVariableNode(temporary, sourcePos);
                if (argumentMatch.postConversionFlags == OperationFlags::addr)
                {
                    std::expected<BoundExpressionNode*, int> brv = MakeLvalueExpression(boundTemporary2, sourcePos, context);
                    if (!brv) return std::unexpected<int>(brv.error());
                    pt = boundTemporary2->GetType()->AddPointer(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* ptrType = *pt;
                    boundTemporary2 = new BoundAddressOfNode(*brv, sourcePos, ptrType);
                }
                else if (argumentMatch.postConversionFlags == OperationFlags::deref)
                {
                    pt = boundTemporary2->GetType()->RemoveReference(context);
                    if (!pt) return std::unexpected<int>(pt.error());
                    TypeSymbol* type = *pt;
                    boundTemporary2 = new BoundDereferenceNode(boundTemporary2, sourcePos, type);
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
            std::expected<BoundExpressionNode*, int> rv = MakeLvalueExpression(arg, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            std::expected<TypeSymbol*, int> pt = arg->GetType()->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* ptrType = *pt;
            arg = new BoundAddressOfNode(*rv, sourcePos, ptrType);
        }
        else if (argumentMatch.postConversionFlags == OperationFlags::deref)
        {
            std::expected<TypeSymbol*, int> pt = arg->GetType()->RemoveReference(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* type = *pt;
            arg = new BoundDereferenceNode(arg, sourcePos, type);
        }
        boundFunctionCall->AddArgument(arg);
    }
    return std::expected<std::unique_ptr<BoundFunctionCallNode>, int>(std::move(boundFunctionCall));
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

std::expected<bool, int> FindTemplateParameterMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!paramType->GetBaseType()->IsTemplateParameterSymbol()) return std::expected<bool, int>(false);
    TemplateParameterSymbol* templateParameter = static_cast<TemplateParameterSymbol*>(paramType->GetBaseType());
    TypeSymbol* templateArgumentType = nullptr;
    auto it = functionMatch.templateParameterMap.find(templateParameter);
    if (it == functionMatch.templateParameterMap.end())
    {
        std::expected<TypeSymbol*, int> rd = argType->RemoveDerivations(paramType->GetDerivations(), context);
        if (!rd) return std::unexpected<int>(rd.error());
        templateArgumentType = *rd;
        if (templateArgumentType)
        {
            functionMatch.templateParameterMap[templateParameter] = templateArgumentType;
        }
        else
        {
            return std::expected<bool, int>(false);
        }
    }
    else
    {
        templateArgumentType = it->second;
    }
    std::expected<TypeSymbol*, int> ud = paramType->Unify(templateArgumentType, context);
    if (!ud) return std::unexpected<int>(ud.error());
    paramType = *ud;
    if (!paramType)
    {
        return std::expected<bool, int>(false);
    }
    if (TypesEqual(argType, paramType, context))
    {
        ArgumentMatch argumentMatch;
        if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
        {
            argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
        }
        functionMatch.argumentMatches.push_back(argumentMatch);
        return std::expected<bool, int>(true);
    }
    else
    {
        bool qualificationConversionMatch = false;
        ArgumentMatch argumentMatch;
        std::expected<TypeSymbol*, int> pa = argType->PlainType(context);
        if (!pa) return std::unexpected<int>(pa.error());
        TypeSymbol* plainArgType = *pa;
        std::expected<TypeSymbol*, int> pt = paramType->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* plainParamType = *pt;
        if (TypesEqual(plainArgType, plainParamType, context))
        {
            qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return std::expected<bool, int>(true);
            }
        }
        else
        {
            std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* conversionFun = *arv;
            if (conversionFun)
            {
                ++functionMatch.numConversions;
                argumentMatch.conversionFun = conversionFun;
                if (argumentMatch.preConversionFlags == OperationFlags::none)
                {
                    if (FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch))
                    {
                        functionMatch.argumentMatches.push_back(argumentMatch);
                        return std::expected<bool, int>(true);
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
                else
                {
                    if (FindQualificationConversion(conversionFun->ConversionParamType(), paramType, arg, functionMatch, argumentMatch))
                    {
                        functionMatch.argumentMatches.push_back(argumentMatch);
                        return std::expected<bool, int>(true);
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
            }
        }
    }
    return std::expected<bool, int>(false);
}

std::expected<bool, int> FindClassTemplateMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
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
                return std::expected<bool, int>(false);
            }
            Symbol* targetArgumentSymbol = paramTemplateDeclaration->TemplateParameters()[i];
            TypeSymbol* targetArgumentType = nullptr;
            if (targetArgumentSymbol->IsTypeSymbol())
            {
                targetArgumentType = static_cast<TypeSymbol*>(targetArgumentSymbol);
            }
            else
            {
                return std::expected<bool, int>(false);
            }
            std::expected<bool, int> tpm = FindTemplateParameterMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
            if (!tpm) return tpm;
            if (*tpm)
            {
                continue;
            }
            else
            {
                std::expected<bool, int> ctm = FindClassTemplateMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
                if (!ctm) return ctm;
                if (*ctm)
                {
                    continue;
                }
                else
                {
                    std::expected<bool, int> spm = FindClassTemplateSpecializationMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
                    if (!spm) return spm;
                    if (*spm)
                    {
                        continue;
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
            }
        }
    }
    if (n == 0)
    {
        return std::expected<bool, int>(false);
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
            return std::expected<bool, int>(false);
        }
        std::expected<TypeSymbol*, int> ud = targetArgumentType->UnifyTemplateArgumentType(functionMatch.templateParameterMap, context);
        if (!ud) return std::unexpected<int>(ud.error());
        TypeSymbol* templateArgumentType = *ud;
        if (templateArgumentType)
        {
            targetTemplateArguments.push_back(templateArgumentType);
        }
        else
        {
            return std::expected<bool, int>(false);
        }
    }
    std::expected<ClassTemplateSpecializationSymbol*, int> sp = context->GetSymbolTable()->MakeClassTemplateSpecialization(paramClassType, targetTemplateArguments);
    if (!sp) return std::unexpected<int>(sp.error());
    TypeSymbol* plainTargetType = *sp;
    std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
    if (!c) return std::unexpected<int>(c.error());
    paramType = *c;
    if (TypesEqual(argType, paramType, context))
    {
        ArgumentMatch argumentMatch;
        if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
        {
            argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
        }
        functionMatch.argumentMatches.push_back(argumentMatch);
        return std::expected<bool, int>(true);
    }
    else
    {
        bool qualificationConversionMatch = false;
        ArgumentMatch argumentMatch;
        std::expected<TypeSymbol*, int> pt = argType->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* plainArgType = *pt;
        pt = paramType->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* plainParamType = *pt;
        if (TypesEqual(plainArgType, plainParamType, context))
        {
            qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
        }
        if (qualificationConversionMatch)
        {
            functionMatch.argumentMatches.push_back(argumentMatch);
            return std::expected<bool, int>(true);
        }
        else
        {
            std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* conversionFun = *arv;
            if (conversionFun)
            {
                ++functionMatch.numConversions;
                argumentMatch.conversionFun = conversionFun;
                if (argumentMatch.preConversionFlags == OperationFlags::none)
                {
                    if (FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch))
                    {
                        functionMatch.argumentMatches.push_back(argumentMatch);
                        return std::expected<bool, int>(true);
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
                else
                {
                    if (FindQualificationConversion(conversionFun->ConversionParamType(), paramType, arg, functionMatch, argumentMatch))
                    {
                        functionMatch.argumentMatches.push_back(argumentMatch);
                        return std::expected<bool, int>(true);
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
            }
        }
    }
    return std::expected<bool, int>(false);
}

std::expected<bool, int> PlainTemplateArgsEqual(const std::vector<Symbol*>& sourceTemplateArguments, const std::vector<Symbol*>& targetTemplateArguments, Context* context)
{
    int n = sourceTemplateArguments.size();
    int m = targetTemplateArguments.size();
    if (n != m) return false;
    for (int i = 0; i < n; ++i)
    {
        Symbol* sourceTemplateArg = sourceTemplateArguments[i];
        Symbol* targetTemplateArg = targetTemplateArguments[i];
        if (!sourceTemplateArg->IsTypeSymbol() || !targetTemplateArg->IsTypeSymbol()) return false;
        TypeSymbol* sourceType = static_cast<TypeSymbol*>(sourceTemplateArg);
        TypeSymbol* targetType = static_cast<TypeSymbol*>(targetTemplateArg);
        std::expected<TypeSymbol*, int> pt = sourceType->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* sourcePlainType = *pt;
        pt = targetType->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* targetPlainType = *pt;
        if (!TypesEqual(sourcePlainType, targetPlainType, context))
        {
            return std::expected<bool, int>(false);
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FindClassTemplateSpecializationMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!paramType->GetBaseType()->IsClassTypeSymbol()) return std::expected<bool, int>(false);
    ClassTypeSymbol* paramClassType = static_cast<ClassTypeSymbol*>(paramType->GetBaseType());
    ClassTemplateSpecializationSymbol* paramSpecializationType = nullptr;
    if (paramClassType->IsClassTemplateSpecializationSymbol())
    {
        paramSpecializationType = static_cast<ClassTemplateSpecializationSymbol*>(paramClassType);
    }
    else
    {
        return std::expected<bool, int>(false);
    }
    int n = paramSpecializationType->TemplateArguments().size();
    int numArgumentMatches = functionMatch.argumentMatches.size();
    std::vector<Symbol*> sourceTemplateArguments;
    if (argType->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* sourceClassTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(argType->GetBaseType());
        int m = sourceClassTemplateSpecialization->TemplateArguments().size();
        if (n != m) return std::expected<bool, int>(false);
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
                return std::expected<bool, int>(false);
            }
            Symbol* targetArgumentSymbol = paramSpecializationType->TemplateArguments()[i];
            TypeSymbol* targetArgumentType = nullptr;
            if (targetArgumentSymbol->IsTypeSymbol())
            {
                targetArgumentType = static_cast<TypeSymbol*>(targetArgumentSymbol);
            }
            else
            {
                return std::expected<bool, int>(false);
            }
            std::expected<bool, int> tpm = FindTemplateParameterMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
            if (!tpm) return tpm;
            if (*tpm)
            {
                continue;
            }
            else
            {
                std::expected<bool, int> ctm = FindClassTemplateMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
                if (!ctm) return ctm;
                if (*ctm)
                {
                    continue;
                }
                else
                {
                    std::expected<bool, int> spm = FindClassTemplateSpecializationMatch(sourceArgumentType, targetArgumentType, arg, functionMatch, sourcePos, context);
                    if (!spm) return spm;
                    if (*spm)
                    {
                        continue;
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
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
            std::expected<TypeSymbol*, int> ud = templateArgumentType->UnifyTemplateArgumentType(functionMatch.templateParameterMap, context);
            if (!ud) return std::unexpected<int>(ud.error());
            templateArgumentType = *ud;
            if (templateArgumentType)
            {
                targetTemplateArguments.push_back(templateArgumentType);
            }
            else
            {
                return std::expected<bool, int>(false);
            }
        }
        std::expected<ClassTemplateSpecializationSymbol*, int> sp = context->GetSymbolTable()->MakeClassTemplateSpecialization(
            paramSpecializationType->ClassTemplate(), targetTemplateArguments);
        if (!sp) return std::unexpected<int>(sp.error());
        TypeSymbol* plainTargetType = *sp;
        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
        if (!c) return std::unexpected<int>(c.error());
        TypeSymbol* compoundParamType = *c;
        if (TypesEqual(argType, compoundParamType, context))
        {
            ArgumentMatch argumentMatch;
            if (argType->IsClassTypeSymbol() && paramType->IsClassTypeSymbol())
            {
                argumentMatch.postConversionFlags = argumentMatch.postConversionFlags | OperationFlags::addr;
            }
            functionMatch.argumentMatches.push_back(argumentMatch);
            return std::expected<bool, int>(true);
        }
        else
        {
            ArgumentMatch argumentMatch;
            bool qualificationConversionMatch = false;
            std::expected<TypeSymbol*, int> pt = argType->PlainType(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* plainArgType = *pt;
            pt = compoundParamType->PlainType(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* plainParamType = *pt;
            if (TypesEqual(plainArgType, plainParamType, context))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch);
            }
            if (qualificationConversionMatch)
            {
                functionMatch.argumentMatches.push_back(argumentMatch);
                return std::expected<bool, int>(true);
            }
            else
            {
                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    compoundParamType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
                if (!arv) return std::expected<bool, int>(false);
                FunctionSymbol* conversionFun = *arv;
                if (conversionFun)
                {
                    ++functionMatch.numConversions;
                    argumentMatch.conversionFun = conversionFun;
                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                    {
                        if (FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            return std::expected<bool, int>(true);
                        }
                        else
                        {
                            return std::expected<bool, int>(false);
                        }
                    }
                    else
                    {
                        if (FindQualificationConversion(conversionFun->ConversionParamType(), compoundParamType, arg, functionMatch, argumentMatch))
                        {
                            functionMatch.argumentMatches.push_back(argumentMatch);
                            return std::expected<bool, int>(true);
                        }
                        else
                        {
                            return std::expected<bool, int>(false);
                        }
                    }
                }
                else
                {
                    bool plainTemplateArgsEqual = PlainTemplateArgsEqual(sourceTemplateArguments, targetTemplateArguments, context);
                    if (plainTemplateArgsEqual)
                    {
                        ++functionMatch.numConversions;
                        std::expected<ClassTemplateSpecializationSymbol*, int> sp = context->GetSymbolTable()->MakeClassTemplateSpecialization(
                            paramSpecializationType->ClassTemplate(), sourceTemplateArguments);
                        if (!sp) return std::unexpected<int>(sp.error());
                        plainTargetType = *sp;
                        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(plainTargetType, paramType->GetDerivations());
                        if (!c) return std::unexpected<int>(c.error());
                        compoundParamType = *c;
                        if (TypesEqual(argType, compoundParamType, context))
                        {
                            functionMatch.argumentMatches.push_back(ArgumentMatch());
                            return std::expected<bool, int>(true);
                        }
                        else
                        {
                            ArgumentMatch argumentMatch;
                            std::expected<TypeSymbol*, int> pt = argType->PlainType(context);
                            if (!pt) return std::unexpected<int>(pt.error());
                            TypeSymbol* plainArgType = *pt;
                            pt = compoundParamType->PlainType(context);
                            if (!pt) return std::unexpected<int>(pt.error());
                            TypeSymbol* plainParamType = *pt;
                            if (TypesEqual(plainArgType, plainParamType, context))
                            {
                                qualificationConversionMatch = FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch);
                            }
                            if (qualificationConversionMatch)
                            {
                                functionMatch.argumentMatches.push_back(argumentMatch);
                                return std::expected<bool, int>(true);
                            }
                            else
                            {
                                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                                    compoundParamType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
                                if (!arv) return std::expected<bool, int>(false);
                                FunctionSymbol* conversionFun = *arv;
                                if (conversionFun)
                                {
                                    ++functionMatch.numConversions;
                                    argumentMatch.conversionFun = conversionFun;
                                    if (argumentMatch.preConversionFlags == OperationFlags::none)
                                    {
                                        if (FindQualificationConversion(argType, compoundParamType, arg, functionMatch, argumentMatch))
                                        {
                                            functionMatch.argumentMatches.push_back(argumentMatch);
                                            return std::expected<bool, int>(true);
                                        }
                                        else
                                        {
                                            return std::expected<bool, int>(false);
                                        }
                                    }
                                    else
                                    {
                                        if (FindQualificationConversion(conversionFun->ConversionParamType(), compoundParamType, arg, functionMatch, argumentMatch))
                                        {
                                            functionMatch.argumentMatches.push_back(argumentMatch);
                                            return std::expected<bool, int>(true);
                                        }
                                        else
                                        {
                                            return std::expected<bool, int>(false);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        return std::expected<bool, int>(false);
                    }
                }
            }
        }
    }
    return std::expected<bool, int>(false);
}

std::expected<bool, int> FindConversions(FunctionMatch& functionMatch, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    int arity = static_cast<int>(args.size());
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
            if (!functionMatch.function->Valid()) return std::unexpected<int>(functionMatch.function->GetError());
            if (parameter->DefaultValue())
            {
                std::expected<bool, int> rv = context->GetSymbolTable()->CurrentScope()->PushParentScope(functionMatch.function->GetScope());
                if (!rv) return rv;
                std::expected<BoundExpressionNode*, int> erv = BindExpression(parameter->DefaultValue(), context);
                if (!erv) return std::unexpected<int>(erv.error());
                defaultArg.reset(*erv);
                rv = context->GetSymbolTable()->CurrentScope()->PopParentScope();
                if (!rv) return rv;
                arg = defaultArg.get();
                std::expected<TypeSymbol*, int> dt = arg->GetType()->DirectType(context);
                if (!dt) return std::unexpected<int>(dt.error());
                TypeSymbol* directType = *dt;
                std::expected<TypeSymbol*, int> frv = directType->FinalType(sourcePos, context);
                if (!frv) return std::unexpected<int>(frv.error());
                argType = *frv;
                functionMatch.defaultArgs.push_back(std::move(defaultArg));
            }
            else
            {
                return std::expected<bool, int>(false);
            }
        }
        else
        {
            arg = args[i].get();
            argType = arg->GetType();
        }
        ParameterSymbol* parameter = functionMatch.function->MemFunParameters(context)[i];
        if (!functionMatch.function->Valid()) return std::unexpected<int>(functionMatch.function->GetError());
        context->PushSetFlag(ContextFlags::resolveDependentTypes | ContextFlags::resolveNestedTypes);
        context->PushTemplateParameterMap(&functionMatch.templateParameterMap);
        context->SetSourcePos(sourcePos);
        std::expected<TypeSymbol*, int> rrv = parameter->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        TypeSymbol* referredType = *rrv;
        rrv = referredType->FinalType(sourcePos, context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        TypeSymbol* paramType = *rrv;
        context->PopTemplateParameterMap();
        context->PopFlags();
        if (TypesEqual(argType, paramType, context))
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
            std::expected<TypeSymbol*, int> pt = argType->PlainType(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* plainArgType = *pt;
            pt = paramType->PlainType(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* plainParamType = *pt;
            if (TypesEqual(plainArgType, plainParamType, context))
            {
                qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
                if (qualificationConversionMatch)
                {
                    functionMatch.argumentMatches.push_back(argumentMatch);
                }
            }
            if (!qualificationConversionMatch)
            {
                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    paramType, argType, arg, sourcePos, argumentMatch, functionMatch, context);
                if (!arv) return std::unexpected<int>(arv.error());
                FunctionSymbol* conversionFun = *arv;
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
                            return std::expected<bool, int>(false);
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
                            return std::expected<bool, int>(false);
                        }
                    }
                }
                else
                {
                    if (functionMatch.function->IsTemplate() || functionMatch.function->IsMemFnOfClassTemplate())
                    {
                        std::expected<bool, int> tpm = FindTemplateParameterMatch(argType, paramType, arg, functionMatch, sourcePos, context);
                        if (!tpm) return tpm;
                        if (*tpm)
                        {
                            continue;
                        }
                        else
                        {
                            std::expected<bool, int> ctm = FindClassTemplateMatch(argType, paramType, arg, functionMatch, sourcePos, context);
                            if (!ctm) return ctm;
                            if (*ctm)
                            {
                                continue;
                            }
                            else
                            {
                                std::expected<bool, int> spm = FindClassTemplateSpecializationMatch(argType, paramType, arg, functionMatch, sourcePos, context);
                                if (!spm) return spm;
                                if (*spm)
                                {
                                    continue;
                                }
                            }
                        }
                    }
                }
                return std::expected<bool, int>(false);
            }
        }
    }
    return std::expected<bool, int>(true);
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

std::expected<std::unique_ptr<FunctionMatch>, int> SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, 
    const std::vector<TypeSymbol*>& templateArgs, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, const std::u32string& groupName, 
    const soul::ast::SourcePos& sourcePos, Context* context)
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
        std::expected<std::u32string, int> fname = viableFunction->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        if (viableFunction->IsFunctionDefinitionSymbol() && viableFunctionFullNameSet.find(*fname) != viableFunctionFullNameSet.end())
        {
            continue;
        }
        viableFunctionSet.insert(viableFunction);
        if (viableFunction->IsFunctionDefinitionSymbol())
        {
            viableFunctionFullNameSet.insert(*fname);
        }
        std::unique_ptr<FunctionMatch> functionMatch(new FunctionMatch(viableFunction, context));
        SetTemplateArgs(viableFunction, functionMatch->templateParameterMap, templateArgs);
/*
        auto sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << *sfname << "\n";
*/
        std::expected<bool, int> crv = FindConversions(*functionMatch, args, sourcePos, context);
        if (!crv) return std::unexpected<int>(crv.error());
        if (*crv)
        {
            functionMatches.push_back(std::move(functionMatch));
        }
    }
    if (functionMatches.size() == 1)
    {
        return std::expected<std::unique_ptr<FunctionMatch>, int>(std::move(functionMatches.front()));
    }
    else if (functionMatches.size() > 1)
    {
        std::insertion_sort(functionMatches.begin(), functionMatches.end(), BetterFunctionMatch());
        if (BetterFunctionMatch()(functionMatches[0], functionMatches[1]))
        {
            return std::expected<std::unique_ptr<FunctionMatch>, int>(std::move(functionMatches.front()));
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
                std::expected<std::u32string, int> fname = functionMatch->function->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname) return std::unexpected<int>(sfname.error());
                message.append(*sfname);
            }
            return Error(message, sourcePos, context);
        }
    }
    else
    {
        std::expected<std::string, int> sgroupName = util::ToUtf8(groupName);
        if (!sgroupName) return std::unexpected<int>(sgroupName.error());
        return Error("overload resolution failed: overload in function group '" + *sgroupName + "' not found, " +
            "or there are no acceptable conversions for all argument types. " + std::to_string(viableFunctions.size()) + " viable functions examined.", sourcePos, context);
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

std::expected<bool, int> MakeFinalDirectArgs(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    for (auto& arg : args)
    {
        std::expected<bool, int> rv = arg->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, FunctionMatch& functionMatch,
    OverloadResolutionFlags flags)
{
    std::expected<bool, int> rv = MakeFinalDirectArgs(args, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::vector<FunctionSymbol*> viableFunctions;
    if (groupName == U"@destructor")
    {
        if (args.size() == 1)
        {
            BoundExpressionNode* arg = args[0].get();
            if (arg->GetType()->GetBaseType()->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(arg->GetType()->GetBaseType());
                std::expected<Symbol*, int> drv = GenerateDestructor(specialization, sourcePos, context);
                if (!drv) return std::unexpected<int>(drv.error());
                Symbol* destructor = *drv;
                viableFunctions.push_back(static_cast<FunctionSymbol*>(destructor));
            }
        }
    }
    context->PushSetFlag(ContextFlags::ignoreClassTemplateSpecializations);
    std::expected<FunctionSymbol*, int> orv = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
    if (!orv) return std::unexpected<int>(orv.error());
    FunctionSymbol* operation = *orv;
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
        bool flagsPushed = false;
        if ((flags & OverloadResolutionFlags::noMemberFunctions) != OverloadResolutionFlags::none)
        {
            context->PushSetFlag(ContextFlags::skipNonstaticMemberFunctions);
            flagsPushed = true;
        }
        std::expected<bool, int> m = context->GetSymbolTable()->CollectViableFunctions(scopeLookups, groupName, templateArgs, 
            static_cast<int>(args.size()), viableFunctions, context);
        if (!m) return std::unexpected<int>(m.error());
        if (flagsPushed)
        {
            context->PopFlags();
        }
    }
    std::expected<std::unique_ptr<FunctionMatch>, int> brv = SelectBestMatchingFunction(viableFunctions, templateArgs, args, groupName, sourcePos, context);
    if (!brv) return std::unexpected<int>(brv.error());
    std::unique_ptr<FunctionMatch> bestMatch = std::move(*brv);
    if (!bestMatch.get())
    {
        context->ResetFlag(ContextFlags::ignoreClassTemplateSpecializations);
        std::expected<FunctionSymbol*, int> orv = context->GetOperationRepository()->GetOperation(groupName, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        FunctionSymbol* operation = *orv;
        if (operation)
        {
            viableFunctions.clear();
            viableFunctions.push_back(operation);
            brv = SelectBestMatchingFunction(viableFunctions, templateArgs, args, groupName, sourcePos, context);
            if (!brv) return std::unexpected<int>(brv.error());
            bestMatch = move(*brv);
        }
        if (!bestMatch.get())
        {
            return std::expected<std::unique_ptr<BoundFunctionCallNode>, int>(std::unique_ptr<BoundFunctionCallNode>());
        }
    }
    if ((bestMatch->function->Qualifiers() & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
    {
        return Error("attempt to call a deleted function", sourcePos, context);
    }
    context->ResetFlag(ContextFlags::noPtrOps);
    functionMatch = *bestMatch;
    bool instantiate = (flags & OverloadResolutionFlags::dontInstantiate) == OverloadResolutionFlags::none;
    if (instantiate)
    {
        if (bestMatch->function->IsTemplate())
        {
            std::expected<FunctionSymbol*, int> irv = InstantiateFunctionTemplate(bestMatch->function, bestMatch->templateParameterMap, sourcePos, context);
            if (!irv) return std::unexpected<int>(irv.error());
            bestMatch->function = *irv;
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
            std::expected<FunctionSymbol*, int> irv = InstantiateMemFnOfClassTemplate(bestMatch->function, classTemplateSpecialization, 
                bestMatch->templateParameterMap, sourcePos, context);
            if (!irv) return std::unexpected<int>(irv.error());
            bestMatch->function = *irv;
        }
        else if (bestMatch->function->IsInline() && context->ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining))
        {
            std::expected<FunctionSymbol*, int> irv = InstantiateInlineFunction(bestMatch->function, sourcePos, context);
            if (!irv) return std::unexpected<int>(irv.error());
            bestMatch->function = *irv;
        }
    }
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> boundFunctionCall = CreateBoundFunctionCall(*bestMatch, args, sourcePos, context);
    return boundFunctionCall;
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags)
{
    FunctionMatch functionMatch;
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, functionMatch, flags);
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, FunctionMatch& functionMatch)
{
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, functionMatch, OverloadResolutionFlags::none);
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    FunctionMatch functionMatch;
    return ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, functionMatch, OverloadResolutionFlags::none);
}

} // namespace otava::symbols
