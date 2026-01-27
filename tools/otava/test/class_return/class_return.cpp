import std.core;

class Foo
{
public:
    Foo() : x(0) {}
    Foo(int x_) : x(x_) {}
    Foo(Foo&& that) : x(that.x) {}
    inline int X() const { return x; }
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
    std::cout << x.X() << "\n";
}
