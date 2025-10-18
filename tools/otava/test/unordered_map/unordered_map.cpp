import std;

template class std::unordered_map<std::string, int>;

void print(const std::unordered_map<std::string, int>& m)
{
    for (const auto& p : m)
    {
        std::cout << p.first << " : " << p.second << "\n";
    }
}

int main()
{
    std::unordered_map<std::string, int> m;
    m["foo"] = 1;
    print(m);
}
