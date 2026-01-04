import std;

int foo()
{
    return 1;
}

int main()
{
    try
    {
        return foo();
    }
    catch (...)
    {
        std::cout << "exception thrown" << "\n";
    }
}
