export module bar;

import std.core;

class Foo;

class Bar
{
public:
    Bar();
    void SetFoo(Foo* foo_) { foo = foo_; }
    Foo* GetFoo() const { return foo; }
    void f();
private:
    Foo* foo;
};

void test(Bar* bar)
{
    bar->f();
}
