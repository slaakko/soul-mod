import std.core;

class Foo
{
public:
    Foo(int x_);
    virtual ~Foo();
    virtual void foo();
private:
    int x;
};

Foo::Foo(int x_) : x(x_)
{
}

Foo::~Foo()
{
}

void Foo::foo()
{
    prints("foo\n", 1);
    std::string s = std::to_string(x);
    prints(s->c_str(), 1);
    prints("\n", 1);
}

int main()
{
    Foo* f = new Foo(1);
    f->foo();
    return 0;
}
