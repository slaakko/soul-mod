import std.core;

int main()
{
    std::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    for (auto x : list)
    {
        std::cout << x << "\n";
    }
    return 0;
}
