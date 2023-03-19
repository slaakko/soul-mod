import std.core;

int main()
{
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    auto it1 = s.find(1);
    if (it1 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it2 = s.find(2);
    if (it2 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it3 = s.find(3);
    if (it3 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it4 = s.find(-1);
    if (it4 != s.end())
    {
        std::cout << "bug" << "\n";
    }
    else
    {
        std::cout << "ok" << "\n";
    }
    auto it5 = s.find(4);
    if (it5 != s.end())
    {
        std::cout << "bug" << "\n";
    }
    else
    {
        std::cout << "ok" << "\n";
    }
    return 0;
}
