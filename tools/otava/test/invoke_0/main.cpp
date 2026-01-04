import std;

void foo()
{
    throw 1;
}

int main()
{
    try
    {
        std::string s("foo");
        foo();
    }
    catch (int& x)
    {
    }
}
