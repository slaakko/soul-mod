import std;

void foo(int local0, int local1)
{
    std::cout << "foo: " << local0 << ", " << local1 << "\n";
    throw 1;
}

int main()
{
    int local0 = 10;
    try
    {
        int local1 = 20;
        try
        {
            foo(local0, local1);
        }
        catch (int& x)
        {
            std::cout << "inner: " << x << ", " << local0 << ", " << local1 << "\n";
            throw 2;
        }
    }
    catch (int& x)
    {
        std::cout << "outer: " << x << ", " << local0 << "\n";
    }
}
