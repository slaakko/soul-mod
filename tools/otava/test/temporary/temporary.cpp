import std.core;

enum class foo
{
    x = 1 << 0, y = 1 << 1
};

foo operator|(foo left, foo right)
{
    return foo(int(left) | int(right));
}

int main()
{
    foo x = foo::x | foo::y;
    return 0;
}
