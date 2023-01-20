import std.core;

struct foo
{
    foo();
    void print();
    int a[5];
};

foo::foo() : a()
{
    for (int i = 0; i < 5; ++i)
    {
        a[i] = i;
    }
}

void foo::print()
{
    for (int x : a)
    {
        std::cout << x << "\n";
    }
}

int main()
{
    foo f;
    f.print();
    return 0;
}
