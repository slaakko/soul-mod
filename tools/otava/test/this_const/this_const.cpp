import std;

class Bar
{
public:
    void foo()
    {
        std::cout << "foo" << "\n";
    }
    void foo() const
    {
        std::cout << "foo const" << "\n";
    }
};

class Foo
{
public:
    void foo() const
    {
        bar.foo();
    }
private:
    Bar bar;
};

int main()
{
    Foo f;
    f.foo();
}
