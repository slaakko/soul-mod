import std.core;

int main()
{
    std::set<int> s;
    s.insert(1);
    auto it = s.find(1);
    return 0;
}
