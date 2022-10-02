// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.statement.binder;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.statement;
import soul.cpp20.ast.function;
import soul.cpp20.ast.declaration;
import soul.cpp20.ast.type;
import soul.cpp20.symbols.bound.tree;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declarator;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.expression.binder;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.variable.symbol;

namespace soul::cpp20::symbols {

class StatementBinder : public soul::cpp20::ast::DefaultVisitor
{
public:
    StatementBinder(Context* context_);
    BoundStatementNode* GetBoundStatement() const { return boundStatement; }
    void Visit(soul::cpp20::ast::FunctionDefinitionNode& node) override;
    void Visit(soul::cpp20::ast::FunctionBodyNode& node) override;
    void Visit(soul::cpp20::ast::CompoundStatementNode& node) override;
    void Visit(soul::cpp20::ast::IfStatementNode& node) override;
    void Visit(soul::cpp20::ast::SwitchStatementNode& node) override;
    void Visit(soul::cpp20::ast::CaseStatementNode& node) override;
    void Visit(soul::cpp20::ast::DefaultStatementNode& node) override;
    void Visit(soul::cpp20::ast::WhileStatementNode& node) override;
    void Visit(soul::cpp20::ast::DoStatementNode& node) override;
    void Visit(soul::cpp20::ast::RangeForStatementNode& node) override;
    void Visit(soul::cpp20::ast::ForStatementNode& node) override;
    void Visit(soul::cpp20::ast::BreakStatementNode& node) override;
    void Visit(soul::cpp20::ast::ContinueStatementNode& node) override;
    void Visit(soul::cpp20::ast::ReturnStatementNode& node) override;
    void Visit(soul::cpp20::ast::ExpressionStatementNode& node) override;
    void Visit(soul::cpp20::ast::DeclarationStatementNode& node) override;
private:
    Context* context;
    BoundStatementNode* boundStatement;
};

StatementBinder::StatementBinder(Context* context_) : context(context_), boundStatement()
{
}

void StatementBinder::Visit(soul::cpp20::ast::FunctionDefinitionNode& node)
{
    node.FunctionBody()->Accept(*this);
}

void StatementBinder::Visit(soul::cpp20::ast::FunctionBodyNode& node)
{
    node.Child()->Accept(*this);
}

void StatementBinder::Visit(soul::cpp20::ast::CompoundStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->BeginCompoundStatement();
    context->GetSymbolTable()->BeginScope(block->GetScope());
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* statementNode = node.Nodes()[i];
        BoundStatementNode* boundStatement = BindStatement(statementNode, context);
        context->GetCurrentCompoundStatement()->AddStatement(boundStatement);
    }
    context->GetSymbolTable()->EndScope();
    context->EndCompoundStatement();
}

void StatementBinder::Visit(soul::cpp20::ast::IfStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundIfStatementNode* boundIfStatement = new BoundIfStatementNode();
    boundStatement = boundIfStatement;
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), context);
        if (boundInitStatement)
        {
            boundIfStatement->SetInitStatement(boundInitStatement);
        }
    }
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    boundIfStatement->SetCondition(condition);
    BoundStatementNode* boundThenStatement = BindStatement(node.ThenStatement(), context);
    if (boundThenStatement)
    {
        boundIfStatement->SetThenStatement(boundThenStatement);
    }
    if (node.ElseStatement())
    {
        BoundStatementNode* boundElseStatement = BindStatement(node.ElseStatement(), context);
        if (boundElseStatement)
        {
            boundIfStatement->SetElseStatement(boundElseStatement);
        }
    }
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(soul::cpp20::ast::SwitchStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundSwitchStatementNode* boundSwitchStatement = new BoundSwitchStatementNode();
    boundStatement = boundSwitchStatement;
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), context);
        if (boundInitStatement)
        {
            boundSwitchStatement->SetInitStatement(boundInitStatement);
        }
    }
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    boundSwitchStatement->SetCondition(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundSwitchStatement->SetStatement(boundStmt);
    }
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(soul::cpp20::ast::CaseStatementNode& node)
{
    BoundCaseStatementNode* boundCaseStatement = new BoundCaseStatementNode();
    boundStatement = boundCaseStatement;
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context);
    boundCaseStatement->SetCaseExpr(caseExpr);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundCaseStatement->SetStatement(boundStmt);
    }
}

void StatementBinder::Visit(soul::cpp20::ast::DefaultStatementNode& node)
{
    BoundDefaultStatementNode* boundDefaultStatement = new BoundDefaultStatementNode();
    boundStatement = boundDefaultStatement;
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundDefaultStatement->SetStatement(boundStmt);
    }
}

void StatementBinder::Visit(soul::cpp20::ast::WhileStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundWhileStatementNode* boundWhileStatement = new BoundWhileStatementNode();
    boundStatement = boundWhileStatement;
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    boundWhileStatement->SetCondition(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundWhileStatement->SetStatement(boundStmt);
    }
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(soul::cpp20::ast::DoStatementNode& node)
{
    BoundDoStatementNode* boundDoStatement = new BoundDoStatementNode();
    boundStatement = boundDoStatement;
    BoundExpressionNode* expr = BindExpression(node.Expression(), context);
    boundDoStatement->SetExpr(expr);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundDoStatement->SetStatement(boundStmt);
    }
}

void StatementBinder::Visit(soul::cpp20::ast::RangeForStatementNode& node)
{
    //auto initializer = node.Initializer()->Clone();
/*  int x = 0;
    soul::ast::SourcePos sourcePos = node.GetSourcePos();
    soul::cpp20::ast::SimpleDeclarationNode* declaration = new soul::cpp20::ast::SimpleDeclarationNode(sourcePos);
    soul::cpp20::ast::DeclarationStatementNode* it = new soul::cpp20::ast::DeclarationStatementNode(sourcePos, declaration);
    declaration->Add(new soul::cpp20::ast::PlaceholderTypeSpecifierNode(sourcePos, nullptr, nullptr, nullptr, nullptr, nullptr));
    soul::cpp20::ast::InitDeclaratorListNode* initDeclList = new soul::cpp20::ast::InitDeclaratorListNode(sourcePos);
    soul::cpp20::ast::IdentifierNode* begin = new soul::cpp20::ast::IdentifierNode(sourcePos, U"begin");
    soul::cpp20::ast::InvokeExprNode* invoke = new soul::cpp20::ast::InvokeExprNode(sourcePos, begin);
    invoke->AddNode(node.Initializer()->Clone());
    soul::cpp20::ast::AssignInitNode* assignInit = new soul::cpp20::ast::AssignInitNode(sourcePos, invoke);
    soul::cpp20::ast::InitializerNode* initializer = new soul::cpp20::ast::InitializerNode(sourcePos, assignInit);
    soul::cpp20::ast::InitDeclaratorNode* initDeclarator = new soul::cpp20::ast::InitDeclaratorNode(sourcePos, U"it", initializer);
    initDeclList->Add(initDeclarator);
    it.SetInitDeclaratorList(initDeclList);
*/
}

void StatementBinder::Visit(soul::cpp20::ast::ForStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundForStatementNode* boundForStatement = new BoundForStatementNode();
    boundStatement = boundForStatement;
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), context);
        if (boundInitStatement)
        {
            boundForStatement->SetInitStatement(boundInitStatement);
        }
    }
    if (node.Condition())
    {
        BoundExpressionNode* condition = BindExpression(node.Condition(), context);
        boundForStatement->SetCondition(condition);
    }
    if (node.LoopExpr())
    {
        BoundExpressionNode* loopExpr = BindExpression(node.LoopExpr(), context);
        boundForStatement->SetLoopExpr(loopExpr);
    }
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), context);
    if (boundStmt)
    {
        boundForStatement->SetStatement(boundStmt);
    }
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(soul::cpp20::ast::BreakStatementNode& node)
{
    BoundBreakStatementNode* boundBreakStatement = new BoundBreakStatementNode();
    boundStatement = boundBreakStatement;
}

void StatementBinder::Visit(soul::cpp20::ast::ContinueStatementNode& node)
{
    BoundContinueStatementNode* boundContinueStatement = new BoundContinueStatementNode();
    boundStatement = boundContinueStatement;
}

void StatementBinder::Visit(soul::cpp20::ast::ReturnStatementNode& node)
{
    BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode();
    boundStatement = boundReturnStatement;
    if (node.ReturnValue())
    {
        BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context);
        boundReturnStatement->SetExpr(returnValueExpr);
    }
}

void StatementBinder::Visit(soul::cpp20::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode();
    boundStatement = boundExpressionStatement;
    BoundExpressionNode* expr = BindExpression(node.Expression(), context);
    boundExpressionStatement->SetExpr(expr);
}

void StatementBinder::Visit(soul::cpp20::ast::DeclarationStatementNode& node)
{
    BoundCompoundStatementNode* boundCompoundStatement = new BoundCompoundStatementNode();
    boundStatement = boundCompoundStatement;
    std::unique_ptr<DeclarationList> declarationList = context->ReleaseDeclarationList(node.Declaration());
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
            if (initializer)
            {
                variable->SetInitializerType(initializer->GetType());
            }
            BoundConstructionStatementNode * boundConstructionStatement = new BoundConstructionStatementNode(variable, initializer);
            boundCompoundStatement->AddStatement(boundConstructionStatement);
        }
    }
    else
    {
        int x = 0;
    }
}

BoundStatementNode* BindStatement(soul::cpp20::ast::Node* statementNode, Context* context)
{
    StatementBinder binder(context);
    statementNode->Accept(binder);
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    return boundStatement;
}

void BindFunction(soul::cpp20::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    if (functionDefinitionSymbol && functionDefinitionSymbol->Parent()->IsTemplateDeclarationSymbol())
    {
        int x = 0;
        return;
    }
    StatementBinder binder(context);
    functionDefinitionNode->Accept(binder);
}

} // namespace soul::cpp20::symbols
