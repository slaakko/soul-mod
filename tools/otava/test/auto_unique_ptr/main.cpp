import std;

class CompoundStatementNode;
class ReturnStatementNode;

class Visitor
{
public:
    Visitor() {}
    virtual ~Visitor() {}
    virtual void Visit(CompoundStatementNode& node) {}
    virtual void Visit(ReturnStatementNode& node) {}
};

class DefaultVisitor : public Visitor
{
public:
    DefaultVisitor() : Visitor() {}
    void Visit(CompoundStatementNode& node) override;
};

class ModifierVisitor : public DefaultVisitor
{
public:
    ModifierVisitor() : DefaultVisitor() {}
    void Visit(ReturnStatementNode& node) override;
};

class Node
{
public:
    virtual ~Node() {}
    virtual void Accept(Visitor& visitor) = 0;
};

class StatementNode : public Node
{
public:
};

class CompoundStatementNode : public StatementNode
{
public:
    inline const std::vector<std::unique_ptr<StatementNode>>& Statements() const { return statements; };
    void AddStatement(StatementNode* statement)
    {
        statements.push_back(std::unique_ptr<StatementNode>(statement));
    }
    void Accept(Visitor& visitor) override
    {
        visitor.Visit(*this);
    }
private:
    std::vector<std::unique_ptr<StatementNode>> statements;
};

class ReturnStatementNode : public StatementNode
{
public:
    ReturnStatementNode() : foo("foo") {}
    void ReturnStatementNode::Accept(Visitor& visitor) override
    {
        visitor.Visit(*this);
    }
    const std::string& Foo() const { return foo; }
private:
    std::string foo;
};

void DefaultVisitor::Visit(CompoundStatementNode& node) 
{
    for (const auto& stmt : node.Statements())
    {
        stmt->Accept(*this);
    }
}

void ModifierVisitor::Visit(ReturnStatementNode& node)
{
    std::cout << node.Foo() << "\n";
}

int main()
{
    std::unique_ptr<CompoundStatementNode> block(new CompoundStatementNode());
    block->AddStatement(new ReturnStatementNode());
    ModifierVisitor visitor;
    block->Accept(visitor);
}

