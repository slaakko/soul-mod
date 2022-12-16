import std.core;

class Foo
{
public:
    Foo(int x_) : x(x_) {}
    Foo(Foo&& that) : x(that.x) {}
private:
    int x;
};

Foo foo()
{
    Foo f(1);
    return f;
}

int main()
{
    Foo x = foo();
}
