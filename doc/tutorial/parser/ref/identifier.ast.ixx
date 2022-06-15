// ast.ixx:

export module minilang.ast;

// ...

class IdentifierNode : public Node
{
public:
	IdentifierNode(const std::u32string& str_);
	const std::u32string& Str() const { return str; }
	// ...
private:
	std::u32string str;
};

// ...
