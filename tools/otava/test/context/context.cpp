import std.core;

void foo()
{
    prints(">foo\n", 1);
    void* ctx = pop_context();
    restore_context(ctx, 1);
    prints("<foo\n", 1);
}

void d()
{
    int x = 1;
    prints(">d\n", 1);
    std::cout << x << "\n";
    void* ctx = push_context();
    if (save_context(ctx) == 0)
    {
        foo();
    }
    else
    {
        void* ctx = pop_context();
        restore_context(ctx, 1);
    }
    prints("<d\n", 1);
    std::cout << x << "\n";
}

void c()
{
    int x = 2;
    prints(">c\n", 1);
    std::cout << x << "\n";
    void* ctx = push_context();
    if (save_context(ctx) == 0)
    {
        d();
        pop_context();
    }
    else
    {
        std::cout << "catch" << "\n";
        std::cout << x << "\n";
    }
    prints("<c\n", 1);
}

void b()
{
    int x = 3;
    prints(">b\n", 1);
    std::cout << x << "\n";
    c();
    std::cout << x << "\n";
    prints("<b\n", 1);
}

void a()
{
    int x = 4;
    prints(">a\n", 1);
    std::cout << x << "\n";
    b();
    std::cout << x << "\n";
    prints("<a\n", 1);
}

int main()
{
    int x = 5;
    std::cout << x << "\n";
    a();
    std::cout << x << "\n";
    return 0;
}
