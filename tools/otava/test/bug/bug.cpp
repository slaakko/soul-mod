import std.core;


void foo(char*& x, char*& y)
{
    std::swap(x, y);
}

int main()
{
    return 0;
}
