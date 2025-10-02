import std;

int main()
{
    int x = static_cast<int>(true);
    std::cout << x << "\n";
    int y = static_cast<int>(false);
    std::cout << y << "\n";
}
