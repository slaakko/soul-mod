import std;

void alpha()
{
}

void bar()
{
}

void foo()
{
    try
    {
        alpha();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
    }
}

void bazz()
{
    try
    {
        bar();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
    }
}

int main()
{
    foo();
    bazz();
}
