// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.statement.binder;

import otava.ast.statement;
import otava.ast.function;
import otava.ast.declaration;
import otava.ast.type;
import otava.ast.classes;
import otava.ast.identifier;
import otava.ast.expression;
import otava.ast.qualifier;
import otava.ast.templates;
import otava.ast.literal;
import otava.symbols.argument.conversion.table;
import otava.symbols.bound.tree;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.declarator;
import otava.symbols.declaration;
import otava.symbols.error;
import otava.symbols.expression.binder;
import otava.symbols.function.kind;
import otava.symbols.function_return_path_checker;
import otava.symbols.overload.resolution;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.class_templates;
import otava.symbols.instantiator;
import otava.symbols.declaration;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.conversion.table;
import otava.symbols.type_compare;
import otava.symbols.alias.type.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.operation.repository;
import otava.symbols.type.resolver;
import util.sha1;
import util.unicode;

namespace otava::symbols {

struct InitializerLess
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool InitializerLess::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, 
    const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first < right.first;
}

struct TerminatorGreater
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool TerminatorGreater::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, 
    const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first > right.first;
}

constexpr int maxBaseInitializers = 10000;

std::expected<BoundExpressionNode*, int> MakeBoundBooleanConversionNode(BoundExpressionNode* condition, Context* context)
{
    soul::ast::SourcePos sourcePos = condition->GetSourcePos();
    std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    FunctionSymbol* conversionFunction = *arv;
    if (!conversionFunction)
    {
        return Error("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
    }
    std::expected<TypeSymbol*, int> pt = condition->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (conversionFunction->GetFunctionKind() == FunctionKind::conversionMemFn && plainType->IsClassTypeSymbol())
    {
        TypeSymbol* conditionType = condition->GetType();
        if (conditionType->IsReferenceType())
        {
            std::expected<TypeSymbol*, int> pt = conditionType->RemoveReference(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* type = *pt;
            pt = type->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            type = *pt;
            condition = new BoundRefToPtrNode(condition, sourcePos, type);
        }
        else
        {
            std::expected<TypeSymbol*, int> pt = conditionType->GetBaseType()->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* type = *pt;
            condition = new BoundAddressOfNode(condition, sourcePos, type);
        }
        BoundFunctionCallNode* functionCall = new BoundFunctionCallNode(conversionFunction, sourcePos, conversionFunction->ReturnType());
        functionCall->AddArgument(condition);
        return functionCall;
    }
    return std::expected<BoundExpressionNode*, int>(new BoundConversionNode(condition, conversionFunction, sourcePos));
}

std::expected<BoundFunctionCallNode*, int> MakeDestructorCall(ClassTypeSymbol* cls, BoundExpressionNode* arg, FunctionDefinitionSymbol* destructor,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* dtorSymbol = nullptr;
    if (destructor)
    {
        dtorSymbol = destructor;
    }
    else
    {
        std::expected<Symbol*, int> rv = GenerateDestructor(cls, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        dtorSymbol = *rv;
    }
    if (dtorSymbol && (dtorSymbol->IsFunctionSymbol() || dtorSymbol->IsExplicitlyInstantiatedFunctionDefinitionSymbol()))
    {
        FunctionSymbol* dtorFunctionSymbol = static_cast<FunctionSymbol*>(dtorSymbol);
        if (dtorFunctionSymbol->GetFlag(FunctionSymbolFlags::trivialDestructor))
        {
            return std::expected<BoundFunctionCallNode*, int>(static_cast<BoundFunctionCallNode*>(nullptr));
        }
        std::expected<std::string, int> rv = dtorSymbol->IrName(context);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string dtorIrName = *rv;
        std::unique_ptr<BoundFunctionCallNode> destructorCall(new BoundFunctionCallNode(dtorFunctionSymbol, sourcePos, cls));
        destructorCall->AddArgument(arg->Clone());
        return std::expected<BoundFunctionCallNode*, int>(destructorCall.release());
    }
    return std::expected<BoundFunctionCallNode*, int>(static_cast<BoundFunctionCallNode*>(nullptr));
}

StatementBinder::StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) :
    context(context_),
    currentClass(nullptr),
    ctorInitializer(nullptr),
    dtorTerminator(nullptr),
    boundStatement(nullptr),
    functionDefinitionSymbol(functionDefinitionSymbol_),
    classTypeSymbol(nullptr),
    memberVariableSymbol(nullptr),
    resolveClass(false),
    resolveMemberVariable(false),
    resolveInitializerArguments(false),
    setVPtrStatementsGenerated(false),
    postfix(false),
    globalStaticVariableSymbol(nullptr)
{
}

void StatementBinder::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (!Valid()) return;
    std::expected<Symbol*, int> s = context->GetSymbolTable()->GetSymbol(&node);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    Symbol* symbol = *s;
    std::expected<SpecialFunctionKind, int> sp = functionDefinitionSymbol->GetSpecialFunctionKind(context);
    if (!sp)
    {
        SetError(sp.error());
        return;
    }
    SpecialFunctionKind specialFunctionKind = *sp;
    switch (specialFunctionKind)
    {
        case SpecialFunctionKind::defaultCtor:
        case SpecialFunctionKind::copyCtor:
        case SpecialFunctionKind::moveCtor:
        {
            functionDefinitionSymbol->SetFunctionKind(FunctionKind::constructor);
            break;
        }
        case SpecialFunctionKind::dtor:
        {
            functionDefinitionSymbol->SetFunctionKind(FunctionKind::destructor);
            break;
        }
    }
    if (node.FunctionBody()->IsDefaultedOrDeletedFunctionNode())
    {
        otava::ast::DefaultedOrDeletedFunctionNode* bodyNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
        if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::defaultNode)
        {
            functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::isDefault);
            ClassTypeSymbol* classType = symbol->ParentClassType();
            if (classType)
            {
                switch (specialFunctionKind)
                {
                    case SpecialFunctionKind::defaultCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        std::expected<FunctionDefinitionSymbol*, int> rv = GenerateClassDefaultCtor(classType, node.GetSourcePos(), context);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        functionDefinitionSymbol = *rv;
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        std::expected<FunctionDefinitionSymbol*, int> rv = GenerateClassCopyCtor(classType, node.GetSourcePos(), context);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        functionDefinitionSymbol = *rv;
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        std::expected<FunctionDefinitionSymbol*, int> rv = GenerateClassMoveCtor(classType, node.GetSourcePos(), context);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        functionDefinitionSymbol = *rv;
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        std::expected<FunctionDefinitionSymbol*, int> rv = GenerateClassCopyAssignment(classType, node.GetSourcePos(), context);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        functionDefinitionSymbol = *rv;
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        std::expected<FunctionDefinitionSymbol*, int> rv = GenerateClassMoveAssignment(classType, node.GetSourcePos(), context);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        functionDefinitionSymbol = *rv;
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                }
                BoundFunctionNode* boundFunction = context->ReleaseBoundFunction();
                std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(boundFunction), context);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                context->PopBoundFunction();
            }
        }
        else if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::deleteNode)
        {
            functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::isDeleted);
        }
        return;
    }
    currentClass = symbol->ParentClassType();
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(symbol->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    node.FunctionBody()->Accept(*this);
    if (!Valid()) return;
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor)
    {
        currentClass->SetHasUserDefinedConstructor();
        if (!ctorInitializer)
        {
            std::expected<bool, int> rv = GenerateDefaultCtorInitializer(node.GetSourcePos());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
    else if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::destructor)
    {
        currentClass->SetHasUserDefinedDestructor();
        std::expected<bool, int> rv = GenerateDestructorTerminator(node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = functionDefinitionSymbol->CheckGenerateClassCopyCtor(node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::ConstructorNode& node)
{
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    if (ctorInitializer)
    {
        context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
    }
    node.Right()->Accept(*this);
    if (!Valid()) return;
    context->GetBoundFunction()->SetBody(static_cast<BoundCompoundStatementNode*>(boundStatement));
    std::expected<bool, int> rv = AddConvertingConstructorToConversionTable(functionDefinitionSymbol, node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::ConstructorInitializerNode& node)
{
    if (!Valid()) return;
    ctorInitializer = new BoundCtorInitializerNode(node.GetSourcePos());
    node.GetMemberInitializerListNode()->Accept(*this);
}

std::expected<bool, int> StatementBinder::GenerateDefaultCtorInitializer(const soul::ast::SourcePos& sourcePos)
{
    ctorInitializer = new BoundCtorInitializerNode(sourcePos);
    std::expected<bool, int> rv = CompleteBaseInitializers(sourcePos);
    if (!rv) return rv;
    std::insertion_sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    rv = GenerateSetVPtrStatements(sourcePos);
    if (!rv) return rv;
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    rv = CompleteMemberInitializers(sourcePos);
    if (!rv) return rv;
    std::insertion_sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
    context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::GenerateDestructorTerminator(const soul::ast::SourcePos& sourcePos)
{
    dtorTerminator = new BoundDtorTerminatorNode(sourcePos);
    std::expected<bool, int> rv = GenerateSetVPtrStatements(sourcePos);
    if (!rv) return rv;
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        dtorTerminator->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    rv = GenerateBaseTerminators(sourcePos);
    if (!rv) return rv;
    rv = GenerateMemberTerminators(sourcePos);
    if (!rv) return rv;
    std::insertion_sort(memberTerminators.begin(), memberTerminators.end(), TerminatorGreater());
    for (auto& terminator : memberTerminators)
    {
        dtorTerminator->AddMemberTerminator(terminator.second.release());
    }
    context->GetBoundFunction()->SetDtorTerminator(dtorTerminator);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::GenerateBaseTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (ClassTypeSymbol* baseClass : currentClass->BaseClasses())
        {
            int index = GetBaseInitializerOrTerminatorIndex(baseClass);
            std::expected<bool, int> rv = AddBaseTerminator(baseClass, index, sourcePos);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::AddBaseTerminator(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(sourcePos);
    if (!tp) return std::unexpected<int>(tp.error());
    BoundExpressionNode* thisPtr = *tp;
    OperationFlags preConversionFlags = OperationFlags::none;
    std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* ptrType = *pt;
    std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        ptrType, thisPtr->GetType(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    FunctionSymbol* conversion = *rv;
    if (conversion)
    {
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> terminator = std::move(*orv);
        memberTerminators.push_back(std::make_pair(std::move(index), std::move(terminator)));
    }
    else
    {
        return Error("base class conversion not found", sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::GenerateMemberTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (VariableSymbol* mermberVar : currentClass->MemberVariables())
        {
            std::expected<bool, int> rv = AddMemberTerminator(mermberVar, sourcePos);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::AddMemberTerminator(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    TypeSymbol* memberVarType = memberVar->GetType();
    if (memberVarType->IsPointerType() || memberVarType->IsReferenceType()) return std::expected<bool, int>(true);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(sourcePos);
    if (!tp) return std::unexpected<int>(tp.error());
    BoundExpressionNode* thisPtr = *tp;
    boundVariableNode->SetThisPtr(thisPtr);
    std::expected<TypeSymbol*, int> pt = boundVariableNode->GetType()->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* ptrType = *pt;
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, ptrType)));
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
    if (!orv) return std::unexpected<int>(orv.error());
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
    memberTerminators.push_back(std::make_pair(std::move(memberVar->Index()), std::move(boundFunctionCall)));
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::GenerateSetVPtrStatements(const soul::ast::SourcePos& sourcePos)
{
    if (!currentClass || !currentClass->IsPolymorphic() || setVPtrStatementsGenerated) return std::expected<bool, int>(false);
    if (HasThisInitializer()) return std::expected<bool, int>(false);
    std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(currentClass, sourcePos, context);
    if (!rv) return rv;
    setVPtrStatementsGenerated = true;
    if (!currentClass->ObjectLayoutComputed())
    {
        rv = currentClass->MakeObjectLayout(sourcePos, context);
        if (!rv) return rv;
    }
    std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(sourcePos);
    if (!tp) return std::unexpected<int>(tp.error());
    BoundExpressionNode* thisPtr = *tp;
    std::vector<ClassTypeSymbol*> vptrHolderClasses = currentClass->VPtrHolderClasses();
    if (vptrHolderClasses.empty())
    {
        std::expected<std::u32string, int> fname = currentClass->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
    }
    for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
    {
        if (vptrHolderClass != currentClass)
        {
            std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* ptrType = *pt;
            std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                ptrType, thisPtr->GetType(), sourcePos, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* conversion = *arv;
            if (conversion)
            {
                BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr->Clone(), conversion, sourcePos);
                setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(
                    new BoundSetVPtrStatementNode(thisPtrConverted, currentClass, vptrHolderClass, sourcePos)));
            }
            else
            {
                return Error("vptr holder class conversion not found", sourcePos, context);
            }
        }
        else
        {
            setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(new BoundSetVPtrStatementNode(thisPtr->Clone(), currentClass, currentClass, sourcePos)));
        }
    }
    return std::expected<bool, int>(true);
}

void StatementBinder::Visit(otava::ast::MemberInitializerListNode& node)
{
    if (!Valid()) return;
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* initializer = node.Items()[i];
        initializer->Accept(*this);
        if (!Valid()) return;
    }
    std::expected<bool, int> rv = CompleteBaseInitializers(node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::insertion_sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    rv = GenerateSetVPtrStatements(node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    rv = CompleteMemberInitializers(node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::insertion_sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
}

std::expected<bool, int> StatementBinder::CompleteMemberInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return std::expected<bool, int>(true);
        for (VariableSymbol* memberVar : currentClass->MemberVariables())
        {
            int index = memberVar->Index();
            bool found = false;
            for (const auto& memberInitilizer : memberInitializers)
            {
                if (memberInitilizer.first == index)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                std::expected<bool, int> rv = AddDefaultMemberInitializer(memberVar, sourcePos);
                if (!rv) return rv;
            }
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::AddDefaultMemberInitializer(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(sourcePos);
    if (!tp) return std::unexpected<int>(tp.error());
    BoundExpressionNode* thisPtr = *tp;
    boundVariableNode->SetThisPtr(thisPtr);
    std::vector<TypeSymbol*> templateArgs;
    std::expected<TypeSymbol*, int> pt = boundVariableNode->GetType()->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* ptrType = *pt;
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, ptrType)));
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
    if (!orv) return std::unexpected<int>(orv.error());
    memberInitializers.push_back(std::make_pair(std::move(memberVar->Index()), std::move(*orv)));
    return std::expected<bool, int>(true);
}

int StatementBinder::GetBaseInitializerOrTerminatorIndex(TypeSymbol* baseClass) const
{
    int n = currentClass->BaseClasses().size();
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* baseCls = currentClass->BaseClasses()[i];
        if (TypesEqual(baseCls, baseClass, context))
        {
            return i - maxBaseInitializers;
        }
    }
    return -1;
}

std::expected<bool, int> StatementBinder::CompleteBaseInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return std::expected<bool, int>(true);
        for (ClassTypeSymbol* baseClass : currentClass->BaseClasses())
        {
            int index = GetBaseInitializerOrTerminatorIndex(baseClass);
            bool found = false;
            for (const auto& baseInitializer : baseInitializers)
            {
                if (baseInitializer.first == index)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                std::expected<bool, int> rv = AddDefaultBaseInitializer(baseClass, index, sourcePos);
                if (!rv) return rv;
            }
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StatementBinder::AddDefaultBaseInitializer(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(sourcePos);
    if (!tp) return std::unexpected<int>(tp.error());
    BoundExpressionNode* thisPtr = *tp;
    std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* ptrType = *pt;
    std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        ptrType, thisPtr->GetType(), sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    FunctionSymbol* conversion = *arv;
    if (conversion)
    {
        std::vector<TypeSymbol*> templateArgs;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
            context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        baseInitializers.push_back(std::make_pair(std::move(index), std::move(*orv)));
    }
    else
    {
        return Error("base class conversion not found", sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

void StatementBinder::Visit(otava::ast::MemberInitializerNode& node)
{
    if (!Valid()) return;
    initializerArgs.clear();
    classTypeSymbol = nullptr;
    memberVariableSymbol = nullptr;
    int index = -1;
    resolveClass = true;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    resolveClass = false;
    if (classTypeSymbol)
    {
        std::expected<BoundExpressionNode*, int> tp = context->GetThisPtr(node.GetSourcePos());
        if (!tp)
        {
            SetError(tp.error());
            return;
        }
        BoundExpressionNode* thisPtr = *tp;
        std::expected<TypeSymbol*, int> pt = classTypeSymbol->AddPointer(context);
        if (!pt)
        {
            SetError(pt.error());
            return;
        }
        TypeSymbol* ptrType = *pt;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            ptrType, thisPtr->GetType(), node.GetSourcePos(), context);
        if (!arv)
        {
            SetError(arv.error());
            return;
        }
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, node.GetSourcePos())));
        }
        else
        {
            std::unexpected<int> result = Error("base class conversion not found", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
        index = GetBaseInitializerOrTerminatorIndex(classTypeSymbol);
    }
    else
    {
        resolveMemberVariable = true;
        node.Left()->Accept(*this);
        if (!Valid()) return;
        resolveMemberVariable = false;
        initializerArgs.clear();
        if (memberVariableSymbol)
        {
            BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVariableSymbol, node.GetSourcePos());
            std::expected<ParameterSymbol*, int> tp = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(context);
            if (!tp)
            {
                SetError(tp.error());
                return;
            }
            ParameterSymbol* thisParam = *tp;
            BoundParameterNode* thisPtr = new BoundParameterNode(thisParam, node.GetSourcePos(), thisParam->GetType());
            boundVariableNode->SetThisPtr(thisPtr);
            std::expected<TypeSymbol*, int> pt = boundVariableNode->GetType()->AddPointer(context);
            if (!pt)
            {
                SetError(pt.error());
                return;
            }
            TypeSymbol* ptrType = *pt;
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(
                new BoundDefaultInitNode(boundVariableNode, node.GetSourcePos()), node.GetSourcePos(), ptrType)));
            index = memberVariableSymbol->Index();
        }
    }
    resolveInitializerArguments = true;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    resolveInitializerArguments = false;
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, initializerArgs, node.GetSourcePos(), context);
    if (!orv)
    {
        SetError(orv.error());
        return;
    }
    if (index < 0)
    {
        baseInitializers.push_back(std::make_pair(std::move(index), std::move(*orv)));
    }
    else
    {
        memberInitializers.push_back(std::make_pair(std::move(index), std::move(*orv)));
    }
}

void StatementBinder::Visit(otava::ast::TemplateIdNode& node)
{
    if (resolveClass)
    {
        std::expected<TypeSymbol*, int> trv = ResolveType(&node, DeclarationFlags::none, context, TypeResolverFlags::none);
        if (!trv)
        {
            SetError(trv.error());
            return;
        }
        TypeSymbol* type = *trv;
        if (type && type->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(type);
        }
    }
}

void StatementBinder::Visit(otava::ast::IdentifierNode& node)
{
    if (resolveClass)
    {
        std::expected<Symbol*, int> lrv = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
        if (!lrv)
        {
            SetError(lrv.error());
            return;
        }
        Symbol* symbol = *lrv;
        if (symbol && symbol->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
        }
    }
    else if (resolveMemberVariable)
    {
        std::expected<Symbol*, int> lrv = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::variableSymbolGroup, node.GetSourcePos(), context);
        if (!lrv)
        {
            SetError(lrv.error());
            return;
        }
        Symbol* symbol = *lrv;
        if (symbol && symbol->IsMemberVariableSymbol())
        {
            memberVariableSymbol = static_cast<VariableSymbol*>(symbol);
        }
    }
}

void StatementBinder::Visit(otava::ast::ExpressionListNode& node)
{
    if (resolveInitializerArguments)
    {
        int n = node.Items().size();
        for (int i = 0; i < n; ++i)
        {
            otava::ast::Node* item = node.Items()[i];
            std::expected<BoundExpressionNode*, int> brv = BindExpression(item, context);
            if (!brv)
            {
                SetError(brv.error());
                return;
            }
            BoundExpressionNode* arg = *brv;
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(arg));
        }
    }
}

void StatementBinder::Visit(otava::ast::FunctionBodyNode& node)
{
    node.Child()->Accept(*this);
    context->GetBoundFunction()->SetBody(static_cast<BoundCompoundStatementNode*>(boundStatement));
}

void StatementBinder::Visit(otava::ast::CompoundStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    BoundCompoundStatementNode* currentCompoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
    }
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor && !setVPtrStatementsGenerated)
    {
        rv = GenerateSetVPtrStatements(node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (auto& setVPtrStatement : setVPtrStatements)
        {
            currentCompoundStatement->AddStatement(setVPtrStatement.release());
        }
        setVPtrStatements.clear();
    }
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* statementNode = node.Nodes()[i];
        std::expected<BoundStatementNode*, int> bs = BindStatement(statementNode, functionDefinitionSymbol, context);
        if (!bs)
        {
            SetError(bs.error());
            return;
        }
        BoundStatementNode* boundStatement = *bs;
        if (boundStatement)
        {
            currentCompoundStatement->AddStatement(boundStatement);
        }
    }
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    SetStatement(currentCompoundStatement);
}

bool StatementBinder::HasThisInitializer() const
{
    for (const auto& baseInit : baseInitializers)
    {
        if (baseInit.first == -1) return true;
    }
    for (const auto& memberInit : memberInitializers)
    {
        if (memberInit.first == -1) return true;
    }
    return false;
}

void StatementBinder::Visit(otava::ast::IfStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    BoundIfStatementNode* boundIfStatement = new BoundIfStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        std::expected<BoundStatementNode*, int> bs = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (!bs)
        {
            SetError(bs.error());
            return;
        }
        BoundStatementNode* boundInitStatement = *bs;
        if (boundInitStatement)
        {
            boundIfStatement->SetInitStatement(boundInitStatement);
        }
    }

    context->PushResetFlag(ContextFlags::returnRef);
    std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Condition(), context);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    BoundExpressionNode* condition = *brv;
    if (condition->GetType()->IsReferenceType())
    {
        condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
    }
    if (!condition->GetType()->IsBoolType())
    {
        std::expected<BoundExpressionNode*, int> rv = MakeBoundBooleanConversionNode(condition, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        condition = *rv;
    }
    context->PopFlags();
    boundIfStatement->SetCondition(condition);
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.ThenStatement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundThenStatement = *bs;
    if (boundThenStatement)
    {
        boundIfStatement->SetThenStatement(boundThenStatement);
    }
    if (node.ElseStatement())
    {
        std::expected<BoundStatementNode*, int> bs = BindStatement(node.ElseStatement(), functionDefinitionSymbol, context);
        if (!bs)
        {
            SetError(bs.error());
            return;
        }
        BoundStatementNode* boundElseStatement = *bs;
        if (boundElseStatement)
        {
            boundIfStatement->SetElseStatement(boundElseStatement);
        }
    }
    SetStatement(boundIfStatement);
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::SwitchStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    BoundSwitchStatementNode* boundSwitchStatement = new BoundSwitchStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        std::expected<BoundStatementNode*, int> bs = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (!bs)
        {
            SetError(bs.error());
            return;
        }
        BoundStatementNode* boundInitStatement = *bs;
        if (boundInitStatement)
        {
            boundSwitchStatement->SetInitStatement(boundInitStatement);
        }
    }
    context->PushResetFlag(ContextFlags::returnRef);
    std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Condition(), context);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    BoundExpressionNode* condition = *brv;
    boundSwitchStatement->SetCondition(condition);
    context->PopFlags();
    context->PushSwitchCondType(condition->GetType());
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    context->PopSwitchCondType();
    if (boundStmt)
    {
        boundSwitchStatement->SetStatement(boundStmt);
    }
    SetStatement(boundSwitchStatement);
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::CaseStatementNode& node)
{
    if (!TerminatesCaseOrDefault(node.Statement()))
    {
        std::unexpected<int> warning = Warning("case statement does not terminate in return, break or continue statement", node.GetSourcePos(), context);
        std::cout << util::GetErrorMessage(warning.error()) << "\n";
    }
    std::expected<BoundExpressionNode*, int> brv = BindExpression(node.CaseExpression(), context);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    BoundExpressionNode* caseExpr = *brv;
    TypeSymbol* switchCondType = context->GetSwitchCondType();
    if (!TypesEqual(caseExpr->GetType(), switchCondType, context))
    {
        std::expected<TypeSymbol*, int> dt = caseExpr->GetType()->DirectType(context);
        if (!dt)
        {
            SetError(dt.error());
            return;
        }
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> trv = directType->FinalType(node.GetSourcePos(), context);
        if (!trv)
        {
            SetError(trv.error());
            return;
        }
        TypeSymbol* finalType = *trv;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(switchCondType, 
            finalType, node.GetSourcePos(), context);
        if (!arv)
        {
            SetError(arv.error());
            return;
        }
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            caseExpr = new BoundConversionNode(caseExpr, conversion, node.GetSourcePos());
        }
        else
        {
            std::unexpected<int> result = Error("no conversion found", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    if (boundStmt)
    {
        if (boundStmt->IsBoundCaseStatementNode())
        {
            BoundCaseStatementNode* caseStmt = static_cast<BoundCaseStatementNode*>(boundStmt);
            caseStmt->InsertCaseExprToFront(caseExpr);
            SetStatement(boundStmt);
        }
        else
        {
            BoundCaseStatementNode* boundCaseStatement = new BoundCaseStatementNode(node.GetSourcePos());
            boundCaseStatement->AddCaseExpr(caseExpr);
            boundCaseStatement->SetStatement(boundStmt);
            SetStatement(boundCaseStatement);
        }
    }
}

void StatementBinder::Visit(otava::ast::DefaultStatementNode& node)
{
    if (!TerminatesCaseOrDefault(node.Statement()))
    {
        std::unexpected<int> warning = Warning("default statement does not terminate in return, break or continue statement", node.GetSourcePos(), context);
        std::cout << util::GetErrorMessage(warning.error()) << "\n";
    }
    BoundDefaultStatementNode* boundDefaultStatement = new BoundDefaultStatementNode(node.GetSourcePos());
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    if (boundStmt)
    {
        boundDefaultStatement->SetStatement(boundStmt);
    }
    SetStatement(boundDefaultStatement);
}

void StatementBinder::Visit(otava::ast::WhileStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    BoundWhileStatementNode* boundWhileStatement = new BoundWhileStatementNode(node.GetSourcePos());
    context->PushResetFlag(ContextFlags::returnRef);
    std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Condition(), context);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    BoundExpressionNode* condition = *brv;
    if (condition->GetType()->IsReferenceType())
    {
        condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
    }
    if (!condition->GetType()->IsBoolType())
    {
        std::expected<BoundExpressionNode*, int> rv = MakeBoundBooleanConversionNode(condition, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        condition = *rv;
    }
    context->PopFlags();
    boundWhileStatement->SetCondition(condition);
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    if (boundStmt)
    {
        boundWhileStatement->SetStatement(boundStmt);
    }
    SetStatement(boundWhileStatement);
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::DoStatementNode& node)
{
    BoundDoStatementNode* boundDoStatement = new BoundDoStatementNode(node.GetSourcePos());
    context->PushResetFlag(ContextFlags::returnRef);
    std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Expression(), context);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    BoundExpressionNode* condition = *brv;
    if (condition->GetType()->IsReferenceType())
    {
        condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
    }
    if (!condition->GetType()->IsBoolType())
    {
        std::expected<BoundExpressionNode*, int> rv = MakeBoundBooleanConversionNode(condition, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        condition = *rv;
    }
    context->PopFlags();
    boundDoStatement->SetExpr(condition);
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    if (boundStmt)
    {
        boundDoStatement->SetStatement(boundStmt);
    }
    SetStatement(boundDoStatement);
}

class RangeForDeclarationExtractor : public otava::ast::DefaultVisitor
{
public:
    RangeForDeclarationExtractor();
    otava::ast::DeclSpecifierSequenceNode* GetDeclSpecifierSequence() { return declSpecifierSequence; }
    otava::ast::Node* GetDeclarator() const { return declarator; }
    void Visit(otava::ast::ForRangeDeclarationNode& node) override;
    void Visit(otava::ast::DeclSpecifierSequenceNode& node) override;
private:
    otava::ast::DeclSpecifierSequenceNode* declSpecifierSequence;
    otava::ast::Node* declarator;
};

RangeForDeclarationExtractor::RangeForDeclarationExtractor() : declSpecifierSequence(nullptr), declarator(nullptr)
{
}

void RangeForDeclarationExtractor::Visit(otava::ast::ForRangeDeclarationNode& node)
{
    node.Left()->Accept(*this);
    declarator = node.Right();
}

void RangeForDeclarationExtractor::Visit(otava::ast::DeclSpecifierSequenceNode& node)
{
    declSpecifierSequence = &node;
}

void StatementBinder::Visit(otava::ast::RangeForStatementNode& node)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    soul::ast::SourcePos sourcePos = node.GetSourcePos();
    std::unique_ptr<otava::ast::CompoundStatementNode> rangeForCompound(new otava::ast::CompoundStatementNode(sourcePos));
    if (node.InitStatement())
    {
        std::expected<otava::ast::Node*, int> n = node.InitStatement()->Clone();
        if (!n)
        {
            SetError(n.error());
            return;
        }
        std::expected<bool, int> rv = rangeForCompound->AddNode(*n);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    otava::ast::DeclSpecifierSequenceNode* endIteratorDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    std::expected<bool, int> rv = endIteratorDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::InitDeclaratorListNode* endIteratorDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::IdentifierNode* endIteratorDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@end");
    std::expected<otava::ast::Node*, int> n = node.Initializer()->Clone();
    if (!n)
    {
        SetError(n.error());
        return;
    }
    otava::ast::Node* invokeChild = *n;
    otava::ast::IdentifierNode* invokeId = new otava::ast::IdentifierNode(sourcePos, U"end");
    otava::ast::MemberExprNode* invokeSubject = new otava::ast::MemberExprNode(sourcePos, invokeChild, new otava::ast::DotNode(sourcePos), invokeId);
    otava::ast::InvokeExprNode* endIteratorInitializer = new otava::ast::InvokeExprNode(sourcePos, invokeSubject);
    otava::ast::AssignmentInitNode* endIteratorAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, endIteratorInitializer);
    otava::ast::InitDeclaratorNode* endIteratorInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, endIteratorDeclarator, endIteratorAssignmentInitializer);
    rv = endIteratorDeclarators->AddNode(endIteratorInitDeclarator);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::SimpleDeclarationNode* endIteratorDeclaration = new otava::ast::SimpleDeclarationNode(sourcePos, endIteratorDeclSpecifiers,
        endIteratorDeclarators, nullptr, nullptr);
    rv = rangeForCompound->AddNode(endIteratorDeclaration);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::DeclSpecifierSequenceNode* forInitDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    rv = forInitDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::InitDeclaratorListNode* forInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    std::expected<otava::ast::Node*, int> f = node.Initializer()->Clone();
    if (!f)
    {
        SetError(f.error());
        return;
    }
    otava::ast::Node* forInitInvokeChild = *f;
    otava::ast::MemberExprNode* forInitInvokeSubject = new otava::ast::MemberExprNode(sourcePos, forInitInvokeChild, new otava::ast::DotNode(sourcePos),
        new otava::ast::IdentifierNode(sourcePos, U"begin"));
    otava::ast::InvokeExprNode* forInitInitializer = new otava::ast::InvokeExprNode(sourcePos, forInitInvokeSubject);
    otava::ast::AssignmentInitNode* forInitAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, forInitInitializer);
    otava::ast::IdentifierNode* forInitDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@it");
    otava::ast::InitDeclaratorNode* forInitInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, forInitDeclarator, forInitAssignmentInitializer);
    rv = forInitDeclarators->AddNode(forInitInitDeclarator);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::SimpleDeclarationNode* forInitStmt = new otava::ast::SimpleDeclarationNode(sourcePos, forInitDeclSpecifiers, forInitDeclarators, nullptr, nullptr);
    otava::ast::BinaryExprNode* forCond = new otava::ast::BinaryExprNode(sourcePos, new otava::ast::NotEqualNode(sourcePos), 
        new otava::ast::IdentifierNode(sourcePos, U"@it"),
        new otava::ast::IdentifierNode(sourcePos, U"@end"));
    otava::ast::UnaryExprNode* forLoopExpr = new otava::ast::UnaryExprNode(sourcePos, new otava::ast::PrefixIncNode(sourcePos), 
        new otava::ast::IdentifierNode(sourcePos, U"@it"));
    otava::ast::CompoundStatementNode* forActionStmt = new otava::ast::CompoundStatementNode(sourcePos);
    RangeForDeclarationExtractor extractor;
    node.Declaration()->Accept(extractor);
    otava::ast::DeclSpecifierSequenceNode* forActionDeclSpecifiers = extractor.GetDeclSpecifierSequence();
    otava::ast::Node* declarator = extractor.GetDeclarator();
    std::expected<otava::ast::Node*, int> d = declarator->Clone();
    if (!d)
    {
        SetError(d.error());
        return;
    }
    otava::ast::AssignmentInitNode* forActionAssignmentInit = new otava::ast::AssignmentInitNode(sourcePos, new otava::ast::UnaryExprNode(sourcePos,
        new otava::ast::DerefNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it")));
    otava::ast::InitDeclaratorNode* forActionInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, *d, forActionAssignmentInit);
    otava::ast::InitDeclaratorListNode* forActionInitDeclaratorList = new otava::ast::InitDeclaratorListNode(sourcePos);
    rv = forActionInitDeclaratorList->AddNode(forActionInitDeclarator);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<otava::ast::Node*, int> fadsrv = forActionDeclSpecifiers->Clone();
    if (!fadsrv)
    {
        SetError(fadsrv.error());
        return;
    }
    otava::ast::SimpleDeclarationNode* forActionDeclaration = new otava::ast::SimpleDeclarationNode(sourcePos, *fadsrv, forActionInitDeclaratorList, nullptr, nullptr);
    otava::ast::DeclarationStatementNode* forActionDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, forActionDeclaration);
    rv = forActionStmt->AddNode(forActionDeclarationStmt);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<otava::ast::Node*, int> s = node.Statement()->Clone();
    if (!s)
    {
        SetError(s.error());
        return;
    }
    rv = forActionStmt->AddNode(*s);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::ast::ForStatementNode* forStmt = new otava::ast::ForStatementNode(sourcePos, forInitStmt, forCond, forLoopExpr, forActionStmt, 
        nullptr, nullptr, sourcePos, sourcePos, sourcePos);
    rv = rangeForCompound->AddNode(forStmt);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
    Instantiator instantiator(context, &instantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    rangeForCompound->Accept(instantiator);
    if (!instantiator)
    {
        SetError(instantiator.Error());
        return;
    }
    context->PopFlags();
    rangeForCompound->Accept(*this);
    if (!Valid()) return;
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
}

void StatementBinder::Visit(otava::ast::ForStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    BoundForStatementNode* boundForStatement = new BoundForStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        std::expected<BoundStatementNode*, int> bs = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (!bs)
        {
            SetError(bs.error());
            return;
        }
        BoundStatementNode* boundInitStatement = *bs;
        if (boundInitStatement)
        {
            boundForStatement->SetInitStatement(boundInitStatement);
        }
    }
    if (node.Condition())
    {
        context->PushResetFlag(ContextFlags::returnRef);
        std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Condition(), context);
        if (!brv)
        {
            SetError(brv.error());
            return;
        }
        BoundExpressionNode* condition = *brv;
        if (condition->GetType()->IsReferenceType())
        {
            condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
        }
        if (!condition->GetType()->IsBoolType())
        {
            std::expected<BoundExpressionNode*, int> rv = MakeBoundBooleanConversionNode(condition, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            condition = *rv;
        }
        context->PopFlags();
        boundForStatement->SetCondition(condition);
    }
    if (node.LoopExpr())
    {
        std::expected<BoundExpressionNode*, int> brv = BindExpression(node.LoopExpr(), context);
        if (!brv)
        {
            SetError(brv.error());
            return;
        }
        BoundExpressionNode* loopExpr = *brv;
        boundForStatement->SetLoopExpr(loopExpr);
    }
    std::expected<BoundStatementNode*, int> bs = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (!bs)
    {
        SetError(bs.error());
        return;
    }
    BoundStatementNode* boundStmt = *bs;
    if (boundStmt)
    {
        boundForStatement->SetStatement(boundStmt);
    }
    SetStatement(boundForStatement);
    rv = context->GetSymbolTable()->EndScopeGeneric(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::BreakStatementNode& node)
{
    BoundBreakStatementNode* boundBreakStatement = new BoundBreakStatementNode(node.GetSourcePos());
    SetStatement(boundBreakStatement);
}

void StatementBinder::Visit(otava::ast::ContinueStatementNode& node)
{
    BoundContinueStatementNode* boundContinueStatement = new BoundContinueStatementNode(node.GetSourcePos());
    SetStatement(boundContinueStatement);
}

void StatementBinder::Visit(otava::ast::ReturnStatementNode& node)
{
    auto vp = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::voidType);
    if (!vp)
    {
        SetError(vp.error());
        return;
    }
    TypeSymbol* voidType = *vp;
    BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(node.GetSourcePos());
    if (node.ReturnValue())
    {
        TypeSymbol* returnType = nullptr;
        if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType())
        {
            auto fp = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType()->DirectType(context);
            if (!fp)
            {
                SetError(fp.error());
                return;
            }
            returnType = *fp;
            fp = returnType->FinalType(node.GetSourcePos(), context);
            if (!fp)
            {
                SetError(fp.error());
                return;
            }
            returnType = *fp;
        }
        if (!returnType || TypesEqual(returnType, voidType, context))
        {
            std::unexpected<int> result = Error("cannot return a value", node.ReturnValue()->GetSourcePos(), context);
            SetError(result.error());
            return;
        }
        if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnsClass())
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> classReturnArgs;
            ParameterSymbol* returnValueParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnValueParam();
            std::expected<TypeSymbol*, int> rrv = returnValueParam->GetReferredType(context);
            if (!rrv)
            {
                SetError(rrv.error());
                return;
            }
            classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundParameterNode(returnValueParam, node.GetSourcePos(), *rrv)));
            std::expected<BoundExpressionNode*, int> brv = BindExpression(node.ReturnValue(), context);
            if (!brv)
            {
                SetError(brv.error());
                return;
            }
            BoundExpressionNode* expression = *brv;
            if (!expression)
            {
                std::unexpected<int> result = Error("could not bind expression", node.ReturnValue()->GetSourcePos(), context);
                SetError(result.error());
                return;
            }
            if (expression->IsBoundLocalVariable())
            {
                std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
                moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
                std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", node.GetSourcePos(), context);
                if (!nrv)
                {
                    SetError(nrv.error());
                    return;
                }
                Scope* scope = *nrv;
                std::vector<TypeSymbol*> templateArgs;
                std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                    scope, U"move", templateArgs, moveArgs, node.GetSourcePos(), context, OverloadResolutionFlags::dontSearchArgumentScopes);
                if (!orv)
                {
                    SetError(orv.error());
                    return;
                }
                std::unique_ptr<BoundFunctionCallNode> moveExpr = std::move(*orv);
                expression = moveExpr.release();
            }
            classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
            std::vector<TypeSymbol*> templateArgs;
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", 
                templateArgs, classReturnArgs, node.GetSourcePos(), context);
            if (!orv)
            {
                SetError(orv.error());
                return;
            }
            std::unique_ptr<BoundFunctionCallNode> constructorCall = std::move(*orv);
            std::unique_ptr<BoundExpressionStatementNode> expressionStatement(new BoundExpressionStatementNode(node.GetSourcePos()));
            std::expected<bool, int> erv = expressionStatement->SetExpr(constructorCall.release(), node.GetSourcePos(), context);
            if (!erv)
            {
                SetError(erv.error());
                return;
            }
            SetStatement(expressionStatement.release());
        }
        else
        {
            std::expected<TypeSymbol*, int> dt = functionDefinitionSymbol->ReturnType()->DirectType(context);
            if (!dt)
            {
                SetError(dt.error());
                return;
            }
            TypeSymbol* directType = *dt;
            std::expected<TypeSymbol*, int> frv = directType->FinalType(node.GetSourcePos(), context);
            if (!frv)
            {
                SetError(frv.error());
                return;
            }
            TypeSymbol* returnType = *frv;
            bool flagsPushed = false;
            if (returnType->IsReferenceType())
            {
                context->PushSetFlag(ContextFlags::returnRef);
                flagsPushed = true;
            }
            std::expected<BoundExpressionNode*, int> brv = BindExpression(node.ReturnValue(), context);
            if (!brv)
            {
                SetError(brv.error());
                return;
            }
            BoundExpressionNode* returnValueExpr = *brv;
            if (!returnValueExpr)
            {
                std::unexpected<int> result = Error("could not bind expression", node.ReturnValue()->GetSourcePos(), context);
                SetError(result.error());
                return;
            }
            if (!TypesEqual(returnValueExpr->GetType(), returnType, context))
            {
                std::expected<TypeSymbol*, int> pt = returnValueExpr->GetType()->PlainType(context);
                if (!pt)
                {
                    SetError(pt.error());
                    return;
                }
                TypeSymbol* returnValueExprType = *pt;
                pt = returnType->PlainType(context);
                if (!pt)
                {
                    SetError(pt.error());
                    return;
                }
                TypeSymbol* retType = *pt;
                if (TypesEqual(returnValueExprType, retType, context))
                {
                    if (!(
                        returnType->IsLValueRefType() && returnValueExpr->GetType()->IsRValueRefType() ||
                        returnType->IsRValueRefType() && returnValueExpr->GetType()->IsLValueRefType()))
                    {
                        if (returnType->IsLValueRefType())
                        {
                            std::expected<TypeSymbol*, int> pt = returnValueExpr->GetType()->AddLValueRef(context);
                            if (!pt)
                            {
                                SetError(pt.error());
                                return;
                            }
                            TypeSymbol* type = *pt;
                            returnValueExpr = new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), type);
                        }
                        else if (returnValueExpr->GetType()->IsLValueRefType())
                        {
                            std::expected<TypeSymbol*, int> pt = returnValueExpr->GetType()->RemoveReference(context);
                            if (!pt)
                            {
                                SetError(pt.error());
                                return;
                            }
                            TypeSymbol* type = *pt;
                            returnValueExpr = new BoundDereferenceNode(returnValueExpr, node.GetSourcePos(), type);
                        }
                    }
                }
                else
                {
                    ArgumentMatch argumentMatch;
                    FunctionMatch functionMatch;
                    std::expected<TypeSymbol*, int> dt = returnValueExpr->GetType()->DirectType(context);
                    if (!dt)
                    {
                        SetError(dt.error());
                        return;
                    }
                    TypeSymbol* directType = *dt;
                    std::expected<TypeSymbol*, int> frv = directType->FinalType(node.GetSourcePos(), context);
                    if (!frv)
                    {
                        SetError(frv.error());
                        return;
                    }
                    TypeSymbol* finalType = *frv;
                    std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        returnType, finalType, returnValueExpr, node.GetSourcePos(), argumentMatch, functionMatch, context);
                    if (!arv)
                    {
                        SetError(arv.error());
                        return;
                    }
                    FunctionSymbol* conversion = *arv;
                    if (conversion)
                    {
                        if (argumentMatch.preConversionFlags == OperationFlags::addr)
                        {
                            std::expected<TypeSymbol*, int> pt = returnValueExpr->GetType()->AddPointer(context);
                            if (!pt)
                            {
                                SetError(pt.error());
                                return;
                            }
                            TypeSymbol* ptrType = *pt;
                            returnValueExpr = new BoundConversionNode(
                                new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), ptrType), conversion, node.GetSourcePos());
                        }
                        else
                        {
                            returnValueExpr = new BoundConversionNode(returnValueExpr, conversion, node.GetSourcePos());
                        }
                    }
                    else
                    {
                        std::unexpected<int> rv = Error("no conversion found", node.GetSourcePos(), context);
                        SetError(rv.error());
                        return;
                    }
                }
            }
            std::expected<bool, int> erv = boundReturnStatement->SetExpr(returnValueExpr, node.GetSourcePos(), context);
            if (!erv)
            {
                SetError(erv.error());
                return;
            }
            if (flagsPushed)
            {
                context->PopFlags();
            }
        }
    }
    else
    {
        TypeSymbol* returnType = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType();
        if (returnType)
        {
            auto fp = returnType->DirectType(context);
            if (!fp)
            {
                SetError(fp.error());
                return;
            }
            returnType = *fp;
            fp = returnType->FinalType(node.GetSourcePos(), context);
            if (!fp)
            {
                SetError(fp.error());
                return;
            }
            returnType = *fp;
        }
        if (returnType && !TypesEqual(returnType, voidType, context))
        {
            std::unexpected<int> result = Error("must return a value", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    SetStatement(boundReturnStatement);
}

void StatementBinder::Visit(otava::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode(node.GetSourcePos());
    if (node.Expression())
    {
        std::expected<BoundExpressionNode*, int> brv = BindExpression(node.Expression(), context);
        if (!brv)
        {
            SetError(brv.error());
            return;
        }
        BoundExpressionNode* expr = *brv;
        if (expr->IsBoundConstructTemporaryNode())
        {
            BoundConstructTemporaryNode* ctNode = static_cast<BoundConstructTemporaryNode*>(expr);
            BoundExpressionNode* call = ctNode->ConstructorCall();
            if (call->IsBoundFunctionCallNode())
            {
                BoundFunctionCallNode* fnCall = static_cast<BoundFunctionCallNode*>(call);
                FunctionSymbol* fn = fnCall->GetFunctionSymbol();
                TypeSymbol* returnType = fn->ReturnType();
                if (returnType && returnType->IsClassTemplateSpecializationSymbol())
                {
                    ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(returnType);
                    ClassTypeSymbol* ct = sp->ClassTemplate();
                    ClassGroupSymbol* group = ct->Group();
                    if (group->Name() == U"expected")
                    {
                        std::expected<std::u32string, int> fname = fn->FullName();
                        if (!fname)
                        {
                            SetError(fname.error());
                            return;
                        }
                        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                        if (!sfname)
                        {
                            SetError(sfname.error());
                            return;
                        }
                        std::unexpected<int> warning = Warning("discarding return value of function '" + *sfname + "'", node.GetSourcePos(), context);
                        std::cout << util::GetErrorMessage(warning.error()) << "\n";
                    }
                }
            }
        }
        std::expected<bool, int> erv = boundExpressionStatement->SetExpr(expr, node.GetSourcePos(), context);
        if (!erv)
        {
            SetError(erv.error());
            return;
        }
    }
    SetStatement(boundExpressionStatement);
}

void StatementBinder::Visit(otava::ast::DeclarationStatementNode& node)
{
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
}

void StatementBinder::Visit(otava::ast::AliasDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<bool, int> erv = ProcessAliasDeclaration(&node, context);
    if (!erv)
    {
        SetError(erv.error());
        return;
    }
}

void StatementBinder::Visit(otava::ast::SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    BoundCompoundStatementNode* boundCompoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
    std::unique_ptr<DeclarationList> declarationList = context->ReleaseDeclarationList(&node);
    if (declarationList)
    {
        bool setStatement = true;
        for (auto& declaration : declarationList->declarations)
        {
            VariableSymbol* variable = declaration.variable;
            if (variable->IsStatic())
            {
                std::expected<bool, int> rv = BindStaticLocalVariable(variable, declaration.initializer, &node);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                setStatement = false;
            }
            else
            {
                BoundExpressionNode* initializer = nullptr;
                if (declaration.initializer)
                {
                    bool flagsPushed = false;
                    if (variable->GetDeclaredType()->IsReferenceType())
                    {
                        context->PushSetFlag(ContextFlags::returnRef);
                        flagsPushed = true;
                    }
                    context->SetDeclaredInitializerType(variable->GetDeclaredType());
                    std::expected<BoundExpressionNode*, int> brv = BindExpression(declaration.initializer, context);
                    if (!brv)
                    {
                        SetError(brv.error());
                        return;
                    }
                    initializer = *brv;
                    context->SetDeclaredInitializerType(nullptr);
                    if (flagsPushed)
                    {
                        context->PopFlags();
                    }
                }
                if (initializer && initializer->GetType())
                {
                    std::expected<TypeSymbol*, int> dt = initializer->GetType()->DirectType(context);
                    if (!dt)
                    {
                        SetError(dt.error());
                        return;
                    }
                    TypeSymbol* directType = *dt;
                    std::expected<TypeSymbol*, int> frv = directType->FinalType(node.GetSourcePos(), context);
                    if (!frv)
                    {
                        SetError(frv.error());
                        return;
                    }
                    TypeSymbol* initializerType = *frv;
                    if (variable->GetDeclaredType()->GetBaseType()->IsAutoTypeSymbol() && variable->GetDeclaredType()->GetDerivations() != Derivations::none)
                    {
                        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(initializerType->GetBaseType(), 
                            variable->GetDeclaredType()->GetDerivations());
                        if (!c)
                        {
                            SetError(c.error());
                            return;
                        }
                        initializerType = *c;
                    }
                    variable->SetInitializerType(initializerType);
                }
                BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
                std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
                std::expected<TypeSymbol*, int> pt = boundVariable->GetType()->AddPointer(context);
                if (!pt)
                {
                    SetError(pt.error());
                    return;
                }
                TypeSymbol* ptrType = *pt;
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, node.GetSourcePos(), ptrType)));
                if (initializer)
                {
                    if (initializer->IsBoundExpressionListNode())
                    {
                        BoundExpressionListNode* exprListNode = static_cast<BoundExpressionListNode*>(initializer);
                        int n = exprListNode->Count();
                        for (int i = 0; i < n; ++i)
                        {
                            arguments.push_back(std::unique_ptr<BoundExpressionNode>(exprListNode->ReleaseExpr(i)));
                        }
                    }
                    else
                    {
                        arguments.push_back(std::unique_ptr<BoundExpressionNode>(initializer));
                    }
                }
                std::vector<TypeSymbol*> templateArgs;
                std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor",
                    templateArgs, arguments, node.GetSourcePos(), context);
                if (!orv)
                {
                    SetError(orv.error());
                    return;
                }
                std::unique_ptr<BoundFunctionCallNode> constructorCall = std::move(*orv);
                BoundConstructionStatementNode* boundConstructionStatement = nullptr;
                otava::symbols::ClassTypeSymbol* cls = nullptr;
                BoundExpressionNode* firstArg = nullptr;
                FunctionDefinitionSymbol* destructor = nullptr;
                if (constructorCall->CallsClassConstructor(cls, firstArg, destructor))
                {
                    boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                    std::expected<BoundFunctionCallNode*, int> rv = MakeDestructorCall(cls, firstArg, destructor, node.GetSourcePos(), context);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    otava::symbols::BoundFunctionCallNode* destructorCall = *rv;
                    if (destructorCall)
                    {
                        boundConstructionStatement->SetDestructorCall(destructorCall);
                    }
                }
                else
                {
                    boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                }
                boundCompoundStatement->AddStatement(boundConstructionStatement);
                functionDefinitionSymbol->AddLocalVariable(variable);
            }
        }
        if (setStatement)
        {
            SetStatement(boundCompoundStatement);
        }
    }
}

void StatementBinder::SetStatement(BoundStatementNode* statement)
{
    if (postfix)
    {
        statement->SetPostfix();
    }
    if (boundStatement)
    {
        if (boundStatement->Postfix())
        {
            BoundSequenceStatementNode* sequenceStatement = new BoundSequenceStatementNode(statement->GetSourcePos(), statement, boundStatement);
            statement = sequenceStatement;
        }
        else
        {
            BoundSequenceStatementNode* sequenceStatement = new BoundSequenceStatementNode(statement->GetSourcePos(), boundStatement, statement);
            statement = sequenceStatement;
        }
        if (postfix)
        {
            statement->SetPostfix();
        }
    }
    boundStatement = statement;
}

struct FunctionStaticDeclarationExtractor : public otava::ast::DefaultVisitor
{
    FunctionStaticDeclarationExtractor(const soul::ast::SourcePos& sourcePos_, otava::ast::IdentifierNode* globalVarId_, bool isArrayVar_);
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::DeclSpecifierSequenceNode& node) override;
    void Visit(otava::ast::InitDeclaratorListNode& node) override;
    void Visit(otava::ast::InitDeclaratorNode& node) override;
    void Visit(otava::ast::PtrDeclaratorNode& node) override;
    void Visit(otava::ast::PtrNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::ArrayDeclaratorNode& node) override;
    soul::ast::SourcePos sourcePos;
    otava::ast::IdentifierNode* globalVarId;
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers;
    otava::ast::InitDeclaratorListNode* initDeclarators;
    otava::ast::PtrDeclaratorNode* ptrDeclaratorNode;
    otava::ast::Node* declaratorNode;
    bool isArrayVar;
};

FunctionStaticDeclarationExtractor::FunctionStaticDeclarationExtractor(const soul::ast::SourcePos& sourcePos_, otava::ast::IdentifierNode* globalVarId_, bool isArrayVar_) :
    sourcePos(sourcePos_), globalVarId(globalVarId_), ptrDeclaratorNode(nullptr), declaratorNode(nullptr), isArrayVar(isArrayVar_)
{
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    initDeclarators = new otava::ast::InitDeclaratorListNode(node.GetSourcePos());
    node.DeclarationSpecifiers()->Accept(*this);
    node.InitDeclaratorList()->Accept(*this);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::DeclSpecifierSequenceNode& node)
{
    if (!Valid()) return;
    for (const auto& declSpecifierNode : node.Nodes())
    {
        if (declSpecifierNode->IsStaticNode())
        {
            continue;
        }
        std::expected<otava::ast::Node*, int> c = declSpecifierNode->Clone();
        if (!c)
        {
            SetError(c.error());
            return;
        }
        std::expected<bool, int> rv = declSpecifiers->AddNode(*c);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrNode& node)
{
    if (!Valid()) return;
    if (ptrDeclaratorNode)
    {
        std::expected<otava::ast::Node*, int> n = node.Clone();
        if (!n)
        {
            SetError(n.error());
            return;
        }
        std::expected<bool, int> rv = ptrDeclaratorNode->AddNode(*n);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    if (ptrDeclaratorNode)
    {
        std::expected<otava::ast::Node*, int> n = globalVarId->Clone();
        if (!n)
        {
            SetError(n.error());
            return;
        }
        std::expected<bool, int> rv = ptrDeclaratorNode->AddNode(*n);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::expected<otava::ast::Node*, int> d = globalVarId->Clone();
        if (!d)
        {
            SetError(d.error());
            return;
        }
        declaratorNode = *d;
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    if (ptrDeclaratorNode)
    {
        std::expected<otava::ast::Node*, int> d = globalVarId->Clone();
        if (!d)
        {
            SetError(d.error());
            return;
        }
        std::expected<bool, int> rv = ptrDeclaratorNode->AddNode(*d);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::expected<otava::ast::Node*, int> d = globalVarId->Clone();
        if (!d)
        {
            SetError(d.error());
            return;
        }
        declaratorNode = *d;
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrDeclaratorNode& node)
{
    if (!Valid()) return;
    ptrDeclaratorNode = new otava::ast::PtrDeclaratorNode(sourcePos);
    for (const auto& node : node.Nodes())
    {
        node->Accept(*this);
        if (!Valid()) return;
    }
    std::expected<bool, int> rv = initDeclarators->AddNode(ptrDeclaratorNode);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ptrDeclaratorNode = nullptr;
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::ArrayDeclaratorNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    otava::ast::Node* dimension = nullptr;
    if (node.Dimension())
    {
        std::expected<otava::ast::Node*, int> d = node.Dimension()->Clone();
        if (!d)
        {
            SetError(d.error());
            return;
        }
        dimension = *d;
    }
    declaratorNode = new otava::ast::ArrayDeclaratorNode(sourcePos, declaratorNode, dimension, sourcePos, sourcePos);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorNode& node)
{
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    if (isArrayVar)
    {
        std::expected<otava::ast::Node*, int> r = node.Right()->Clone();
        if (!r)
        {
            SetError(r.error());
            return;
        }
        declaratorNode = new otava::ast::InitDeclaratorNode(sourcePos, declaratorNode, *r);
    }
    if (declaratorNode)
    {
        std::expected<bool, int> rv = initDeclarators->AddNode(declaratorNode);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        declaratorNode = nullptr;
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorListNode& node)
{
    if (!Valid()) return;
    for (const auto& declNode : node.Nodes())
    {
        declNode->Accept(*this);
        if (!Valid()) return;
        if (declaratorNode)
        {
            std::expected<bool, int> rv = initDeclarators->AddNode(declaratorNode);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            declaratorNode = nullptr;
        }
    }
}

void StatementBinder::Visit(otava::ast::BoundStatementNode& node)
{
    if (!Valid()) return;
    SetStatement(static_cast<BoundStatementNode*>(node.GetBoundStatementNode()));
}

std::expected<bool, int> StatementBinder::BindStaticLocalVariable(
    VariableSymbol* variable, otava::ast::Node* initializerNode, otava::ast::SimpleDeclarationNode* declarationNode)
{
    /*
        std::atomic_bool variable_initialized;
        if (!variable_initialized)
        {
            std::lock_guard<std::recursive_mutex> lock(std::get_init_lock());
            if (!variable_initialized)
            {
                type variable(initializer);
                variable_initialized = true;
            }
        }
    */
    bool isArrayVar = variable->GetDeclaredType()->IsArrayTypeSymbol();
    soul::ast::SourcePos sourcePos = declarationNode->GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::expected<std::u32string, int> fname = functionDefinitionSymbol->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    std::string shaMaterial = *sfname;
    if (!functionDefinitionSymbol->Specialization().empty())
    {
        for (TypeSymbol* type : functionDefinitionSymbol->Specialization())
        {
            fname = type->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            shaMaterial.append(".").append(*sfname);
        }
    }
    shaMaterial.append(".").append(context->GetBoundCompileUnit()->Id()).append(1, '_').append(std::to_string(context->GetBoundFunction()->Serial()));
    std::string sha = util::GetSha1MessageDigest(shaMaterial);
    std::expected<otava::ast::Node*, int> n = MakeTypeNameNodes(sourcePos, U"std::atomic_bool");
    if (!n) return std::unexpected<int>(n.error());
    otava::ast::Node* atomicBoolType = *n;
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    std::expected<bool, int> erv = declSpecifiers->AddNode(atomicBoolType);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::ast::InitDeclaratorListNode* initDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    std::expected<std::u32string, int> shau32 = util::ToUtf32(sha);
    if (!shau32) return std::unexpected<int>(shau32.error());
    std::unique_ptr<otava::ast::IdentifierNode> initializedVarName(new otava::ast::IdentifierNode(sourcePos, variable->Name() + U"_initialized_" + *shau32));
    std::expected<otava::ast::Node*, int> i = initializedVarName->Clone();
    if (!i) return std::unexpected<int>(i.error());
    erv = initDeclarators->AddNode(*i);
    if (!erv) return std::unexpected<int>(erv.error());
    std::unique_ptr<otava::ast::SimpleDeclarationNode> initializedVarDeclaration(
        new otava::ast::SimpleDeclarationNode(sourcePos, declSpecifiers, initDeclarators, nullptr, nullptr));
    context->GetSymbolTable()->BeginScope(context->GetSymbolTable()->GlobalNs()->GetScope());
    erv = ProcessSimpleDeclaration(initializedVarDeclaration.get(), nullptr, context);
    if (!erv) return std::unexpected<int>(erv.error());
    std::u32string globalStaticVarName = variable->Name() + U"_global_" + *shau32;
    std::unique_ptr<otava::ast::IdentifierNode> globalStaticVarId(new otava::ast::IdentifierNode(sourcePos, globalStaticVarName));
    FunctionStaticDeclarationExtractor extractor(sourcePos, globalStaticVarId.get(), isArrayVar);
    declarationNode->Accept(extractor);
    otava::ast::DeclSpecifierSequenceNode* globalStaticDeclSpecifiers = extractor.declSpecifiers;
    otava::ast::InitDeclaratorListNode* globalStaticInitDeclarators = extractor.initDeclarators;
    context->PushSetFlag(ContextFlags::noDynamicInit);
    std::unique_ptr<otava::ast::SimpleDeclarationNode> globalStaticVarDeclaration(new otava::ast::SimpleDeclarationNode(sourcePos,
        globalStaticDeclSpecifiers, globalStaticInitDeclarators, nullptr, nullptr));
    if (isArrayVar)
    {
        context->SetDeclaredInitializerType(variable->GetDeclaredType());
    }
    erv = ProcessSimpleDeclaration(globalStaticVarDeclaration.get(), nullptr, context);
    if (!erv) return std::unexpected<int>(erv.error());
    context->PopFlags();
    erv = context->GetSymbolTable()->EndScope();
    if (!erv) return std::unexpected<int>(erv.error());
    std::unique_ptr<otava::ast::CompoundStatementNode> compound1;
    std::unique_ptr<otava::ast::UnaryExprNode> inititalizedCond;
    std::unique_ptr<otava::ast::CompoundStatementNode> compound2;
    if (!isArrayVar)
    {
        compound1.reset(new otava::ast::CompoundStatementNode(sourcePos));
        std::expected<otava::ast::Node*, int> n = MakeTypeNameNodes(sourcePos, U"std::lock_guard");
        if (!n) return std::unexpected<int>(n.error());
        otava::ast::TemplateIdNode* lockGuardType = new otava::ast::TemplateIdNode(sourcePos, *n);
        n = MakeTypeNameNodes(sourcePos, U"std::recursive_mutex");
        if (!n) return std::unexpected<int>(n.error());
        erv = lockGuardType->AddNode(*n);
        if (!erv) return std::unexpected<int>(erv.error());
        otava::ast::DeclSpecifierSequenceNode* lockGuardDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
        erv = lockGuardDeclSpecifiers->AddNode(lockGuardType);
        if (!erv) return std::unexpected<int>(erv.error());
        otava::ast::InitDeclaratorListNode* lockGuardInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
        n = MakeTypeNameNodes(sourcePos, U"std::get_init_lock");
        if (!n) return std::unexpected<int>(n.error());
        otava::ast::Node* getInitLock = *n;
        otava::ast::InvokeExprNode* lockInit = new otava::ast::InvokeExprNode(sourcePos, getInitLock);
        otava::ast::InitDeclaratorNode* lockGuardInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, 
            new otava::ast::IdentifierNode(sourcePos, U"lock"), lockInit);
        erv = lockGuardInitDeclarators->AddNode(lockGuardInitDeclarator);
        if (!erv) return std::unexpected<int>(erv.error());
        std::unique_ptr<otava::ast::SimpleDeclarationNode> lockGuardDeclaration(new otava::ast::SimpleDeclarationNode(sourcePos, 
            lockGuardDeclSpecifiers, lockGuardInitDeclarators, nullptr, nullptr));
        otava::ast::DeclarationStatementNode* lockGuardDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, lockGuardDeclaration.release());
        erv = compound1->AddNode(lockGuardDeclarationStmt);
        if (!erv) return std::unexpected<int>(erv.error());
        std::expected<otava::ast::Node*, int> i = initializedVarName->Clone();
        if (!i) return std::unexpected<int>(i.error());
        inititalizedCond.reset(new otava::ast::UnaryExprNode(sourcePos, new otava::ast::NotNode(sourcePos), *i));
        compound2.reset(new otava::ast::CompoundStatementNode(sourcePos));
    }
    globalStaticVariableSymbol = nullptr;
    std::expected<Symbol*, int> lrv = context->GetSymbolTable()->Lookup(globalStaticVarName, SymbolGroupKind::variableSymbolGroup, sourcePos, context);
    if (!lrv) return std::unexpected<int>(lrv.error());
    Symbol* symbol = *lrv;
    if (symbol && symbol->IsVariableSymbol())
    {
        globalStaticVariableSymbol = static_cast<VariableSymbol*>(symbol);
    }
    else if (symbol && symbol->IsVariableGroupSymbol())
    {
        auto irn = util::ToUtf8(globalStaticVarName);
        if (!irn) return std::unexpected<int>(irn.error());
        std::string irName = *irn;
        return Error("ir name '" + irName + "' of function static global not unique", sourcePos, context);
    }
    else
    {
        return Error("function static global not found", sourcePos, context);
    }
    if (!isArrayVar)
    {
        BoundVariableNode* boundVariable = new BoundVariableNode(globalStaticVariableSymbol, sourcePos);
        std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
        std::expected<TypeSymbol*, int> pt = boundVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, sourcePos, ptrType)));
        BoundExpressionNode* initializer = nullptr;
        if (initializerNode)
        {
            std::expected<BoundExpressionNode*, int> brv = BindExpression(initializerNode, context);
            if (!brv) return std::unexpected<int>(brv.error());
            initializer = *brv;
        }
        if (initializer)
        {
            if (initializer->IsBoundExpressionListNode())
            {
                BoundExpressionListNode* exprListNode = static_cast<BoundExpressionListNode*>(initializer);
                int n = exprListNode->Count();
                for (int i = 0; i < n; ++i)
                {
                    arguments.push_back(std::unique_ptr<BoundExpressionNode>(exprListNode->ReleaseExpr(i)));
                }
            }
            else
            {
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(initializer));
            }
        }
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor",
            templateArgs, arguments, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> constructorCall = std::move(*orv);
        constructFunctionStaticStatement.reset(new BoundExpressionStatementNode(sourcePos));
        erv = constructFunctionStaticStatement->SetExpr(constructorCall.release(), sourcePos, context);
        if (!erv) return std::unexpected<int>(erv.error());
        otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(constructFunctionStaticStatement.release(), sourcePos);
        erv = compound2->AddNode(boundStatement);
        if (!erv) return std::unexpected<int>(erv.error());
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> arv = MakeAtExitForVariable(globalStaticVariableSymbol, sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        std::unique_ptr<BoundFunctionCallNode> atExitCall = std::move(*arv);
        if (atExitCall.get())
        {
            atExitStatement.reset(new BoundExpressionStatementNode(sourcePos));
            erv = atExitStatement->SetExpr(atExitCall.release(), sourcePos, context);
            if (!erv) return std::unexpected<int>(erv.error());
            otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(atExitStatement.release(), sourcePos);
            erv = compound2->AddNode(boundStatement);
            if (!erv) return std::unexpected<int>(erv.error());
        }
        std::expected<otava::ast::Node*, int> i = initializedVarName->Clone();
        if (!i) return std::unexpected<int>(i.error());
        otava::ast::BinaryExprNode* setInitializedToTrueExpr = new otava::ast::BinaryExprNode(sourcePos, new otava::ast::AssignNode(sourcePos), *i,
            new otava::ast::BooleanLiteralNode(sourcePos, true, U"true"));
        std::unique_ptr<otava::ast::ExpressionStatementNode> setInitializedToTrueStmt(
            new otava::ast::ExpressionStatementNode(sourcePos, setInitializedToTrueExpr, nullptr, nullptr));
        erv = compound2->AddNode(setInitializedToTrueStmt.release());
        if (!erv) return std::unexpected<int>(erv.error());
        std::expected<otava::ast::Node*, int> c = inititalizedCond->Clone();
        if (!c) return std::unexpected<int>(c.error());
        std::unique_ptr<otava::ast::IfStatementNode> innerIf(
            new otava::ast::IfStatementNode(sourcePos, nullptr, *c, compound2.release(), nullptr, nullptr,
            sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        erv = compound1->AddNode(innerIf.release());
        if (!erv) return std::unexpected<int>(erv.error());
        c = inititalizedCond->Clone();
        if (!c) return std::unexpected<int>(c.error());
        std::unique_ptr<otava::ast::IfStatementNode> ifStmt(
            new otava::ast::IfStatementNode(sourcePos, nullptr, *c, compound1.release(), nullptr, nullptr,
            sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
        Instantiator instantiator(context, &instantiationScope);
        context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
        ifStmt->Accept(instantiator);
        if (!instantiator) return std::unexpected<int>(instantiator.Error());
        context->PopFlags();
        std::expected<BoundStatementNode*, int> bs = BindStatement(ifStmt.get(), functionDefinitionSymbol, context);
        if (!bs) return std::unexpected<int>(bs.error());
        BoundStatementNode* boundIfStmt = *bs;
        SetStatement(boundIfStmt);
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    }
    context->SetDeclaredInitializerType(nullptr);
    variable->SetGlobal(globalStaticVariableSymbol);
}

std::expected<BoundStatementNode*, int> BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    StatementBinder binder(context, functionDefinitionSymbol);
    statementNode->Accept(binder);
    if (!binder) return std::unexpected<int>(binder.Error());
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    return std::expected<BoundStatementNode*, int>(boundStatement);
}

std::expected<FunctionDefinitionSymbol*, int> BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    auto fname = functionDefinitionSymbol->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    auto sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    TraceInfo* traceInfo = context->GetTraceInfo();
    if (traceInfo)
    {
        int64_t sourceFileId = traceInfo->GetSourceFileId(context->GetModule()->FilePath());
        if (sourceFileId != -1)
        {
            traceInfo->AddFunctionTraceInfo(sourceFileId, context->GetModule()->Id(), *sfname);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("source file id for source file '" + context->GetModule()->FilePath() + "' not set"));
        }
    }
    if (!functionDefinitionSymbol->IsSpecialization())
    {
        if (functionDefinitionSymbol->Declaration())
        {
            functionDefinitionSymbol->Declaration()->SetFlag(FunctionSymbolFlags::fixedIrName);
        }
        functionDefinitionSymbol->SetFlag(FunctionSymbolFlags::fixedIrName);
    }
    std::expected<bool, int> rv = RemoveTemporaryAliasTypeSymbols(context);
    if (!rv) return std::unexpected<int>(rv.error());
    if (functionDefinitionSymbol->IsBound()) return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
    if (functionDefinitionSymbol->IsTemplate()) return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
    if (context->GetFlag(ContextFlags::parseMemberFunction)) return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
    std::set<const Symbol*> visited;
    if (functionDefinitionSymbol->IsTemplateParameterInstantiation(context, visited)) return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
#ifdef DEBUG_FUNCTIONS
    std::cout << ">" << *sfname << "\n";
#endif
    functionDefinitionSymbol->SetBound();
    StatementBinder binder(context, functionDefinitionSymbol);
    rv = GenerateEnterFunctionCode(functionDefinitionNode, functionDefinitionSymbol, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionDefinitionNode->Accept(binder);
    if (!binder) return std::unexpected<int>(binder.Error());
    functionDefinitionSymbol = binder.GetFunctionDefinitionSymbol();
    bool hasNoReturnAttribute = false;
    if (functionDefinitionNode->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* fnDefNode = static_cast<otava::ast::FunctionDefinitionNode*>(functionDefinitionNode);
        hasNoReturnAttribute = HasNoReturnAttribute(fnDefNode->Attributes());
    }
    if (functionDefinitionSymbol->ReturnType() &&
        !functionDefinitionSymbol->ReturnType()->IsVoidType() &&
        functionDefinitionSymbol->GroupName() != U"main" &&
        !hasNoReturnAttribute)
    {
        std::expected<bool, int> rv = CheckFunctionReturnPaths(functionDefinitionNode, context);
        if (!rv) return std::unexpected<int>(rv.error());
    }
#ifdef DEBUG_FUNCTIONS
    std::cout << "<" << *sfname << "\n";
#endif
    return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
}

} // namespace otava::symbols
