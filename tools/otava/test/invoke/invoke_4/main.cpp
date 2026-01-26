import std;

void foo(bool x)
{
    if (x)
    {
        std::string s("abc");
        throw std::runtime_error(s);
    }
}

int main()
{
    try
    {
        foo(true);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << "\n";
    }
}
