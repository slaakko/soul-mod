export module minilang.visitor;

export namespace minilang::tree {

class UnaryOpExprNode;
class InvokeNode;
class BinaryOpExprNode;
class IntNode;
class BoolNode;
class VoidNode;
class BooleanLiteralNode;
class IntegerLiteralNode;
class IdentifierNode;
class ParenthesizedExpressionNode;
class IfStatementNode;
class WhileStatementNode;
class ReturnStatementNode;
class ConstructionStatementNode;
class AssignmentStatementNode;
class CompoundStatementNode;
class ParameterNode;
class FunctionNode;
class SourceFileNode;

} // namespace minilang::tree

export namespace minilang::visitor {

class Visitor
{
public:
	virtual void Visit(minilang::tree::UnaryOpExprNode& node) {}
	virtual void Visit(minilang::tree::InvokeNode& node) {}
	virtual void Visit(minilang::tree::BinaryOpExprNode& node) {}
	virtual void Visit(minilang::tree::IntNode& node) {}
	virtual void Visit(minilang::tree::BoolNode& node) {}
	virtual void Visit(minilang::tree::VoidNode& node) {}
	virtual void Visit(minilang::tree::BooleanLiteralNode& node) {}
	virtual void Visit(minilang::tree::IntegerLiteralNode& node) {}
	virtual void Visit(minilang::tree::IdentifierNode& node) {}
	virtual void Visit(minilang::tree::ParenthesizedExpressionNode& node) {}
	virtual void Visit(minilang::tree::IfStatementNode& node) {}
	virtual void Visit(minilang::tree::WhileStatementNode& node) {}
	virtual void Visit(minilang::tree::ReturnStatementNode& node) {}
	virtual void Visit(minilang::tree::ConstructionStatementNode& node) {}
	virtual void Visit(minilang::tree::AssignmentStatementNode& node) {}
	virtual void Visit(minilang::tree::CompoundStatementNode& node) {}
	virtual void Visit(minilang::tree::ParameterNode& node) {}
	virtual void Visit(minilang::tree::FunctionNode& node) {}
	virtual void Visit(minilang::tree::SourceFileNode& node) {}
};

} // namespace minilang::visitor
