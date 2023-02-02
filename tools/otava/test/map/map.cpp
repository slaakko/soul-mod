import std.core;

int main()
{
    std::map<int, int> m;
    m[1] = 2;
    auto it = m.find(1);
    if (it != m.end())
    {
        std::string s = std::to_string(it->second);
        prints(s.c_str(), 1);
        prints("\n", 1);
    }
    return 0;
}
