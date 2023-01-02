import std.core;

class Foo
{
public:
    Foo(int x);
    virtual ~Foo();
};

Foo::Foo(int x)
{
}

Foo::~Foo()
{
}

int main()
{
    return 0;
}