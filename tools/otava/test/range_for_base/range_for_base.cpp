import std.core;

int main()
{
    std::string s;
    auto end = s.end();
    for (auto it = s.begin(); it != end; ++it)
    {
        auto c = *it;
    }
}
