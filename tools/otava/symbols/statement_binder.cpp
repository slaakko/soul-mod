// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.statement.binder;

import otava.ast.visitor;
import otava.ast.statement;
import otava.ast.function;
import otava.ast.declaration;
import otava.ast.type;
import otava.symbols.bound.tree;
import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.exception;
import otava.symbols.expression.binder;
import otava.symbols.function.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;
import otava.symbols.variable.symbol;

namespace otava::symbols {

class StatementBinder : public otava::ast::DefaultVisitor
{
public:
    StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    BoundStatementNode* GetBoundStatement() const { return boundStatement; }
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::FunctionBodyNode& node) override;
    void Visit(otava::ast::CompoundStatementNode& node) override;
    void Visit(otava::ast::IfStatementNode& node) override;
    void Visit(otava::ast::SwitchStatementNode& node) override;
    void Visit(otava::ast::CaseStatementNode& node) override;
    void Visit(otava::ast::DefaultStatementNode& node) override;
    void Visit(otava::ast::WhileStatementNode& node) override;
    void Visit(otava::ast::DoStatementNode& node) override;
    void Visit(otava::ast::RangeForStatementNode& node) override;
    void Visit(otava::ast::ForStatementNode& node) override;
    void Visit(otava::ast::BreakStatementNode& node) override;
    void Visit(otava::ast::ContinueStatementNode& node) override;
    void Visit(otava::ast::ReturnStatementNode& node) override;
    void Visit(otava::ast::ExpressionStatementNode& node) override;
    void Visit(otava::ast::DeclarationStatementNode& node) override;
private:
    Context* context;
    BoundStatementNode* boundStatement;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
};

StatementBinder::StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) : 
    context(context_), 
    functionDefinitionSymbol(functionDefinitionSymbol_), 
    boundStatement()
{
}

void StatementBinder::Visit(otava::ast::FunctionDefinitionNode& node)
{
    node.FunctionBody()->Accept(*this);
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
    context->GetSymbolTable()->BeginScope(block->GetScope());
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* statementNode = node.Nodes()[i];
        BoundStatementNode* boundStatement = BindStatement(statementNode, functionDefinitionSymbol, context);
        currentCompoundStatement->AddStatement(boundStatement);
    }
    context->GetSymbolTable()->EndScope();
    boundStatement = currentCompoundStatement;
}

void StatementBinder::Visit(otava::ast::IfStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
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
        condition = context->GetSymbolTable()->MakeBooleanConversion(condition, context);
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
    boundStatement = boundIfStatement;
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(otava::ast::SwitchStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundSwitchStatementNode* boundSwitchStatement = new BoundSwitchStatementNode(node.GetSourcePos());
    boundStatement = boundSwitchStatement;
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
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(otava::ast::CaseStatementNode& node)
{
    BoundCaseStatementNode* boundCaseStatement = new BoundCaseStatementNode(node.GetSourcePos());
    boundStatement = boundCaseStatement;
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context);
    boundCaseStatement->SetCaseExpr(caseExpr);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundCaseStatement->SetStatement(boundStmt);
    }
}

void StatementBinder::Visit(otava::ast::DefaultStatementNode& node)
{
    BoundDefaultStatementNode* boundDefaultStatement = new BoundDefaultStatementNode(node.GetSourcePos());
    boundStatement = boundDefaultStatement;
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundDefaultStatement->SetStatement(boundStmt);
    }
}

void StatementBinder::Visit(otava::ast::WhileStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundWhileStatementNode* boundWhileStatement = new BoundWhileStatementNode(node.GetSourcePos());
    boundStatement = boundWhileStatement;
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = context->GetSymbolTable()->MakeBooleanConversion(condition, context);
    }
    boundWhileStatement->SetCondition(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundWhileStatement->SetStatement(boundStmt);
    }
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(otava::ast::DoStatementNode& node)
{
    BoundDoStatementNode* boundDoStatement = new BoundDoStatementNode(node.GetSourcePos());
    boundStatement = boundDoStatement;
    BoundExpressionNode* condition = BindExpression(node.Expression(), context);
    if (!condition->GetType()->IsBoolType())
    {
        condition = context->GetSymbolTable()->MakeBooleanConversion(condition, context);
    }
    boundDoStatement->SetExpr(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundDoStatement->SetStatement(boundStmt);
    }
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
    context->GetSymbolTable()->BeginScope(block->GetScope());
    BoundForStatementNode* boundForStatement = new BoundForStatementNode(node.GetSourcePos());
    boundStatement = boundForStatement;
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
            condition = context->GetSymbolTable()->MakeBooleanConversion(condition, context);
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
    context->GetSymbolTable()->EndScope();
}

void StatementBinder::Visit(otava::ast::BreakStatementNode& node)
{
    BoundBreakStatementNode* boundBreakStatement = new BoundBreakStatementNode(node.GetSourcePos());
    boundStatement = boundBreakStatement;
}

void StatementBinder::Visit(otava::ast::ContinueStatementNode& node)
{
    BoundContinueStatementNode* boundContinueStatement = new BoundContinueStatementNode(node.GetSourcePos());
    boundStatement = boundContinueStatement;
}

void StatementBinder::Visit(otava::ast::ReturnStatementNode& node)
{
    BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(node.GetSourcePos());
    boundStatement = boundReturnStatement;
    if (node.ReturnValue())
    {
        BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context);
        boundReturnStatement->SetExpr(returnValueExpr);
    }
}

void StatementBinder::Visit(otava::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode(node.GetSourcePos());
    boundStatement = boundExpressionStatement;
    BoundExpressionNode* expr = BindExpression(node.Expression(), context);
    boundExpressionStatement->SetExpr(expr);
}

void StatementBinder::Visit(otava::ast::DeclarationStatementNode& node)
{
    BoundCompoundStatementNode* boundCompoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
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
            BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
            std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
            arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, node.GetSourcePos())));
            if (initializer)
            {
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(initializer));
            }
            std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", arguments, 
                node.GetSourcePos(), context);
            BoundConstructionStatementNode * boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
            boundCompoundStatement->AddStatement(boundConstructionStatement);
            functionDefinitionSymbol->AddLocalVariable(variable, node.GetSourcePos(), context);
        }
    }
    else
    {
        int x = 0;
    }
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
    StatementBinder binder(context, functionDefinitionSymbol);
    functionDefinitionNode->Accept(binder);
}

} // namespace otava::symbols
