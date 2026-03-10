import std;

std::string foo()
{
    std::string s = "foo";
    return s;
}

int main()
{
    std::string s = "s";
    std::string x = foo();
    std::cout << x << "\n";
}
