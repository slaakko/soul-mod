import std;

class Foo
{
public:
    Foo();
    ~Foo();
};

Foo::Foo()
{
    std::cout << "Foo::Foo()" << "\n";
}

Foo::~Foo()
{
    std::cout << "Foo::~Foo()" << "\n";
}

void bar()
{
    throw 1;
}

int main()
{
    try
    {
        Foo foo;
        bar();
    }
    catch (int& x)
    {
        std::cout << x << "\n";
    }
}
