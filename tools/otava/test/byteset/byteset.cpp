import std.core;
import util;

template<typename Container>
void print(Container& c)
{
    bool first = true;
    for (auto x : c)
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
    std::cout << "\n";
}

void test_set(const std::vector<int>& v)
{
    print(v);
    std::set<int> s;
    for (auto x : v)
    {
        s.insert(x);
    }
    print(s);
    std::cout << "******************************\n";
}

void test_set(int n, std::vector<int>& r, int& index)
{
    std::vector<int> v;
    for (int i = 0; i < n; ++i)
    {
        int k = index++;
        k %= 1000;
        v.push_back(r[k]);
    }
    print(v);
    test_set(v);
}

extern "C" void set_rand_seed(uint64_t seed);

int main()
{
    std::vector<int> s;
    util::FileStream fs("C:\\work\\rnd\\rnd.bin", util::OpenMode::read | util::OpenMode::binary);
    util::BinaryStreamReader reader(fs);
    for (int i = 0; i < 1000; ++i)
    {
        uint32_t x = reader.ReadUInt();
        s.push_back(static_cast<int>(x));
    }
    int index = 0;
    for (int i = 0; i < 256; ++i)
    {
        test_set(i, s, index);
    }
    return 0;
}
