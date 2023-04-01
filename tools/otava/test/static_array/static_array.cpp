import std.core;

int* foo()
{
    static int x[] = { 1, 2, 3 };
    return x;
}

int main()
{
    int* y = foo();
}