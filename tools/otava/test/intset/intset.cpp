import std;

template class std::set<int>;
template class std::rb_tree<int, int, std::identity<int>, std::less<int>>;

void print(const std::set<int>& s)
{
    std::cout << "{";
    bool first = true;
    for (int x : s)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << ", ";
        }
        std::cout << x;
    }
    std::cout << "}\n";
}

void three()
{
    std::set<int> s;
    print(s);
    s.insert(1);
    print(s);
    s.insert(2);
    print(s);
    s.insert(3);
    print(s);
    auto it1 = s.find(1);
    if (it1 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it2 = s.find(2);
    if (it2 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it3 = s.find(3);
    if (it3 != s.end())
    {
        std::cout << "ok" << "\n";
    }
    else
    {
        std::cout << "bug" << "\n";
    }
    auto it4 = s.find(-1);
    if (it4 != s.end())
    {
        std::cout << "bug" << "\n";
    }
    else
    {
        std::cout << "ok" << "\n";
    }
    auto it5 = s.find(4);
    if (it5 != s.end())
    {
        std::cout << "bug" << "\n";
    }
    else
    {
        std::cout << "ok" << "\n";
    }
}

void thirtytwo()
{
    std::vector<int> v;
    std::set<int> s;
    for (int i = 0; i < 32; ++i)
    {
        int x = std::random() & 0x7FFFFFFFU;
        s.insert(x);
        v.push_back(x);
    }
    print(s);
    for (int i = 0; i < 32; ++i)
    {
        int index = std::random() % v.size();
        int x = v[index];
        std::cout << x << "\n";
        s.erase(x);
        v.erase(v.begin() + index);
        print(s);
    }
}

int main()
{
    three();
    thirtytwo();
}
