import std.core;

int main()
{
    std::map<int, int> m;
    m[1] = 2;
    auto it = m.find(1);
    if (it != m.end())
    {
        std::string s = std::to_string(it->second);
        std::cout << s << "\n";
    }
    return 0;
}
