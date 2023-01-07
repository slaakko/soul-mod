import std.core;

class Foo
{
public:
    ~Foo() {}
    void foo()
    {
        prints("foo\n");
    }
};

int main()
{
    std::unique_ptr<Foo> p(new Foo());
    p->foo();
    if (p)
    {
        p.reset();
    }
    return 0;
}
