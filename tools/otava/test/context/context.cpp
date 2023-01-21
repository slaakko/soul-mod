import std.core;

void bar(void* ctx)
{
    restore_context(ctx, 1);
}

void foo()
{
    void* ctx = malloc(256);
    if (save_context(ctx) > 0)
    {
        prints("from restore", 1);
    }
    else
    {
        prints("from save", 1);
        bar(ctx);
    }
}

int main()
{
    foo();
    return 0;
}
