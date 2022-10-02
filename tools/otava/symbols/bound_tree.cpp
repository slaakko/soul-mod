// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree;

import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.function.symbol;
import otava.symbols.enums;
import otava.symbols.classes;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.operation.repository;

namespace otava::symbols {

BoundNode::BoundNode(BoundNodeKind kind_) : kind(kind_)
{
}

BoundNode::~BoundNode()
{
}

BoundCompileUnitNode::BoundCompileUnitNode() : BoundNode(BoundNodeKind::boundCompileUnitNode), operationRepository(new OperationRepository())
{
}

void BoundCompileUnitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCompileUnitNode::AddBoundNode(BoundNode* node)
{
    boundNodes.push_back(std::unique_ptr<BoundNode>(node));
}

BoundFunctionNode::BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_) : 
    BoundNode(BoundNodeKind::boundFunctionNode), 
    functionDefinitionSymbol(functionDefinitionSymbol_), 
    body()
{
}

void BoundFunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionNode::SetBody(BoundCompoundStatementNode* body_)
{
    body.reset(body_);
}

BoundStatementNode::BoundStatementNode(BoundNodeKind kind_) : BoundNode(kind_)
{
}

BoundCompoundStatementNode::BoundCompoundStatementNode() : BoundStatementNode(BoundNodeKind::boundCompoundStatementNode)
{
}

void BoundCompoundStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCompoundStatementNode::AddStatement(BoundStatementNode* statement)
{
    statements.push_back(std::unique_ptr<BoundStatementNode>(statement));
}

BoundIfStatementNode::BoundIfStatementNode() : BoundStatementNode(BoundNodeKind::boundIfStatementNode)
{
}

void BoundIfStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundIfStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundIfStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundIfStatementNode::SetThenStatement(BoundStatementNode* thenStatement_)
{
    thenStatement.reset(thenStatement_);
}

void BoundIfStatementNode::SetElseStatement(BoundStatementNode* elseStatement_)
{
    elseStatement.reset(elseStatement_);
}

BoundSwitchStatementNode::BoundSwitchStatementNode() : BoundStatementNode(BoundNodeKind::boundSwitchStatementNode)
{
}

void BoundSwitchStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundSwitchStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundSwitchStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundSwitchStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundCaseStatementNode::BoundCaseStatementNode() : BoundStatementNode(BoundNodeKind::boundCaseStatementNode)
{
}

void BoundCaseStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCaseStatementNode::SetCaseExpr(BoundExpressionNode* caseExpr_)
{
    caseExpr.reset(caseExpr_);
}

void BoundCaseStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundDefaultStatementNode::BoundDefaultStatementNode() : BoundStatementNode(BoundNodeKind::boundDefaultStatementNode)
{
}

void BoundDefaultStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDefaultStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundWhileStatementNode::BoundWhileStatementNode() : BoundStatementNode(BoundNodeKind::boundWhileStatementNode)
{
}

void BoundWhileStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundWhileStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundWhileStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundDoStatementNode::BoundDoStatementNode() : BoundStatementNode(BoundNodeKind::boundDoStatementNode)
{
}

void BoundDoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDoStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
}

void BoundDoStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundForStatementNode::BoundForStatementNode() : BoundStatementNode(BoundNodeKind::boundForStatementNode)
{
}

void BoundForStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundForStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundForStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundForStatementNode::SetLoopExpr(BoundExpressionNode* loopExpr_)
{
    loopExpr.reset(loopExpr_);
}

void BoundForStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundBreakStatementNode::BoundBreakStatementNode() : BoundStatementNode(BoundNodeKind::boundBreakStatementNode)
{
}

void BoundBreakStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundContinueStatementNode::BoundContinueStatementNode() : BoundStatementNode(BoundNodeKind::boundContinueStatementNode)
{
}

void BoundContinueStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundReturnStatementNode::BoundReturnStatementNode() : BoundStatementNode(BoundNodeKind::boundReturnStatementNode)
{
}

void BoundReturnStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundReturnStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
}

BoundGotoStatementNode::BoundGotoStatementNode() : BoundStatementNode(BoundNodeKind::boundGotoStatementNode)
{
}

void BoundGotoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundConstructionStatementNode::BoundConstructionStatementNode(VariableSymbol* variable_, BoundExpressionNode* initializer_) : 
    BoundStatementNode(BoundNodeKind::boundConstructionStatementNode), variable(variable_), initializer(initializer_)
{
}

void BoundConstructionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionStatementNode::BoundExpressionStatementNode() : BoundStatementNode(BoundNodeKind::boundExpressionStatementNode)
{
}

void BoundExpressionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundExpressionStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
}

BoundExpressionNode::BoundExpressionNode(BoundNodeKind kind_, TypeSymbol* type_) : BoundNode(kind_), type(type_)
{
}

void BoundExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("LOAD not implemented", sourcePos, context);
}

void BoundExpressionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("STORE not implemented", sourcePos, context);
}

Scope* BoundExpressionNode::GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const
{
    if (type)
    {
        if (op->IsDotNode())
        {
            TypeSymbol* baseType = ResolveFwdDeclaredType(type->DirectType()->GetBaseType(), sourcePos, context);
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && type->IsPointerType())
        {
            TypeSymbol* baseType = ResolveFwdDeclaredType(type->DirectType()->RemovePointer()->GetBaseType(), sourcePos, context);
            return baseType->GetScope();
        }
    }
    return nullptr;
}

BoundLiteralNode::BoundLiteralNode(Value* value_) : BoundExpressionNode(BoundNodeKind::boundLiteralNode, value_->GetType()), value(value_)
{
}

void BoundLiteralNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundLiteralNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{

}

BoundVariableNode::BoundVariableNode(VariableSymbol* variable_) : BoundExpressionNode(BoundNodeKind::boundVariableNode, variable_->GetType()), variable(variable_)
{
}

void BoundVariableNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundParameterNode::BoundParameterNode(ParameterSymbol* parameter_) : BoundExpressionNode(BoundNodeKind::boundParameterNode, parameter_->GetType()), parameter(parameter_)
{
}

void BoundParameterNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundEnumConstant::BoundEnumConstant(EnumConstantSymbol* enumConstant_) : 
    BoundExpressionNode(BoundNodeKind::boundEnumConstantNode, enumConstant_->GetType()), enumConstant(enumConstant_)
{
}

void BoundEnumConstant::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundFunctionGroupNode::BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionGroupNode, nullptr), functionGroupSymbol(functionGroupSymbol_)
{
}

void BoundFunctionGroupNode::Accept(BoundTreeVisitor& visitor) 
{
    visitor.Visit(*this);
}

BoundTypeNode::BoundTypeNode(TypeSymbol* type_) : BoundExpressionNode(BoundNodeKind::boundTypeNode, type_)
{
}

void BoundTypeNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundMemberExprNode::BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_) : 
    BoundExpressionNode(BoundNodeKind::boundMemberExprNode, nullptr), subject(subject_), member(member_)
{
}

void BoundMemberExprNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundFunctionCallNode::BoundFunctionCallNode(FunctionSymbol* functionSymbol_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionCallNode, functionSymbol_->ReturnType()), functionSymbol(functionSymbol_)
{
}

void BoundFunctionCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionCallNode::AddArgument(BoundExpressionNode* arg)
{
    args.push_back(std::unique_ptr<BoundExpressionNode>(arg));
}

BoundErrorNode::BoundErrorNode() : BoundExpressionNode(BoundNodeKind::boundErrorNode, nullptr)
{
}

void BoundErrorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

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
