import std;
import foo;

int main()
{
    auto x = 1;
    using Type = decltype(x);
    Foo<Type>::foo(x);
}
