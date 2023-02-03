import std.core;

class Foo
{
public:
    Foo();
    static Foo& Instance();
    void foo();
private:
    int x;
};

Foo::Foo() : x(1) 
{
}

Foo& Foo::Instance()
{
    static Foo instance;
    return instance;
}

void Foo::foo()
{
    std::cout << "foo" << " " << x << "\n";
}

int main()
{
    Foo::Instance().foo();
    return 0;
}
