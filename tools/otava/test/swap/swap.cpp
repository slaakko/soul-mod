import std;

int main()
{
    int x = 1;
    int y = 2;
    std::cout << x << y << "\n";
    std::swap(x, y);
    std::cout << x << y << "\n";
    char a = 'a';
    char b = 'b';
    const char* pa = &a;
    const char* pb = &b;
    std::cout << *pa << *pb << "\n";
    std::swap(pa, pb);
    std::cout << *pa << *pb << "\n";
}
