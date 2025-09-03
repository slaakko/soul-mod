module foo;

template<typename T>
void Foo<T>::foo(T& x)
{
    std::cout << x << "\n";
}

template struct Foo<int>;
