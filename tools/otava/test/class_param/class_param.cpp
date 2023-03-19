import std.core;

class Foo
{
};

void bar(Foo foo)
{
}

int main()
{
    Foo foo;
    bar(foo);
    return 0;
}
