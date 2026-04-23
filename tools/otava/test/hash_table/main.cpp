import std;

void foo()
{
    std::unordered_map<int, int> m;
    m[0] = 1;
    auto it = m.find(0);
    if (it != m.end())
    {
        std::cout << it->second << "\n";
    }
}

int main()
{
    foo();
}
