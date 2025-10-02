import std;

struct Range
{
    std::int32_t first;
    std::int32_t last;
};

static constexpr int s1[] = { 1, 2, 3 };

static constexpr Range s20[] = { { 58, 58 }, { 65, 90 } };

int main()
{
    int i = 70;
    for (const Range& range : s20)
    {
        if (i >= range.first && i <= range.last)
        {
            std::cout << i << "\n";
        }
    }
}
