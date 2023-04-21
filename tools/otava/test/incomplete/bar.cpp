module bar;

import foo;

Bar::Bar() : foo(nullptr)
{
}

void Bar::f()
{
    foo->Print();
}