import std;

int main()
{
    std::string foo = "foo";
    std::string abc = "abc";
    foo.replace(1, 1, abc);
    std::cout << foo << "\n";
}
