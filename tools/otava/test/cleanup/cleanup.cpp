import std.core;

class Foo
{
public:
    ~Foo();
};

Foo::~Foo()
{

}

void bar(int i)
{
    std::cout << i << std::endl;
}

void a()
{
    Foo foo;
    int i = 3;
    while (i > 0)
    {
        Foo foo2;
        --i;
    }
}

void b()
{
    Foo foo;
    int i = 3;
    while (i > 0)
    {
        Foo foo2;
        bar(i);
        --i;
    }
}

int main()
{
    a();
    b();
    return 0;
}