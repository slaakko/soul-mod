import std.core;

int main()
{
    int a[3];
    for (int& x : a)
    {
        x = 1;
    }
    for (int x : a)
    {
        std::cout << x << "\n";
    }
}