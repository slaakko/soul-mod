export module minilang.ast;

import std;

export namespace minilang::visitor {

class Visitor;

} // namespace minilang::visitor

export namespace minilang::ast {

enum class Operator
{
	equal, notEqual, less, greater, lessOrEqual, greaterOrEqual, add, sub, mul, div, mod, unaryPlus, unaryMinus, not_
};

enum class NodeKind
{
	intNode, boolNode, voidNode, booleanLiteralNode, integerLiteralNode, identifierNode, parenthesizedExprNode, invokeNode, unaryExprNode, binaryExprNode,
	ifStatementNode, whileStatementNode, returnStatementNode, constructionStatementNode, assignmentStatementNode, compoundStatementNode, 
	parameterNode, functionNode, sourceFileNode
};

class Node
{
public:
	Node(NodeKind kind_);
	NodeKind Kind() const { return kind; }
	virtual ~Node();
	bool IsCompoundStatementNode() const { return kind == NodeKind::compoundStatementNode;  }
	virtual void AddArgument(Node* arg);
	virtual void Accept(minilang::visitor::Visitor& visitor) = 0;
private:
	NodeKind kind;
};

class IntNode : public Node
{
public:
	IntNode();
	void Accept(minilang::visitor::Visitor& visitor) override;
};

class BoolNode : public Node
{
public:
	BoolNode();
	void Accept(minilang::visitor::Visitor& visitor) override;
};

class VoidNode : public Node
{
public:
	VoidNode();
	void Accept(minilang::visitor::Visitor& visitor) override;
};

class BooleanLiteralNode : public Node
{
public:
	BooleanLiteralNode(bool value_);
	bool Value() const { return value; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	bool value;
};

class IntegerLiteralNode : public Node
{
public:
	IntegerLiteralNode(std::int64_t value_);
	std::int64_t Value() const { return value; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::int64_t value;
};

class IdentifierNode : public Node
{
public:
	IdentifierNode(const std::u32string& str_);
	const std::u32string& Str() const { return str; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::u32string str;
};

class UnaryNode : public Node
{
public:
	UnaryNode(NodeKind kind_, Node* child_);
	Node* Child() const { return child.get(); }
private:
	std::unique_ptr<Node> child;
};

class ParenthesizedExpressionNode : public UnaryNode
{
public:
	ParenthesizedExpressionNode(Node* child_);
	void Accept(minilang::visitor::Visitor& visitor) override;
};

class InvokeNode : public UnaryNode
{
public:
	InvokeNode(Node* child_);
	const std::vector<std::unique_ptr<Node>>& Args() const { return args; }
	void AddArgument(Node* arg) override;
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::vector<std::unique_ptr<Node>> args;
};

class UnaryExprNode : public UnaryNode
{
public:
	UnaryExprNode(Operator op_, Node* child_);
	Operator Op() const { return op; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	Operator op;
};

class BinaryNode : public Node
{
public:
	BinaryNode(NodeKind kind_, Node* left_, Node* right_);
	Node* Left() const { return left.get(); }
	Node* Right() const { return right.get(); }
private:
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
};

class BinaryExprNode : public BinaryNode
{
public:
	BinaryExprNode(Operator op_, Node* left_, Node* right_);
	Operator Op() const { return op; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	Operator op;
};

class IfStatementNode : public Node
{
public:
	IfStatementNode(Node* condition_, Node* thenS_, Node* elseS_);
	Node* Condition() const { return condition.get(); }
	Node* ThenS() const { return thenS.get(); }
	Node* ElseS() const { return elseS.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> condition;
	std::unique_ptr<Node> thenS;
	std::unique_ptr<Node> elseS;
};

class WhileStatementNode : public Node
{
public:
	WhileStatementNode(Node* condition_, Node* statement_);
	Node* Condition() const { return condition.get(); }
	Node* Statement() const { return statement.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> condition;
	std::unique_ptr<Node> statement;
};

class ReturnStatementNode : public Node
{
public:
	ReturnStatementNode(Node* returnValue_);
	Node* ReturnValue() const { return returnValue.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> returnValue;
};

class CompoundStatementNode : public Node
{
public:
	CompoundStatementNode();
	void AddStatement(Node* statement);
	const std::vector<std::unique_ptr<Node>>& Statements() const { return statements; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::vector<std::unique_ptr<Node>> statements;
};

class ConstructionStatementNode : public Node
{
public:
	ConstructionStatementNode(Node* type_, IdentifierNode* variableName_, Node* value_);
	Node* Type() const { return type.get(); }
	IdentifierNode* VariableName() const { return variableName.get(); }
	Node* Value() const { return value.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> type;
	std::unique_ptr<IdentifierNode> variableName;
	std::unique_ptr<Node> value;
};

class AssignmentStatementNode : public Node
{
public:
	AssignmentStatementNode(IdentifierNode* variableName_, Node* value_);
	IdentifierNode* VariableName() const { return variableName.get(); }
	Node* Value() const { return value.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<IdentifierNode> variableName;
	std::unique_ptr<Node> value;
};

class ParameterNode : public Node
{
public:
	ParameterNode(Node* paramType_, IdentifierNode* paramName_);
	Node* ParamType() const { return paramType.get(); }
	IdentifierNode* ParamName() const { return paramName.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> paramType;
	std::unique_ptr<IdentifierNode> paramName;
};

class FunctionNode : public Node
{
public:
	FunctionNode(Node* returnType_, IdentifierNode* functionName_);
	Node* ReturnType() const { return returnType.get(); }
	IdentifierNode* FunctionName() const { return functionName.get(); }
	void AddParam(ParameterNode* param);
	const std::vector<std::unique_ptr<ParameterNode>>& Parameters() const { return parameters; }
	void SetBody(CompoundStatementNode* body_);
	CompoundStatementNode* Body() const { return body.get(); }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::unique_ptr<Node> returnType;
	std::unique_ptr<IdentifierNode> functionName;
	std::vector<std::unique_ptr<ParameterNode>> parameters;
	std::unique_ptr<CompoundStatementNode> body;
};

class SourceFileNode : public Node
{
public:
	SourceFileNode();
	void AddFunction(FunctionNode* function);
	const std::vector<std::unique_ptr<FunctionNode>>& Functions() const { return functions; }
	void Accept(minilang::visitor::Visitor& visitor) override;
private:
	std::vector<std::unique_ptr<FunctionNode>> functions;
};

} // namespace minilang::ast
