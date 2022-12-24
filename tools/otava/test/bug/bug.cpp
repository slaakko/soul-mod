import std.core;

int main()
{
    int x = 100;
    int y(x);
    int z(std::move(x));
}
