// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree.visitor;

import otava.symbols.bound.node;
import otava.symbols.bound.tree;

namespace otava::symbols {

BoundTreeVisitor::~BoundTreeVisitor()
{
}

void DefaultBoundTreeVisitor::Visit(BoundCompileUnitNode& node)
{
    for (const auto& node : node.BoundNodes())
    {
        node->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundFunctionNode& node)
{
    node.Body()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundCompoundStatementNode& node)
{
    for (const auto& stmt : node.Statements())
    {
        stmt->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundIfStatementNode& node)
{
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.GetCondition()->Accept(*this);
    node.ThenStatement()->Accept(*this);
    if (node.ElseStatement())
    {
        node.ElseStatement()->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundSwitchStatementNode& node)
{
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.GetCondition()->Accept(*this);
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundCaseStatementNode& node)
{
    node.CaseExpr()->Accept(*this);
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundDefaultStatementNode& node)
{
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundWhileStatementNode& node)
{
    node.GetCondition()->Accept(*this);
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundDoStatementNode& node)
{
    node.GetExpr()->Accept(*this);
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundForStatementNode& node)
{
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    if (node.GetCondition())
    {
        node.GetCondition()->Accept(*this);
    }
    if (node.GetLoopExpr())
    {
        node.GetLoopExpr()->Accept(*this);
    }
    node.Statement()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundSequenceStatementNode& node)
{
    node.First()->Accept(*this);
    node.Second()->Accept(*this);
}

void DefaultBoundTreeVisitor::Visit(BoundReturnStatementNode& node)
{
    if (node.GetExpr())
    {
        node.GetExpr()->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundConstructionStatementNode& node)
{
    if (node.Initializer())
    {
        node.Initializer()->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundExpressionStatementNode& node)
{
    if (node.GetExpr())
    {
        node.GetExpr()->Accept(*this);
    }
}

void DefaultBoundTreeVisitor::Visit(BoundMemberExprNode& node)
{
    node.Subject()->Accept(*this);
    node.Member()->Accept(*this);
}

} // namespace otava::symbols
