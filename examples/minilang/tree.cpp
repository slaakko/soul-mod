module minilang.tree;

import minilang.visitor;

namespace minilang::tree {

Node::~Node()
{
}

void Node::AddArgument(Node* arg)
{
	throw std::runtime_error("cannot add argument to this kind of node");
}

UnaryNode::UnaryNode(Node* child_) : child(child_)
{
}

UnaryOpExprNode::UnaryOpExprNode(Operator op_, Node* child_) : UnaryNode(child_), op(op_)
{
}

void UnaryOpExprNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

InvokeNode::InvokeNode(Node* child_) : UnaryNode(child_)
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

BinaryNode::BinaryNode(Node* left_, Node* right_) : left(left_), right(right_)
{
}

BinaryOpExprNode::BinaryOpExprNode(Operator op_, Node* left_, Node* right_) : BinaryNode(left_, right_), op(op_)
{
}

void BinaryOpExprNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

void IntNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

void BoolNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

void VoidNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

BooleanLiteralNode::BooleanLiteralNode(bool value_) : value(value_)
{
}

void BooleanLiteralNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IntegerLiteralNode::IntegerLiteralNode(int64_t value_) : value(value_)
{
}

void IntegerLiteralNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IdentifierNode::IdentifierNode(const std::u32string& str_) : str(str_)
{
}

void IdentifierNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ParenthesizedExpressionNode::ParenthesizedExpressionNode(Node* child_) : UnaryNode(child_)
{
}

void ParenthesizedExpressionNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

IfStatementNode::IfStatementNode(Node* condition_, Node* thenS_, Node* elseS_) : condition(condition_), thenS(thenS_), elseS(elseS_)
{
}

void IfStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

WhileStatementNode::WhileStatementNode(Node* condition_, Node* statement_) : condition(condition_), statement(statement_)
{
}

void WhileStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ReturnStatementNode::ReturnStatementNode(Node* returnValue_) : returnValue(returnValue_)
{
}

void ReturnStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ConstructionStatementNode::ConstructionStatementNode(Node* type_, IdentifierNode* variableName_, Node* value_) : type(type_), variableName(variableName_), value(value_)
{
}

void ConstructionStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* variableName_, Node* value_) : variableName(variableName_), value(value_)
{
}

void AssignmentStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

void CompoundStatementNode::AddStatement(Node* statement)
{
	statements.push_back(std::unique_ptr<Node>(statement));
}

void CompoundStatementNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

ParameterNode::ParameterNode(Node* paramType_, IdentifierNode* paramName_) : paramType(paramType_), paramName(paramName_)
{
}

void ParameterNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

FunctionNode::FunctionNode(Node* returnType_, IdentifierNode* functionName_) : returnType(returnType_), functionName(functionName_)
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

void SourceFileNode::AddFunction(FunctionNode* function)
{
	functions.push_back(std::unique_ptr<FunctionNode>(function));
}

void SourceFileNode::Accept(minilang::visitor::Visitor& visitor)
{
	visitor.Visit(*this);
}

} // namespace minilang::tree

