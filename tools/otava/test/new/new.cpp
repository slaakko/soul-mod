import std.core;

void new_int()
{
    int* x = new int(1);
}

struct foo
{
    foo(int x_) : x(x_) {}
    int x;
};

void new_foo()
{
    foo* f = new foo(1);
}

void new_placement()
{
    int x;
    new (&x) int(1);
}

int main()
{
    new_int();
    new_foo();
    new_placement();
    return 0;
}
