import std.core;

int main()
{
    std::int32_t x0 = 1;
    size_t hx0 = std::hash<std::int32_t>()(x0);
    std::cout << hx0 << "\n";
    std::int64_t x1 = 0xFFFEFDFCFBFAF9F8ll;
    size_t hx1 = std::hash<std::int64_t>()(x1);
    std::cout << hx1 << "\n";
    std::string abc = "abc";
    size_t hs = std::hash<std::string>()(abc);
    std::cout << hs << "\n";
    return 0;
}
