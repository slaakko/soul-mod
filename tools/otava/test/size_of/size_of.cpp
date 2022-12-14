import std.core;

struct Foo
{
    int x;
};

int main()
{
    size_t i = sizeof(int);
    size_t l = sizeof(long long);
    size_t f = sizeof(Foo);
    return 0;
}