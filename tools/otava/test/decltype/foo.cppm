export module foo;

import std;

template<typename T>
struct Foo
{
    static void foo(T& x);
};
