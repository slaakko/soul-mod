import std;

std::expected<bool, int> fn()
{
    return std::unexpected<int>(1);
}

int main()
{
    std::expected<bool, int> rv = fn();
    fn();
}
