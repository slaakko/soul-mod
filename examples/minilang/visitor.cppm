export module minilang.visitor;

export namespace minilang::ast {

class IntNode;
class BoolNode;
class VoidNode;
class BooleanLiteralNode;
class IntegerLiteralNode;
class IdentifierNode;
class ParenthesizedExpressionNode;
class InvokeNode;
class UnaryExprNode;
class BinaryExprNode;
class IfStatementNode;
class WhileStatementNode;
class ReturnStatementNode;
class CompoundStatementNode;
class ConstructionStatementNode;
class AssignmentStatementNode;
class ParameterNode;
class FunctionNode;
class SourceFileNode;

} // namespace minilang::ast

export namespace minilang::visitor {

class Visitor
{
public:
	virtual void Visit(minilang::ast::IntNode& node) {}
	virtual void Visit(minilang::ast::BoolNode& node) {}
	virtual void Visit(minilang::ast::VoidNode& node) {}
	virtual void Visit(minilang::ast::BooleanLiteralNode& node) {}
	virtual void Visit(minilang::ast::IntegerLiteralNode& node) {}
	virtual void Visit(minilang::ast::IdentifierNode& node) {}
	virtual void Visit(minilang::ast::ParenthesizedExpressionNode& node) {}
	virtual void Visit(minilang::ast::InvokeNode& node) {}
	virtual void Visit(minilang::ast::UnaryExprNode& node) {}
	virtual void Visit(minilang::ast::BinaryExprNode& node) {}
	virtual void Visit(minilang::ast::IfStatementNode& node) {}
	virtual void Visit(minilang::ast::WhileStatementNode& node) {}
	virtual void Visit(minilang::ast::ReturnStatementNode& node) {}
	virtual void Visit(minilang::ast::CompoundStatementNode& node) {}
	virtual void Visit(minilang::ast::ConstructionStatementNode& node) {}
	virtual void Visit(minilang::ast::AssignmentStatementNode& node) {}
	virtual void Visit(minilang::ast::ParameterNode& node) {}
	virtual void Visit(minilang::ast::FunctionNode& node) {}
	virtual void Visit(minilang::ast::SourceFileNode& node) {}
};

} // namespace minilang::visitor
