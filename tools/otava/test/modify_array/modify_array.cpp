import std.core;

int main()
{
    int a[3];
    for (auto& x : a)
    {
        x = 1;
    }
    for (auto x : a)
    {
        std::cout << x << "\n";
    }
}