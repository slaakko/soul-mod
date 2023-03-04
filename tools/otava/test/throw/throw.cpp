import std.core;

class Foo
{
public:
    ~Foo();
};

Foo::~Foo()
{
    std::cout << "Foo::~Foo() called" << std::endl;
}


void foo()
{
    Foo f;
    throw std::runtime_error("foo");
}

int main()
{
    int x = 10;
    try
    {
        foo();
    }
    catch (const std::exception& ex)
    {
        std::cout << "catch" << " " << x << " " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "catch" << " " << x << std::endl;
    }
    std::cout << "continue" << " " << x << std::endl;
    return 0;
}
