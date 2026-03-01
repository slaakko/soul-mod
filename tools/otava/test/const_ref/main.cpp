import std;

int main()
{
    std::map<int, std::string> m;
    m[1] = "foo";
    auto it = m.find(1);
    if (it != m.end())
    {
        const std::string& s = it->second;
        std::cout << s << "\n";
    }
}
