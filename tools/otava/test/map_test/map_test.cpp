import std;

class Node
{
public:
    Node(int index_) : index(index_) {}
    int Index() const { return index; }
private:
    int index;
};

class Symbol
{
public:
    Symbol(int index_) : index(index_) {}
    int Index() const { return index; }
private:
    int index;
};

std::vector<Node*> Pick(const std::vector<std::unique_ptr<Node>>& nodes, const std::vector<int>& p)
{
    std::vector<Node*> s;
    for (int i = 0; i < p.size(); ++i)
    {
        int index = p[i];
        s.push_back(nodes[index].get());
    }
    return s;
}

void Map(std::map<Node*, Symbol*>& map, const std::vector<Node*>& s, const std::vector<std::unique_ptr<Symbol>>& symbols)
{
    for (int i = 0; i < s.size(); ++i)
    {
        Node* node = s[i];
        Symbol* symbol = symbols[i].get();
        map[node] = symbol;
    }
}

Symbol* GetSymbol(const std::map<Node*, Symbol*>& map, Node* node)
{
    Symbol* symbol = nullptr;
    auto it = map.find(node);
    if (it != map.end())
    {
        symbol = it->second;
    }
    return symbol;
}

void map_test(int n)
{
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Symbol>> symbols;
    std::vector<int> p;
    for (int i = 0; i < n; ++i)
    {
        nodes.push_back(std::unique_ptr<Node>(new Node(i)));
        symbols.push_back(std::unique_ptr<Symbol>(new Symbol(i)));
        p.push_back(i);
    }
    do
    {
        std::vector<Node*> s = Pick(nodes, p);
        std::map<Node*, Symbol*> map;
        Map(map, s, symbols);
        for (int i = 0; i < s.size(); ++i)
        {
            Node* node = s[i];
            Symbol* symbol = GetSymbol(map, node);
            if (!symbol)
            {
                std::cout << "symbol for node " << node->Index() << " not found" << "\n";
                std::exit(1);
            }
        }
    } 
    while (std::next_permutation(p.begin(), p.end()));
}

int main()
{
    int n = 9;
    for (int i = 0; i < n; ++i)
    {
        std::cout << "> " << i << "\n";
        map_test(i);
    }
}
