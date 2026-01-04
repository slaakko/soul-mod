import std;

void foo(int local)
{
    std::cout << "foo: " << local << "\n";
    throw 1;
}

int main()
{
    int local = 10;
    try
    {
        foo(local);
    }
    catch (int& x)
    {
        std::cout << "handler: " << local << ", " << x << "\n";
    }
}
