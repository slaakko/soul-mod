import std.core;

struct node
{
    node(int x_) : x(x_) {}
    int get_x() const { return x; }
    int x;
};

void print(node* n)
{
    int x = n->get_x();
    std::string s = std::to_string(x);
    prints(s.c_str());
    prints("\n");
}

void foo(node* a, node* b, node* c, node* d, node* e, node* f, node* g, node* h)
{
    print(a);
    print(b);
    print(c);
    print(d);
    print(e);
    print(f);
    print(g);
    print(h);
}

int main()
{
    node* a = new node(1);
    node* b = new node(2);
    node* c = new node(3);
    node* d = new node(4);
    node* e = new node(5);
    node* f = new node(6);
    node* g = new node(7);
    node* h = new node(8);
    foo(a, b, c, d, e, f, g, h);
    return 0;
}
