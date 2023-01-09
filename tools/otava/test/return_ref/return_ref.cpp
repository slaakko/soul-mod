import std.core;

template<typename T>
class Foo
{
public:
    Foo(const T& x_) : x(x_) {}
    T& get() { return x; }
private:
    T x;
};

int main()
{
    Foo<int> foo;
    int x = foo.get();
    return 0;
}
