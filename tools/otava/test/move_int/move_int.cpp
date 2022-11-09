import std.core;

int main()
{
    int x = 0;
    int&& y = std::move(x);
    return 0;
}
