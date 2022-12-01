import std.core;

class Foo
{
public:
    Foo();
private:
    char* chars;
    ssize_t len;
    ssize_t res;
};

Foo::Foo() : chars(nullptr), len(0), res(0)
{
}

int main()
{
    Foo foo;
}
