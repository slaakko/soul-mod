import std;

int main()
{
    std::string abc("abc");
    std::vector<std::string> v;
    v.push_back("s1");
    v.push_back("s2");
    for (const auto& s : v)
    {
        std::string filePath = "filePath";
        std::cout << filePath << "\n";
        std::cout << s << "\n";
    }
}
