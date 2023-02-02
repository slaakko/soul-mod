import std.core;

void c()
{
    void* ctx = pop_context();
    restore_context(ctx, 123);
}

void b()
{
    std::cout << ">b" << "\n";
    c();
    std::cout << "<b" << "\n";
}

void a()
{
    std::cout << ">a" << "\n";
    b();
    std::cout << "<a" << "\n";
}

int main()
{
    int x = 1;
    void* ctx = push_context();
    int rv = save_context(ctx);
    if (rv == 0)
    {
        a();
    }
    else
    {
        std::cout << "catch " << x << " " << rv << "\n";
    }
}