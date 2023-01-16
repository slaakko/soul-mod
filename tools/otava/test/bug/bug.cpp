import std.core;

using value_type = int;

struct node_type
{
    node_type(const value_type& value_, node_type* p) : value(value_), parent(p) {}
    value_type value;
    node_type* parent;
};

struct iterator
{
    iterator() : n(nullptr) {}
    iterator(node_type* n_) : n(n_) {}
    node_type* n;
};

class Tree
{
public:
    iterator insert(node_type* x, node_type* p, const value_type& value)
    {
        node_type* n = new node_type(value, p);
        return iterator(n);
    }
    std::pair<iterator, bool> insert(const value_type& value)
    {
        node_type* x = nullptr;
        node_type* p = nullptr;
        iterator it = insert(x, p, value);
        return std::make_pair(it, true);
    }
};

int main()
{
    Tree tree;
    tree.insert(1);
}
