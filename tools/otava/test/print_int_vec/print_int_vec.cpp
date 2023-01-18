import std.core;

int main()
{
    std::vector<int> v;
    for (int i = 1; i <= 10; ++i)
    {
        v.push_back(i);
    }

    bool first = true;
    for (auto x : v)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << ", ";
        }
        std::cout << x;
    }

    std::cout << "\n";

    return 0;
}
