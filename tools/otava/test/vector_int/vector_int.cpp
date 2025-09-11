import std;

template class std::vector<int>;

int main()
{
    std::vector<int> v;
    int n = 100;
    for (int x = 0; x < n; ++x)
    {
        v.push_back(x);
    }
    for (int x : v)
    {
        std::cout << x << "\n";
    }
}
