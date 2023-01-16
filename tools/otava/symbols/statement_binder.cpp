// =================================
// Copyright (c) 2022 Seppo Laakko
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
import otava.symbols.argument.conversion.table;
import otava.symbols.bound.tree;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.exception;
import otava.symbols.expression.binder;
import otava.symbols.function.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.class_templates;

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

BoundFunctionCallNode* MakeDestructorCall(ClassTypeSymbol* cls, BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* dtorSymbol = GenerateDestructor(cls, sourcePos, context);
    if (dtorSymbol && dtorSymbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* dtorFunctionSymbol = static_cast<FunctionDefinitionSymbol*>(dtorSymbol);
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
    setVPtrStatementGenerated(false),
    postfix(false)
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
    GenerateSetVPtrStatement(sourcePos);
    if (setVPtrStatement)
    {
        ctorInitializer->SetSetVPtrStatement(setVPtrStatement.release());
    }
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
    GenerateSetVPtrStatement(sourcePos);
    if (setVPtrStatement)
    {
        dtorTerminator->SetSetVPtrStatement(setVPtrStatement.release());
    }
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
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", args, sourcePos, context);
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
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@destructor", args, sourcePos, context, ex);
    if (boundFunctionCall)
    {
        memberTerminators.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
    }
}

void StatementBinder::GenerateSetVPtrStatement(const soul::ast::SourcePos& sourcePos)
{
    if (!currentClass || !currentClass->IsPolymorphic() || setVPtrStatementGenerated) return;
    if (HasThisInitializer()) return;
    setVPtrStatementGenerated = true;
    if (!currentClass->ObjectLayoutComputed())
    {
        currentClass->MakeObjectLayout(context);
    }
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    ClassTypeSymbol* vptrHolderClass = currentClass->VPtrHolderClass();
    if (!vptrHolderClass)
    {
        ThrowException("vptr holder class not found", sourcePos, context);
    }
    if (vptrHolderClass != currentClass)
    {
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
            setVPtrStatement.reset(new BoundSetVPtrStatementNode(thisPtrConverted, currentClass, sourcePos));
        }
        else
        {
            ThrowException("vptr holder class conversion not found", sourcePos, context);
        }
    }
    else
    {
        setVPtrStatement.reset(new BoundSetVPtrStatementNode(thisPtr, currentClass, sourcePos));
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
    GenerateSetVPtrStatement(node.GetSourcePos());
    if (setVPtrStatement)
    {
        ctorInitializer->SetSetVPtrStatement(setVPtrStatement.release());
    }
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
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", args, sourcePos, context);
    memberInitializers.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
}

int StatementBinder::GetBaseInitializerOrTerminatorIndex(TypeSymbol* baseClass) const
{
    int n = currentClass->BaseClasses().size();
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* baseCls = currentClass->BaseClasses()[i];
        if (TypesEqual(baseCls, baseClass))
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
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@constructor", args, sourcePos, context);
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
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", initializerArgs, node.GetSourcePos(), context);
    if (index < 0)
    {
        baseInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
    else
    {
        memberInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
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
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor && !setVPtrStatementGenerated)
    {
        GenerateSetVPtrStatement(node.GetSourcePos());
        if (setVPtrStatement)
        {
            currentCompoundStatement->AddStatement(setVPtrStatement.release());
        }
    }
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* statementNode = node.Nodes()[i];
        BoundStatementNode* boundStatement = BindStatement(statementNode, functionDefinitionSymbol, context);
        currentCompoundStatement->AddStatement(boundStatement);
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    boundSwitchStatement->SetCondition(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundSwitchStatement->SetStatement(boundStmt);
    }
    SetStatement(boundSwitchStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
}

void StatementBinder::Visit(otava::ast::CaseStatementNode& node)
{
    BoundCaseStatementNode* boundCaseStatement = new BoundCaseStatementNode(node.GetSourcePos());
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context);
    boundCaseStatement->SetCaseExpr(caseExpr);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundCaseStatement->SetStatement(boundStmt);
    }
    SetStatement(boundCaseStatement);
}

void StatementBinder::Visit(otava::ast::DefaultStatementNode& node)
{
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
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
    BoundExpressionNode* condition = BindExpression(node.Expression(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    boundDoStatement->SetExpr(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundDoStatement->SetStatement(boundStmt);
    }
    SetStatement(boundDoStatement);
}

void StatementBinder::Visit(otava::ast::RangeForStatementNode& node)
{
    //auto initializer = node.Initializer()->Clone();
/*  int x = 0;
    soul::ast::SourcePos sourcePos = node.GetSourcePos();
    otava::ast::SimpleDeclarationNode* declaration = new otava::ast::SimpleDeclarationNode(sourcePos);
    otava::ast::DeclarationStatementNode* it = new otava::ast::DeclarationStatementNode(sourcePos, declaration);
    declaration->Add(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos, nullptr, nullptr, nullptr, nullptr, nullptr));
    otava::ast::InitDeclaratorListNode* initDeclList = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::IdentifierNode* begin = new otava::ast::IdentifierNode(sourcePos, U"begin");
    otava::ast::InvokeExprNode* invoke = new otava::ast::InvokeExprNode(sourcePos, begin);
    invoke->AddNode(node.Initializer()->Clone());
    otava::ast::AssignInitNode* assignInit = new otava::ast::AssignInitNode(sourcePos, invoke);
    otava::ast::InitializerNode* initializer = new otava::ast::InitializerNode(sourcePos, assignInit);
    otava::ast::InitDeclaratorNode* initDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, U"it", initializer);
    initDeclList->Add(initDeclarator);
    it.SetInitDeclaratorList(initDeclList);
*/
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
        BoundExpressionNode* condition = BindExpression(node.Condition(), context);
        if (!condition->GetType()->IsBoolType())
        {
            condition = MakeBoundBooleanConversionNode(condition, context);
        }
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
                std::unique_ptr<BoundFunctionCallNode> moveExpr = ResolveOverloadThrow(
                    scope, U"move", moveArgs, node.GetSourcePos(), context, OverloadResolutionFlags::dontSearchArgumentScopes);
                expression = moveExpr.release();
            }
            classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
            std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", classReturnArgs,
                node.GetSourcePos(), context);
            std::unique_ptr<BoundExpressionStatementNode> expressionStatement(new BoundExpressionStatementNode(node.GetSourcePos()));
            expressionStatement->SetExpr(constructorCall.release());
            SetStatement(expressionStatement.release());
        }
        else
        {
            TypeSymbol* returnType = functionDefinitionSymbol->ReturnType()->DirectType(context);
            if (returnType->IsReferenceType())
            {
                context->PushSetFlag(ContextFlags::returnRef);
            }
            BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context);
            if (!TypesEqual(returnValueExpr->GetType(), returnType))
            {
                if (TypesEqual(returnValueExpr->GetType()->PlainType(context), returnType->PlainType(context)))
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
                    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        returnType->DirectType(context), returnValueExpr->GetType(), node.GetSourcePos(), context);
                    if (conversion)
                    {
                        returnValueExpr = new BoundConversionNode(returnValueExpr, conversion, node.GetSourcePos());
                    }
                    else
                    {
                        ThrowException("no conversion found", node.GetSourcePos(), context);
                    }
                }
            }
            boundReturnStatement->SetExpr(returnValueExpr);
            if (returnType->IsReferenceType())
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
    BoundExpressionNode* expr = BindExpression(node.Expression(), context);
    boundExpressionStatement->SetExpr(expr);
    SetStatement(boundExpressionStatement);
}

void StatementBinder::Visit(otava::ast::DeclarationStatementNode& node)
{
    node.Declaration()->Accept(*this);
}

void StatementBinder::Visit(otava::ast::SimpleDeclarationNode& node)
{
    BoundCompoundStatementNode* boundCompoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
    std::unique_ptr<DeclarationList> declarationList = context->ReleaseDeclarationList(&node);
    if (declarationList)
    {
        for (auto& declaration : declarationList->declarations)
        {
            BoundExpressionNode* initializer = nullptr;
            if (declaration.initializer)
            {
                initializer = BindExpression(declaration.initializer, context);
            }
            VariableSymbol* variable = declaration.variable;
            if (initializer && initializer->GetType())
            {
                variable->SetInitializerType(initializer->GetType()->DirectType(context));
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
            std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", arguments,
                node.GetSourcePos(), context);
            BoundConstructionStatementNode* boundConstructionStatement = nullptr;
            otava::symbols::ClassTypeSymbol* cls = nullptr;
            BoundExpressionNode* firstArg = nullptr;
            if (constructorCall->CallsClassConstructor(cls, firstArg))
            {
                boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                otava::symbols::BoundFunctionCallNode* destructorCall = MakeDestructorCall(cls, firstArg, node.GetSourcePos(), context);
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
        SetStatement(boundCompoundStatement);
    }
    else
    {
        int x = 0;
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

BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    StatementBinder binder(context, functionDefinitionSymbol);
    statementNode->Accept(binder);
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    return boundStatement;
}

void BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    if (functionDefinitionSymbol->IsBound()) return;
    if (functionDefinitionSymbol->IsTemplate()) return;
    if (context->GetFlag(ContextFlags::parseMemberFunction)) return;
    functionDefinitionSymbol->SetBound();
    StatementBinder binder(context, functionDefinitionSymbol);
    functionDefinitionNode->Accept(binder);
}

} // namespace otava::symbols
