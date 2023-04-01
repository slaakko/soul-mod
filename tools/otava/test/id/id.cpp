import std.core;

template<typename T>
const T& id(const T& x);

template<>
int id<int>(int x);

int main()
{
    int x = id<int>(1);
    return 0;
}

template<typename T>
const T& id(const T& x)
{
    return x;
}

template<>
int id<int>(int x)
{
    return 1;
}
