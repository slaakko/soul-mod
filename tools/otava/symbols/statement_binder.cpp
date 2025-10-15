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
import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.declaration;
import otava.symbols.exception;
import otava.symbols.expression.binder;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
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

bool InitializerLess::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first < right.first;
}

struct TerminatorGreater
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool TerminatorGreater::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first > right.first;
}

constexpr int maxBaseInitializers = 10000;

BoundExpressionNode* MakeBoundBooleanConversionNode(BoundExpressionNode* condition, Context* context)
{
    soul::ast::SourcePos sourcePos = condition->GetSourcePos();
    FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), sourcePos, context);
    if (!conversionFunction)
    {
        ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
    }
    if (conversionFunction->GetFunctionKind() == FunctionKind::conversionMemFn && condition->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        TypeSymbol* conditionType = condition->GetType();
        if (conditionType->IsReferenceType())
        {
            condition = new BoundRefToPtrNode(condition, sourcePos, conditionType->RemoveReference(context)->AddPointer(context));
        }
        else
        {
            condition = new BoundAddressOfNode(condition, sourcePos, conditionType->GetBaseType()->AddPointer(context));
        }
        BoundFunctionCallNode* functionCall = new BoundFunctionCallNode(conversionFunction, sourcePos, conversionFunction->ReturnType());
        functionCall->AddArgument(condition);
        return functionCall;
    }
    return new BoundConversionNode(condition, conversionFunction, sourcePos);
}

BoundFunctionCallNode* MakeDestructorCall(ClassTypeSymbol* cls, BoundExpressionNode* arg, FunctionDefinitionSymbol* destructor, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* dtorSymbol = nullptr;
    if (destructor)
    {
        dtorSymbol = destructor;
    }
    else
    {
        dtorSymbol = GenerateDestructor(cls, sourcePos, context);
    }
    if (dtorSymbol && (dtorSymbol->IsFunctionSymbol() || dtorSymbol->IsExplicitlyInstantiatedFunctionDefinitionSymbol()))
    {
        FunctionSymbol* dtorFunctionSymbol = static_cast<FunctionSymbol*>(dtorSymbol);
        if (dtorFunctionSymbol->GetFlag(FunctionSymbolFlags::trivialDestructor))
        {
            return nullptr;
        }
        std::string dtorIrName = dtorSymbol->IrName(context);
        std::unique_ptr<BoundFunctionCallNode> destructorCall(new BoundFunctionCallNode(dtorFunctionSymbol, sourcePos, cls));
        destructorCall->AddArgument(arg->Clone());
        return destructorCall.release();
    }
    return nullptr;
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
    Symbol* symbol = context->GetSymbolTable()->GetSymbol(&node);
    SpecialFunctionKind specialFunctionKind = functionDefinitionSymbol->GetSpecialFunctionKind(context);
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
                        functionDefinitionSymbol = GenerateClassDefaultCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassCopyCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassMoveCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassCopyAssignment(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassMoveAssignment(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                }
                std::unique_ptr<BoundFunctionNode> boundFunction(context->ReleaseBoundFunction());
                context->GetBoundCompileUnit()->AddBoundNode(std::move(boundFunction), context);
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
    context->GetSymbolTable()->BeginScopeGeneric(symbol->GetScope(), context);
    node.FunctionBody()->Accept(*this);
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor)
    {
        currentClass->SetHasUserDefinedConstructor();
        if (!ctorInitializer)
        {
            GenerateDefaultCtorInitializer(node.GetSourcePos());
        }
    }
    else if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::destructor)
    {
        currentClass->SetHasUserDefinedDestructor();
        GenerateDestructorTerminator(node.GetSourcePos());
    }
    context->GetSymbolTable()->EndScopeGeneric(context);
    functionDefinitionSymbol->CheckGenerateClassCopyCtor(node.GetSourcePos(), context);
}

void StatementBinder::Visit(otava::ast::ConstructorNode& node)
{
    node.Left()->Accept(*this);
    if (ctorInitializer)
    {
        context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
    }
    node.Right()->Accept(*this);
    context->GetBoundFunction()->SetBody(static_cast<BoundCompoundStatementNode*>(boundStatement));
    AddConvertingConstructorToConversionTable(functionDefinitionSymbol, node.GetSourcePos(), context);
}

void StatementBinder::Visit(otava::ast::ConstructorInitializerNode& node)
{
    ctorInitializer = new BoundCtorInitializerNode(node.GetSourcePos());
    node.MemberInitializerListNode()->Accept(*this);
}

void StatementBinder::GenerateDefaultCtorInitializer(const soul::ast::SourcePos& sourcePos)
{
    ctorInitializer = new BoundCtorInitializerNode(sourcePos);
    CompleteBaseInitializers(sourcePos);
    std::sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    GenerateSetVPtrStatements(sourcePos);
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    CompleteMemberInitializers(sourcePos);
    std::sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
    context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
}

void StatementBinder::GenerateDestructorTerminator(const soul::ast::SourcePos& sourcePos)
{
    dtorTerminator = new BoundDtorTerminatorNode(sourcePos);
    GenerateSetVPtrStatements(sourcePos);
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        dtorTerminator->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    GenerateBaseTerminators(sourcePos);
    GenerateMemberTerminators(sourcePos);
    std::sort(memberTerminators.begin(), memberTerminators.end(), TerminatorGreater());
    for (auto& terminator : memberTerminators)
    {
        dtorTerminator->AddMemberTerminator(terminator.second.release());
    }
    context->GetBoundFunction()->SetDtorTerminator(dtorTerminator);
}

void StatementBinder::GenerateBaseTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (const auto& baseClass : currentClass->BaseClasses())
        {
            int index = GetBaseInitializerOrTerminatorIndex(baseClass);
            AddBaseTerminator(baseClass, index, sourcePos);
        }
    }
}

void StatementBinder::AddBaseTerminator(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    OperationFlags preConversionFlags = OperationFlags::none;
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
    if (conversion)
    {
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
        memberTerminators.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
    else
    {
        ThrowException("base class conversion not found", sourcePos, context);
    }
}

void StatementBinder::GenerateMemberTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (const auto& mermberVar : currentClass->MemberVariables())
        {
            AddMemberTerminator(mermberVar, sourcePos);
        }
    }
}

void StatementBinder::AddMemberTerminator(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    TypeSymbol* memberVarType = memberVar->GetType();
    if (memberVarType->IsPointerType() || memberVarType->IsReferenceType()) return;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    boundVariableNode->SetThisPtr(thisPtr);
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
    Exception ex;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context, ex);
    if (boundFunctionCall)
    {
        memberTerminators.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
    }
}

void StatementBinder::GenerateSetVPtrStatements(const soul::ast::SourcePos& sourcePos)
{
    if (!currentClass || !currentClass->IsPolymorphic() || setVPtrStatementsGenerated) return;
    if (HasThisInitializer()) return;
    context->GetBoundCompileUnit()->AddBoundNodeForClass(currentClass, sourcePos, context);
    setVPtrStatementsGenerated = true;
    if (!currentClass->ObjectLayoutComputed())
    {
        currentClass->MakeObjectLayout(sourcePos, context);
    }
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    std::vector<ClassTypeSymbol*> vptrHolderClasses = currentClass->VPtrHolderClasses();
    if (vptrHolderClasses.empty())
    {
        ThrowException("no vptr holder classes for the class '" + util::ToUtf8(currentClass->FullName()) + "'", sourcePos, context);
    }
    for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
    {
        if (vptrHolderClass != currentClass)
        {
            FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
            if (conversion)
            {
                BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr->Clone(), conversion, sourcePos);
                setVPtrStatements.push_back(std::unique_ptr<BoundSetVPtrStatementNode>(
                    new BoundSetVPtrStatementNode(thisPtrConverted, currentClass, vptrHolderClass, sourcePos)));
            }
            else
            {
                ThrowException("vptr holder class conversion not found", sourcePos, context);
            }
        }
        else
        {
            setVPtrStatements.push_back(std::unique_ptr<BoundSetVPtrStatementNode>(new BoundSetVPtrStatementNode(thisPtr->Clone(), currentClass, currentClass, sourcePos)));
        }
    }
}

void StatementBinder::Visit(otava::ast::MemberInitializerListNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* initializer = node.Items()[i];
        initializer->Accept(*this);
    }
    CompleteBaseInitializers(node.GetSourcePos());
    std::sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    GenerateSetVPtrStatements(node.GetSourcePos());
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    CompleteMemberInitializers(node.GetSourcePos());
    std::sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
}

void StatementBinder::CompleteMemberInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return;
        for (const auto& memberVar : currentClass->MemberVariables())
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
                AddDefaultMemberInitializer(memberVar, sourcePos);
            }
        }
    }
}

void StatementBinder::AddDefaultMemberInitializer(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    boundVariableNode->SetThisPtr(thisPtr);
    std::vector<TypeSymbol*> templateArgs;
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
    memberInitializers.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
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

void StatementBinder::CompleteBaseInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return;
        for (const auto& baseClass : currentClass->BaseClasses())
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
                AddDefaultBaseInitializer(baseClass, index, sourcePos);
            }
        }
    }
}

void StatementBinder::AddDefaultBaseInitializer(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
    if (conversion)
    {
        std::vector<TypeSymbol*> templateArgs;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
        baseInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall))); 
    }
    else
    {
        ThrowException("base class conversion not found", sourcePos, context);
    }
}

void StatementBinder::Visit(otava::ast::MemberInitializerNode& node)
{
    initializerArgs.clear();
    classTypeSymbol = nullptr;
    memberVariableSymbol = nullptr;
    int index = -1;
    resolveClass = true;
    node.Left()->Accept(*this);
    resolveClass = false;
    if (classTypeSymbol)
    {
        BoundExpressionNode* thisPtr = context->GetThisPtr(node.GetSourcePos());
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            classTypeSymbol->AddPointer(context), thisPtr->GetType(), node.GetSourcePos(), context);
        if (conversion)
        {
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, node.GetSourcePos())));
        }
        else
        {
            ThrowException("base class conversion not found", node.GetSourcePos(), context);
        }
        index = GetBaseInitializerOrTerminatorIndex(classTypeSymbol);
    }
    else
    {
        resolveMemberVariable = true;
        node.Left()->Accept(*this);
        resolveMemberVariable = false;
        initializerArgs.clear();
        if (memberVariableSymbol)
        {
            BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVariableSymbol, node.GetSourcePos());
            ParameterSymbol* thisParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(context);
            BoundParameterNode* thisPtr = new BoundParameterNode(thisParam, node.GetSourcePos(), thisParam->GetType());
            boundVariableNode->SetThisPtr(thisPtr);
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(
                new BoundDefaultInitNode(boundVariableNode, node.GetSourcePos()), node.GetSourcePos(), boundVariableNode->GetType()->AddPointer(context))));
            index = memberVariableSymbol->Index();
        }
    }
    resolveInitializerArguments = true;
    node.Right()->Accept(*this);
    resolveInitializerArguments = false;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, initializerArgs, node.GetSourcePos(), context);
    if (index < 0)
    {
        baseInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
    else
    {
        memberInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
}

void StatementBinder::Visit(otava::ast::TemplateIdNode& node)
{
    if (resolveClass)
    {
        TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context, TypeResolverFlags::none);
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
        Symbol* symbol = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
        if (symbol && symbol->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
        }
    }
    else if (resolveMemberVariable)
    {
        Symbol* symbol = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::variableSymbolGroup, node.GetSourcePos(), context);
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
            BoundExpressionNode* arg = BindExpression(item, context);
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
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor && !setVPtrStatementsGenerated)
    {
        GenerateSetVPtrStatements(node.GetSourcePos());
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
        BoundStatementNode* boundStatement = BindStatement(statementNode, functionDefinitionSymbol, context);
        if (boundStatement)
        {
            currentCompoundStatement->AddStatement(boundStatement);
        }
    }
    context->GetSymbolTable()->EndScopeGeneric(context);
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
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundIfStatementNode* boundIfStatement = new BoundIfStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (boundInitStatement)
        {
            boundIfStatement->SetInitStatement(boundInitStatement);
        }
    }

    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    context->PopFlags();
    boundIfStatement->SetCondition(condition);
    BoundStatementNode* boundThenStatement = BindStatement(node.ThenStatement(), functionDefinitionSymbol, context);
    if (boundThenStatement)
    {
        boundIfStatement->SetThenStatement(boundThenStatement);
    }
    if (node.ElseStatement())
    {
        BoundStatementNode* boundElseStatement = BindStatement(node.ElseStatement(), functionDefinitionSymbol, context);
        if (boundElseStatement)
        {
            boundIfStatement->SetElseStatement(boundElseStatement);
        }
    }
    SetStatement(boundIfStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
}

void StatementBinder::Visit(otava::ast::SwitchStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundSwitchStatementNode* boundSwitchStatement = new BoundSwitchStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (boundInitStatement)
        {
            boundSwitchStatement->SetInitStatement(boundInitStatement);
        }
    }
    // todo!!!
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    boundSwitchStatement->SetCondition(condition);
    context->PopFlags();
    context->PushSwitchCondType(condition->GetType());
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    context->PopSwitchCondType();
    if (boundStmt)
    {
        boundSwitchStatement->SetStatement(boundStmt);
    }
    SetStatement(boundSwitchStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
}

void StatementBinder::Visit(otava::ast::CaseStatementNode& node)
{
    if (!TerminatesCaseOrDefault(node.Statement()))
    {
        PrintWarning("case statement does not terminate in return, break or continue statement", node.GetSourcePos(), context);
    }
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context);
    TypeSymbol* switchCondType = context->GetSwitchCondType();
    if (!TypesEqual(caseExpr->GetType(), switchCondType, context))
    {
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            switchCondType, caseExpr->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context), node.GetSourcePos(), context);
        if (conversion)
        {
            caseExpr = new BoundConversionNode(caseExpr, conversion, node.GetSourcePos());
        }
        else
        {
            ThrowException("no conversion found", node.GetSourcePos(), context);
        }
    }
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
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
        PrintWarning("default statement does not terminate in return, break or continue statement", node.GetSourcePos(), context);
    }
    BoundDefaultStatementNode* boundDefaultStatement = new BoundDefaultStatementNode(node.GetSourcePos());
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
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
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundWhileStatementNode* boundWhileStatement = new BoundWhileStatementNode(node.GetSourcePos());
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    context->PopFlags();
    boundWhileStatement->SetCondition(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundWhileStatement->SetStatement(boundStmt);
    }
    SetStatement(boundWhileStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
}

void StatementBinder::Visit(otava::ast::DoStatementNode& node)
{
    BoundDoStatementNode* boundDoStatement = new BoundDoStatementNode(node.GetSourcePos());
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Expression(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    context->PopFlags();
    boundDoStatement->SetExpr(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
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
        rangeForCompound->AddNode(node.InitStatement()->Clone());
    }
    otava::ast::DeclSpecifierSequenceNode* endIteratorDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    endIteratorDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    otava::ast::InitDeclaratorListNode* endIteratorDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::IdentifierNode* endIteratorDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@end");
    otava::ast::Node* invokeChild = node.Initializer()->Clone();
    otava::ast::IdentifierNode* invokeId = new otava::ast::IdentifierNode(sourcePos, U"end");
    otava::ast::MemberExprNode* invokeSubject = new otava::ast::MemberExprNode(sourcePos, invokeChild, new otava::ast::DotNode(sourcePos), invokeId);
    otava::ast::InvokeExprNode* endIteratorInitializer = new otava::ast::InvokeExprNode(sourcePos, invokeSubject);
    otava::ast::AssignmentInitNode* endIteratorAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, endIteratorInitializer);
    otava::ast::InitDeclaratorNode* endIteratorInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, endIteratorDeclarator, endIteratorAssignmentInitializer);
    endIteratorDeclarators->AddNode(endIteratorInitDeclarator);
    otava::ast::SimpleDeclarationNode* endIteratorDeclaration = new otava::ast::SimpleDeclarationNode(sourcePos, endIteratorDeclSpecifiers, endIteratorDeclarators, nullptr, nullptr);
    rangeForCompound->AddNode(endIteratorDeclaration);
    otava::ast::DeclSpecifierSequenceNode* forInitDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    forInitDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    otava::ast::InitDeclaratorListNode* forInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::Node* forInitInvokeChild = node.Initializer()->Clone();
    otava::ast::MemberExprNode* forInitInvokeSubject = new otava::ast::MemberExprNode(sourcePos, forInitInvokeChild, new otava::ast::DotNode(sourcePos), 
        new otava::ast::IdentifierNode(sourcePos, U"begin"));
    otava::ast::InvokeExprNode* forInitInitializer = new otava::ast::InvokeExprNode(sourcePos, forInitInvokeSubject);
    otava::ast::AssignmentInitNode* forInitAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, forInitInitializer);
    otava::ast::IdentifierNode* forInitDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@it");
    otava::ast::InitDeclaratorNode* forInitInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, forInitDeclarator, forInitAssignmentInitializer);
    forInitDeclarators->AddNode(forInitInitDeclarator);
    otava::ast::SimpleDeclarationNode* forInitStmt = new otava::ast::SimpleDeclarationNode(sourcePos, forInitDeclSpecifiers, forInitDeclarators, nullptr, nullptr);
    otava::ast::BinaryExprNode* forCond = new otava::ast::BinaryExprNode(sourcePos, new otava::ast::NotEqualNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it"),
        new otava::ast::IdentifierNode(sourcePos, U"@end"));
    otava::ast::UnaryExprNode* forLoopExpr = new otava::ast::UnaryExprNode(sourcePos, new otava::ast::PrefixIncNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it"));
    otava::ast::CompoundStatementNode* forActionStmt = new otava::ast::CompoundStatementNode(sourcePos);
    RangeForDeclarationExtractor extractor;
    node.Declaration()->Accept(extractor);
    otava::ast::DeclSpecifierSequenceNode* forActionDeclSpecifiers = extractor.GetDeclSpecifierSequence();
    otava::ast::Node* declarator = extractor.GetDeclarator();
    otava::ast::AssignmentInitNode* forActionAssignmentInit = new otava::ast::AssignmentInitNode(sourcePos, new otava::ast::UnaryExprNode(sourcePos, 
        new otava::ast::DerefNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it")));
    otava::ast::InitDeclaratorNode* forActionInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, declarator->Clone(), forActionAssignmentInit);
    otava::ast::InitDeclaratorListNode* forActionInitDeclaratorList = new otava::ast::InitDeclaratorListNode(sourcePos);
    forActionInitDeclaratorList->AddNode(forActionInitDeclarator);
    otava::ast::SimpleDeclarationNode* forActionDeclaration = new otava::ast::SimpleDeclarationNode(sourcePos, forActionDeclSpecifiers->Clone(), forActionInitDeclaratorList, nullptr, nullptr);
    otava::ast::DeclarationStatementNode* forActionDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, forActionDeclaration);
    forActionStmt->AddNode(forActionDeclarationStmt);
    forActionStmt->AddNode(node.Statement()->Clone());
    otava::ast::ForStatementNode* forStmt = new otava::ast::ForStatementNode(sourcePos, forInitStmt, forCond, forLoopExpr, forActionStmt, nullptr, nullptr,
        sourcePos, sourcePos, sourcePos);
    rangeForCompound->AddNode(forStmt);
    InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
    Instantiator instantiator(context, &instantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    rangeForCompound->Accept(instantiator);
    context->PopFlags();
    rangeForCompound->Accept(*this);
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
}

void StatementBinder::Visit(otava::ast::ForStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundForStatementNode* boundForStatement = new BoundForStatementNode(node.GetSourcePos());
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (boundInitStatement)
        {
            boundForStatement->SetInitStatement(boundInitStatement);
        }
    }
    if (node.Condition())
    {
        context->PushResetFlag(ContextFlags::returnRef);
        BoundExpressionNode* condition = BindExpression(node.Condition(), context);
        if (!condition->GetType()->IsBoolType())
        {
            condition = MakeBoundBooleanConversionNode(condition, context);
        }
        context->PopFlags();
        boundForStatement->SetCondition(condition);
    }
    if (node.LoopExpr())
    {
        BoundExpressionNode* loopExpr = BindExpression(node.LoopExpr(), context);
        boundForStatement->SetLoopExpr(loopExpr);
    }
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundForStatement->SetStatement(boundStmt);
    }
    SetStatement(boundForStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
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
    BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(node.GetSourcePos());
    if (node.ReturnValue())
    {
        if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnsClass())
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> classReturnArgs;
            ParameterSymbol* returnValueParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnValueParam();
            classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundParameterNode(returnValueParam,
                node.GetSourcePos(), returnValueParam->GetReferredType(context))));
            BoundExpressionNode* expression = BindExpression(node.ReturnValue(), context);
            if (expression->IsBoundLocalVariable())
            {
                std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
                moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
                Scope* scope = context->GetSymbolTable()->GetNamespaceScope(U"std", node.GetSourcePos(), context);
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> moveExpr = ResolveOverloadThrow(
                    scope, U"move", templateArgs, moveArgs, node.GetSourcePos(), context, OverloadResolutionFlags::dontSearchArgumentScopes);
                expression = moveExpr.release();
            }
            classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
            std::vector<TypeSymbol*> templateArgs;
            std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, classReturnArgs,
                node.GetSourcePos(), context);
            std::unique_ptr<BoundExpressionStatementNode> expressionStatement(new BoundExpressionStatementNode(node.GetSourcePos()));
            expressionStatement->SetExpr(constructorCall.release(), node.GetSourcePos(), context);
            SetStatement(expressionStatement.release());
        }
        else
        {
            TypeSymbol* returnType = functionDefinitionSymbol->ReturnType()->DirectType(context)->FinalType(node.GetSourcePos(), context);
            bool flagsPushed = false;
            if (returnType->IsReferenceType())
            {
                context->PushSetFlag(ContextFlags::returnRef);
                flagsPushed = true;
            }
            BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context);
            if (!TypesEqual(returnValueExpr->GetType(), returnType, context))
            {
                if (TypesEqual(returnValueExpr->GetType()->PlainType(context), returnType->PlainType(context), context))
                {
                    if (!(
                        returnType->IsLValueRefType() && returnValueExpr->GetType()->IsRValueRefType() || 
                        returnType->IsRValueRefType() && returnValueExpr->GetType()->IsLValueRefType()))
                    {

                        if (returnType->IsLValueRefType())
                        {
                            returnValueExpr = new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->AddLValueRef(context));
                        }
                        else if (returnValueExpr->GetType()->IsLValueRefType())
                        {
                            returnValueExpr = new BoundDereferenceNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->RemoveReference(context));
                        }
                    }
                }
                else
                {
                    ArgumentMatch argumentMatch;
                    FunctionMatch functionMatch;
                    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        returnType, returnValueExpr->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context), returnValueExpr, node.GetSourcePos(), argumentMatch, 
                        functionMatch, context);
                    if (conversion)
                    {
                        if (argumentMatch.preConversionFlags == OperationFlags::addr)
                        {
                            returnValueExpr = new BoundConversionNode(
                                new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->AddPointer(context)), conversion, node.GetSourcePos());
                        }
                        else
                        {
                            returnValueExpr = new BoundConversionNode(returnValueExpr, conversion, node.GetSourcePos());
                        }
                    }
                    else
                    {
                        ThrowException("no conversion found", node.GetSourcePos(), context);
                    }
                }
            }
            boundReturnStatement->SetExpr(returnValueExpr, node.GetSourcePos(), context);
            if (flagsPushed)
            {
                context->PopFlags();
            }
        }
    }
    SetStatement(boundReturnStatement);
}

void StatementBinder::Visit(otava::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode(node.GetSourcePos());
    if (node.Expression())
    {
        BoundExpressionNode* expr = BindExpression(node.Expression(), context);
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
                        PrintWarning("discarding return value of function '" + util::ToUtf8(fn->FullName()) + "", node.GetSourcePos(), context);
                    }
                }
            }
        }
        boundExpressionStatement->SetExpr(expr, node.GetSourcePos(), context);
    }
    SetStatement(boundExpressionStatement);
}

void StatementBinder::Visit(otava::ast::DeclarationStatementNode& node)
{
    node.Declaration()->Accept(*this);
}

void StatementBinder::Visit(otava::ast::AliasDeclarationNode& node)
{
    ProcessAliasDeclaration(&node, context);
}

void StatementBinder::Visit(otava::ast::SimpleDeclarationNode& node)
{
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
                BindStaticLocalVariable(variable, declaration.initializer, &node);
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
                    initializer = BindExpression(declaration.initializer, context);
                    context->SetDeclaredInitializerType(nullptr);
                    if (flagsPushed)
                    {
                        context->PopFlags();
                    }
                }
                if (initializer && initializer->GetType())
                {
                    TypeSymbol* initializerType = initializer->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context);
                    if (variable->GetDeclaredType()->GetBaseType()->IsAutoTypeSymbol() && variable->GetDeclaredType()->GetDerivations() != Derivations::none)
                    {
                        initializerType = context->GetSymbolTable()->MakeCompoundType(initializerType->GetBaseType(), variable->GetDeclaredType()->GetDerivations());
                    }
                    variable->SetInitializerType(initializerType);
                }
                BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
                std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, node.GetSourcePos(), boundVariable->GetType()->AddPointer(context))));
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
                std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, arguments,
                    node.GetSourcePos(), context);
                BoundConstructionStatementNode* boundConstructionStatement = nullptr;
                otava::symbols::ClassTypeSymbol* cls = nullptr;
                BoundExpressionNode* firstArg = nullptr;
                FunctionDefinitionSymbol* destructor = nullptr;
                if (constructorCall->CallsClassConstructor(cls, firstArg, destructor))
                {
                    boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                    otava::symbols::BoundFunctionCallNode* destructorCall = MakeDestructorCall(cls, firstArg, destructor, node.GetSourcePos(), context);
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
    declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    initDeclarators = new otava::ast::InitDeclaratorListNode(node.GetSourcePos());
    node.DeclarationSpecifiers()->Accept(*this);
    node.InitDeclaratorList()->Accept(*this);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::DeclSpecifierSequenceNode& node)
{
    for (const auto& declSpecifierNode : node.Nodes())
    {
        if (declSpecifierNode->IsStaticNode())
        {
            continue;
        }
        declSpecifiers->AddNode(declSpecifierNode->Clone());
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(node.Clone());
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::IdentifierNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(globalVarId->Clone());
    }
    else
    {
        declaratorNode = globalVarId->Clone();
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(globalVarId->Clone());
    }
    else
    {
        declaratorNode = globalVarId->Clone();
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrDeclaratorNode& node)
{
    ptrDeclaratorNode = new otava::ast::PtrDeclaratorNode(sourcePos);
    for (const auto& node : node.Nodes())
    {
        node->Accept(*this);
    }
    initDeclarators->AddNode(ptrDeclaratorNode);
    ptrDeclaratorNode = nullptr;
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::ArrayDeclaratorNode& node)
{
    node.Child()->Accept(*this);
    otava::ast::Node* dimension = nullptr;
    if (node.Dimension())
    {
        dimension = node.Dimension()->Clone();
    }
    declaratorNode = new otava::ast::ArrayDeclaratorNode(sourcePos, declaratorNode, dimension, sourcePos, sourcePos);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorNode& node)
{
    node.Left()->Accept(*this);
    if (isArrayVar)
    {
        declaratorNode = new otava::ast::InitDeclaratorNode(sourcePos, declaratorNode, node.Right()->Clone());
    }
    if (declaratorNode)
    {
        initDeclarators->AddNode(declaratorNode);
        declaratorNode = nullptr;
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorListNode& node)
{
    for (const auto& declNode : node.Nodes())
    {
        declNode->Accept(*this);
        if (declaratorNode)
        {
            initDeclarators->AddNode(declaratorNode);
            declaratorNode = nullptr;
        }
    }
}

void StatementBinder::Visit(otava::ast::BoundStatementNode& node)
{
    SetStatement(static_cast<BoundStatementNode*>(node.GetBoundStatementNode()));
}

void StatementBinder::BindStaticLocalVariable(VariableSymbol* variable, otava::ast::Node* initializerNode, otava::ast::SimpleDeclarationNode* declarationNode)
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
    std::string shaMaterial = util::ToUtf8(functionDefinitionSymbol->FullName());
    if (!functionDefinitionSymbol->Specialization().empty())
    {
        for (const auto& type : functionDefinitionSymbol->Specialization())
        {
            shaMaterial.append(".").append(util::ToUtf8(type->FullName()));
        }
    }
    shaMaterial.append(".").append(context->GetBoundCompileUnit()->Id());
    std::string sha = util::GetSha1MessageDigest(shaMaterial);
    otava::ast::Node* atomicBoolType = MakeTypeNameNodes(sourcePos, U"std::atomic_bool");
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    declSpecifiers->AddNode(atomicBoolType);
    otava::ast::InitDeclaratorListNode* initDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    std::unique_ptr<otava::ast::IdentifierNode> initializedVarName(new otava::ast::IdentifierNode(sourcePos, variable->Name() + U"_initialized_" + util::ToUtf32(sha)));
    initDeclarators->AddNode(initializedVarName->Clone());
    std::unique_ptr<otava::ast::SimpleDeclarationNode> initializedVarDeclaration(new otava::ast::SimpleDeclarationNode(sourcePos, declSpecifiers, initDeclarators, nullptr, nullptr));
    context->GetSymbolTable()->BeginScope(context->GetSymbolTable()->GlobalNs()->GetScope());
    ProcessSimpleDeclaration(initializedVarDeclaration.get(), nullptr, context);
    std::u32string globalStaticVarName = variable->Name() + U"_global_" + util::ToUtf32(sha);
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
    ProcessSimpleDeclaration(globalStaticVarDeclaration.get(), nullptr, context);
    context->PopFlags();
    context->GetSymbolTable()->EndScope();
    std::unique_ptr<otava::ast::CompoundStatementNode> compound1;
    std::unique_ptr<otava::ast::UnaryExprNode> inititalizedCond;
    std::unique_ptr<otava::ast::CompoundStatementNode> compound2;
    if (!isArrayVar)
    {
        compound1.reset(new otava::ast::CompoundStatementNode(sourcePos));
        otava::ast::TemplateIdNode* lockGuardType = new otava::ast::TemplateIdNode(sourcePos, MakeTypeNameNodes(sourcePos, U"std::lock_guard"));
        lockGuardType->AddNode(MakeTypeNameNodes(sourcePos, U"std::recursive_mutex"));
        otava::ast::DeclSpecifierSequenceNode* lockGuardDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
        lockGuardDeclSpecifiers->AddNode(lockGuardType);
        otava::ast::InitDeclaratorListNode* lockGuardInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
        otava::ast::Node* getInitLock = MakeTypeNameNodes(sourcePos, U"std::get_init_lock");
        otava::ast::InvokeExprNode* lockInit(new otava::ast::InvokeExprNode(sourcePos, getInitLock));
        otava::ast::InitDeclaratorNode* lockGuardInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, new otava::ast::IdentifierNode(sourcePos, U"lock"), lockInit);
        lockGuardInitDeclarators->AddNode(lockGuardInitDeclarator);
        std::unique_ptr<otava::ast::SimpleDeclarationNode> lockGuardDeclaration(new otava::ast::SimpleDeclarationNode(sourcePos, lockGuardDeclSpecifiers, lockGuardInitDeclarators,
            nullptr, nullptr));
        otava::ast::DeclarationStatementNode* lockGuardDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, lockGuardDeclaration.release());
        compound1->AddNode(lockGuardDeclarationStmt);
        inititalizedCond.reset(new otava::ast::UnaryExprNode(sourcePos, new otava::ast::NotNode(sourcePos), initializedVarName->Clone()));
        compound2.reset(new otava::ast::CompoundStatementNode(sourcePos));
    }
    globalStaticVariableSymbol = nullptr;
    Symbol* symbol = context->GetSymbolTable()->Lookup(globalStaticVarName, SymbolGroupKind::variableSymbolGroup, sourcePos, context);
    if (symbol && symbol->IsVariableSymbol())
    {
        globalStaticVariableSymbol = static_cast<VariableSymbol*>(symbol);
    }
    else
    {
        ThrowException("function static global not found", sourcePos, context);
    }
    if (!isArrayVar)
    {
        BoundVariableNode* boundVariable = new BoundVariableNode(globalStaticVariableSymbol, sourcePos);
        std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
        arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, sourcePos, boundVariable->GetType()->AddPointer(context))));
        BoundExpressionNode* initializer = nullptr;
        if (initializerNode)
        {
            initializer = BindExpression(initializerNode, context);
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
        std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, arguments,
            sourcePos, context);
        constructFunctionStaticStatement.reset(new BoundExpressionStatementNode(sourcePos));
        constructFunctionStaticStatement->SetExpr(constructorCall.release(), sourcePos, context);
        otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(constructFunctionStaticStatement.release(), sourcePos);
        compound2->AddNode(boundStatement);
        std::unique_ptr<BoundFunctionCallNode> atExitCall = MakeAtExitForVariable(globalStaticVariableSymbol, sourcePos, context);
        if (atExitCall)
        {
            atExitStatement.reset(new BoundExpressionStatementNode(sourcePos));
            atExitStatement->SetExpr(atExitCall.release(), sourcePos, context);
            otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(atExitStatement.release(), sourcePos);
            compound2->AddNode(boundStatement);
        }
        otava::ast::BinaryExprNode* setInitializedToTrueExpr = new otava::ast::BinaryExprNode(sourcePos, new otava::ast::AssignNode(sourcePos), initializedVarName->Clone(),
            new otava::ast::BooleanLiteralNode(sourcePos, true, U"true"));
        std::unique_ptr<otava::ast::ExpressionStatementNode> setInitializedToTrueStmt(new otava::ast::ExpressionStatementNode(sourcePos, setInitializedToTrueExpr, nullptr, nullptr));
        compound2->AddNode(setInitializedToTrueStmt.release());
        std::unique_ptr<otava::ast::IfStatementNode> innerIf(new otava::ast::IfStatementNode(sourcePos, nullptr, inititalizedCond->Clone(), compound2.release(), nullptr, nullptr,
            sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        compound1->AddNode(innerIf.release());
        std::unique_ptr<otava::ast::IfStatementNode> ifStmt(new otava::ast::IfStatementNode(sourcePos, nullptr, inititalizedCond->Clone(), compound1.release(), nullptr, nullptr,
            sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
        Instantiator instantiator(context, &instantiationScope);
        context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
        ifStmt->Accept(instantiator);
        context->PopFlags();
        BoundStatementNode* boundIfStmt = BindStatement(ifStmt.get(), functionDefinitionSymbol, context);
        SetStatement(boundIfStmt);
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    }
    context->SetDeclaredInitializerType(nullptr);
    variable->SetGlobal(globalStaticVariableSymbol);
}

BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    StatementBinder binder(context, functionDefinitionSymbol);
    statementNode->Accept(binder);
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    return boundStatement;
}

FunctionDefinitionSymbol* BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    if (functionDefinitionSymbol->GroupName() == U"GenerateCode" && functionDefinitionSymbol->ThisParam(context) && 
        functionDefinitionSymbol->ThisParam(context)->GetType()->GetBaseType()->Name() == U"DerivedToBaseConversion")
    {
        int x = 0;
    }
    RemoveTemporaryAliasTypeSymbols(context);
    if (functionDefinitionSymbol->IsBound()) return functionDefinitionSymbol;
    if (functionDefinitionSymbol->IsTemplate()) return functionDefinitionSymbol;
    if (context->GetFlag(ContextFlags::parseMemberFunction)) return functionDefinitionSymbol;
    std::set<const Symbol*> visited;
    if (functionDefinitionSymbol->IsTemplateParameterInstantiation(context, visited)) return functionDefinitionSymbol;
    functionDefinitionSymbol->SetBound();
    StatementBinder binder(context, functionDefinitionSymbol);
    functionDefinitionNode->Accept(binder);
    functionDefinitionSymbol = binder.GetFunctionDefinitionSymbol();
    bool hasNoReturnAttribute = false;
    if (functionDefinitionNode->IsFunctionDefinitionNode())
    {
        hasNoReturnAttribute = HasNoReturnAttribute(static_cast<otava::ast::FunctionDefinitionNode*>(functionDefinitionNode)->Attributes());
    }
    if (functionDefinitionSymbol->ReturnType() && 
        !functionDefinitionSymbol->ReturnType()->IsVoidType() && 
        functionDefinitionSymbol->GroupName() != U"main" && 
        !hasNoReturnAttribute)
    {
        CheckFunctionReturnPaths(functionDefinitionNode, context);
    }
    return functionDefinitionSymbol;
}

} // namespace otava::symbols
