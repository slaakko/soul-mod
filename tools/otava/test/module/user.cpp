import std.core;
import cls;
import drv;

void test()
{
    ns::Class* c = new ns::Derived(10);
    c->Foo();
    c->Bar();
}

int main()
{
    test();
    return 0;
}
