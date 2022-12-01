import std.core;

class foo
{
public:
    void f();
    void g();
};

void foo::f()
{
    g();
}

void foo::g()
{
}

int main()
{
    foo f;
    f.f();
    return 0;
}
