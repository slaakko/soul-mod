import std;

int foo()
{
    return 1;
}

int main()
{
    try
    {
        std::string s;
        return foo();
    }
    catch (...)
    {
    }
}
