import std.core;

int main()
{
    std::map<int, int> m;
    m[0] = 0;
    m[1] = 2;
    m[2] = 4;
    auto it1 = m.find(0);
    if (it1 != m.end())
    {
        std::cout << it1->second << "\n";
    }
    auto it2 = m.find(1);
    if (it2 != m.end())
    {
        std::cout << it2->second << "\n";
    }
    auto it3 = m.find(2);
    if (it3 != m.end())
    {
        std::cout << it3->second << "\n";
    }
    auto it4 = m.find(3);
    if (it4 != m.end())
    {
        std::cout << "bug" << "\n";
    }
    else
    {
        std::cout << "OK" << "\n";
    }
    return 0;
}
