import std.core;

int main()
{
    std::vector<int> x;
    x.push_back(2);
    x.push_back(1);
    x.push_back(3);
    std::sort(x.begin(), x.end());
    for (auto v : x)
    {
        std::cout << v << "\n";
    }
}