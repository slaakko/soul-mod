import std;

int main()
{
    std::cout << true << "\n";
    std::cout << false << "\n";
    unsigned long long x = 123456789;
    std::cout << x << "\n";
    const void* v = &x;
    std::cout << v << "\n";
    float xf = 123.45f;
    std::cout << xf << "\n";
    double xd = 1234.5678;
    std::cout << xd << "\n";
    std::cout << nullptr << "\n";
    std::cout << 123 << "\n";
    std::cout << std::endl;
}
