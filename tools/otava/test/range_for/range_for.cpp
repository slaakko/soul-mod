import std.core;

int main()
{
    std::string s = std::to_string(12345);
    std::string t;
    for (char c : s)
    {
        t.append(1, c);
    }
    prints(t.c_str(), 1);
    prints("\n", 1);
    return 0;
}
