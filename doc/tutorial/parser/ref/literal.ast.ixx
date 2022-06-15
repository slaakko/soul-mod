// ast.ixx:

export module minilang.ast;

// ...

class BooleanLiteralNode : public Node
{
public:
	BooleanLiteralNode(bool value_);
	bool Value() const { return value; }
	// ...
private:
	bool value;
};

class IntegerLiteralNode : public Node
{
public:
	IntegerLiteralNode(int64_t value_);
	int64_t Value() const { return value; }
	// ...
private:
	int64_t value;
};

// ...
