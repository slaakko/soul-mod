import std;

std::string foo()
{
    return "foo";
}

std::string bar()
{
    std::string s;
    return foo();
}

int main()
{
    std::string s = bar();
}
