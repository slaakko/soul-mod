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

namespace otava::symbols {

struct MemberInitializerLess
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool MemberInitializerLess::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first < right.first;
}

StatementBinder::StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) : 
    context(context_), 
    ctorInitializer(nullptr),
    boundStatement(nullptr),
    functionDefinitionSymbol(functionDefinitionSymbol_),
    classTypeSymbol(nullptr),
    memberVariableSymbol(nullptr),
    resolveClass(false),
    resolveMemberVariable(false),
    resolveInitializerArguments(false),
    postfix(false)
{
}

void StatementBinder::CompileStatement(otava::ast::Node* statementNode, bool setPostfix)
{
    bool prevPostfix = postfix;
    postfix = setPostfix;
    statementNode->Accept(*this);
    postfix = prevPostfix;
}

void StatementBinder::Visit(otava::ast::FunctionDefinitionNode& node)
{
    Symbol* symbol = context->GetSymbolTable()->GetSymbol(&node);
    if (node.FunctionBody()->IsDefaultedOrDeletedFunctionNode())
    {
        if (symbol->IsFunctionDefinitionSymbol())
        {
            FunctionDefinitionSymbol* definition = static_cast<FunctionDefinitionSymbol*>(symbol);
            otava::ast::DefaultedOrDeletedFunctionNode* bodyNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
            if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::defaultNode)
            {
                definition->SetFunctionQualifiers(definition->Qualifiers() | FunctionQualifiers::isDefault);
            }
            else if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::deleteNode)
            {
                definition->SetFunctionQualifiers(definition->Qualifiers() | FunctionQualifiers::isDeleted);
            }
        }
        return;
    }
    context->GetSymbolTable()->BeginScopeGeneric(symbol->GetScope(), context);
    node.FunctionBody()->Accept(*this);
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

void StatementBinder::Visit(otava::ast::MemberInitializerListNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* initializer = node.Items()[i];
        initializer->Accept(*this);
    }
    std::sort(memberInitializers.begin(), memberInitializers.end(), MemberInitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
}

void StatementBinder::Visit(otava::ast::MemberInitializerNode& node)
{
    int index = -1;
    resolveClass = true;
    node.Left()->Accept(*this);
    resolveClass = false;
    if (classTypeSymbol)
    {
        BoundExpressionNode* thisPtr = context->GetThisPtr(node.GetSourcePos());
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            classTypeSymbol->AddPointer(), thisPtr->GetType(), context);
        if (conversion)
        {
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, node.GetSourcePos())));
        }
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
            BoundParameterNode* thisPtr = new BoundParameterNode(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(), node.GetSourcePos());
            boundVariableNode->SetThisPtr(thisPtr);
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(new BoundDefaultInitNode(boundVariableNode, node.GetSourcePos()), node.GetSourcePos())));
            index = memberVariableSymbol->Index();
        }
    }
    resolveInitializerArguments = true;
    node.Right()->Accept(*this);
    resolveInitializerArguments = false;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", initializerArgs, node.GetSourcePos(), context);
    memberInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
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
            BoundExpressionNode* arg = BindExpression(item, context, this);
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context, this);
    if (!condition->GetType()->IsBoolType())
    {
        FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), context); 
        if (!conversionFunction)
        {
            ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
        }
        condition = new BoundConversionNode(condition, conversionFunction, condition->GetSourcePos());
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context, this);
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
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context, this);
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
    BoundExpressionNode* condition = BindExpression(node.Condition(), context, this);
    if (!condition->GetType()->IsBoolType())
    {
        FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), context);
        if (!conversionFunction)
        {
            ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
        }
        condition = new BoundConversionNode(condition, conversionFunction, condition->GetSourcePos());
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
    BoundExpressionNode* condition = BindExpression(node.Expression(), context, this);
    if (!condition->GetType()->IsBoolType())
    {
        FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), context);
        if (!conversionFunction)
        {
            ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
        }
        condition = new BoundConversionNode(condition, conversionFunction, condition->GetSourcePos());
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
        BoundExpressionNode* condition = BindExpression(node.Condition(), context, this);
        if (!condition->GetType()->IsBoolType())
        {
            FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), context);
            if (!conversionFunction)
            {
                ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
            }
            condition = new BoundConversionNode(condition, conversionFunction, condition->GetSourcePos());
        }
        boundForStatement->SetCondition(condition);
    }
    if (node.LoopExpr())
    {
        BoundExpressionNode* loopExpr = BindExpression(node.LoopExpr(), context, this);
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
        BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context, this);
        TypeSymbol* returnType = functionDefinitionSymbol->ReturnType();
        if (returnValueExpr->GetType() != returnType)
        {
            FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(returnType, returnValueExpr->GetType(), context);
            if (conversion)
            {
                returnValueExpr = new BoundConversionNode(returnValueExpr, conversion, node.GetSourcePos());
            }
            else
            {
                ThrowException("no conversion found", node.GetSourcePos(), context);
            }
        }
        boundReturnStatement->SetExpr(returnValueExpr);
    }
    SetStatement(boundReturnStatement);
}

void StatementBinder::Visit(otava::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode(node.GetSourcePos());
    BoundExpressionNode* expr = BindExpression(node.Expression(), context, this);
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
                initializer = BindExpression(declaration.initializer, context, this);
            }
            VariableSymbol* variable = declaration.variable;
            if (initializer && initializer->GetType())
            {
                variable->SetInitializerType(initializer->GetType());
            }
            BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
            std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
            arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, node.GetSourcePos())));
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
            BoundConstructionStatementNode* boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
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
