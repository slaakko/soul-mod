import std;

void add(std::vector<int>& vec)
{
    bool e = vec.empty();
    std::cout << e << "\n";
    int n = 10;
    for (int i = 0; i < n; ++i)
    {
        vec.push_back(i);
    }
}

void print(const std::vector<int>& vec)
{
    std::cout << vec.size() << "\n";
    int n = vec.size();
    for (int i = 0; i < n; ++i)
    {
        std::cout << vec[i] << "\n";
    }
}

int main()
{
    std::vector<int> vec;
    add(vec);
    print(vec);
}
