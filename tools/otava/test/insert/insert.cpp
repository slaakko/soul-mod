import std;

int main()
{
    std::string foo = "foo";
    std::cout << foo << "\n";
    std::string abc = "abc";
    std::cout << abc << "\n";
    foo.insert(1, abc, 1);
    std::cout << foo << "\n";
}
