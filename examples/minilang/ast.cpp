module minilang.ast;

import minilang.visitor;

namespace minilang::ast {

Node::Node(NodeKind kind_) : kind(kind_)
{
}

Node::~Node()
{
}

void Node::AddArgument(Node* arg)
{
	throw std::runtime_error("cannot add argument to this kind of node");
}

IntNode::IntNode() : Node(NodeKind::intNode)
{
}

void IntNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

BoolNode::BoolNode() : Node(NodeKind::boolNode)
{
}

void BoolNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

VoidNode::VoidNode() : Node(NodeKind::voidNode)
{
}

void VoidNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

BooleanLiteralNode::BooleanLiteralNode(bool value_) : Node(NodeKind::booleanLiteralNode), value(value_)
{
}

void BooleanLiteralNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IntegerLiteralNode::IntegerLiteralNode(std::int64_t value_) : Node(NodeKind::integerLiteralNode), value(value_)
{
}

void IntegerLiteralNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IdentifierNode::IdentifierNode(const std::u32string& str_) : Node(NodeKind::identifierNode), str(str_)
{
}

void IdentifierNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

UnaryNode::UnaryNode(NodeKind kind_, Node* child_) : Node(kind_), child(child_)
{
}

ParenthesizedExpressionNode::ParenthesizedExpressionNode(Node* child_) : UnaryNode(NodeKind::parenthesizedExprNode, child_)
{
}

void ParenthesizedExpressionNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

InvokeNode::InvokeNode(Node* child_) : UnaryNode(NodeKind::invokeNode, child_)
{
}

void InvokeNode::AddArgument(Node* arg)
{
	args.push_back(std::unique_ptr<Node>(arg));
}

void InvokeNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

UnaryExprNode::UnaryExprNode(Operator op_, Node* child_) : UnaryNode(NodeKind::unaryExprNode, child_), op(op_)
{
}

void UnaryExprNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

BinaryNode::BinaryNode(NodeKind kind_, Node* left_, Node* right_) : Node(kind_), left(left_), right(right_)
{
}

BinaryExprNode::BinaryExprNode(Operator op_, Node* left_, Node* right_) : BinaryNode(NodeKind::binaryExprNode, left_, right_), op(op_)
{
}

void BinaryExprNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IfStatementNode::IfStatementNode(Node* condition_, Node* thenS_, Node* elseS_) : Node(NodeKind::ifStatementNode), condition(condition_), thenS(thenS_), elseS(elseS_)
{
}

void IfStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

WhileStatementNode::WhileStatementNode(Node* condition_, Node* statement_) : Node(NodeKind::whileStatementNode), condition(condition_), statement(statement_)
{
}

void WhileStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ReturnStatementNode::ReturnStatementNode(Node* returnValue_) : Node(NodeKind::returnStatementNode), returnValue(returnValue_)
{
}

void ReturnStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

CompoundStatementNode::CompoundStatementNode() : Node(NodeKind::compoundStatementNode)
{
}

void CompoundStatementNode::AddStatement(Node* statement)
{
	statements.push_back(std::unique_ptr<Node>(statement));
}

void CompoundStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ConstructionStatementNode::ConstructionStatementNode(Node* type_, IdentifierNode* variableName_, Node* value_) :
	Node(NodeKind::constructionStatementNode), type(type_), variableName(variableName_), value(value_)
{
}

void ConstructionStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* variableName_, Node* value_) : Node(NodeKind::assignmentStatementNode), variableName(variableName_), value(value_)
{
}

void AssignmentStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ParameterNode::ParameterNode(Node* paramType_, IdentifierNode* paramName_) : Node(NodeKind::parameterNode), paramType(paramType_), paramName(paramName_)
{
}

void ParameterNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

FunctionNode::FunctionNode(Node* returnType_, IdentifierNode* functionName_) : Node(NodeKind::functionNode), returnType(returnType_), functionName(functionName_)
{
}

void FunctionNode::AddParam(ParameterNode* param)
{
	parameters.push_back(std::unique_ptr<ParameterNode>(param));
}

void FunctionNode::SetBody(CompoundStatementNode* body_)
{
	body.reset(body_);
}

void FunctionNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

SourceFileNode::SourceFileNode() : Node(NodeKind::sourceFileNode)
{
}

void SourceFileNode::AddFunction(FunctionNode* function)
{
	functions.push_back(std::unique_ptr<FunctionNode>(function));
}

void SourceFileNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

} // namespace minilang::ast

