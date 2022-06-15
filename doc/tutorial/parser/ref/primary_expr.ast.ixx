// ast.ixx:

export module minilang.ast;

// ...

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
	// ...
};
