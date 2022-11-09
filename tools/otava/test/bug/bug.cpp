import std.core;

template<class T>
void bug(T& x)
{
    T temp(std::move(x));
}

int main()
{
    int x = 0;
    bug(x);
    return 0;
}
