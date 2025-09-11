import std;

int main()
{
    std::vector<std::string> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::to_string(i));
    }
    for (const auto& s : v)
    {
        std::cout << s << "\n";
    }
}
