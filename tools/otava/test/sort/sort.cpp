import std;

int main()
{
    std::vector<int> v;
    int n = 32;
    for (int i = 0; i < n; ++i)
    {
        int x = static_cast<int>(std::random() & 0x7FFFFFFFu);
        v.push_back(x);
    }
    std::sort(v.begin(), v.end());
    for (auto x : v)
    {
        std::cout << x << "\n";
    }
}
