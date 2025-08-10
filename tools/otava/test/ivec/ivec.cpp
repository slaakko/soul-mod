import std;
import ivec;

int main()
{
    std::vector<int> v;
    v.push_back(1);
    int x = 2;
    v.push_back(std::move(x));
    v.push_back(3);
    print_ivec(v);
    v.insert(v.begin() + 1, 9);
    v.insert(v.begin() + 2, 3, 7);
    print_ivec(v);
    v.erase(v.begin() + 1);
    print_ivec(v);
    v.erase(v.begin() + 1, v.begin() + 4);
    print_ivec(v);
    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(4);
    if (v == v2)
    {
        std::cout << "bug\n";
    }
    if (v < v2)
    {
        std::cout << "yep\n";
    }
}
