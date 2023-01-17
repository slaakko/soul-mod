import std.core;

int main()
{
    std::string s = std::to_string(12345);
    std::string t;
    for (char c : s)
    {
        t.append(1, c);
    }
    prints(t.c_str());
    prints("\n");
    return 0;
}
