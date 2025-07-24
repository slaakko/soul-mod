import std;

std::expected<bool, int> foo(bool x)
{
    if (x)
    {
        return x;
    }
    else
    {
        return std::unexpected<int>(1);
    }
}

int main()
{
    std::expected<int, int> exp0;
    if (exp0)
    {
        std::cout << exp0.value() << "\n";
    }
    std::expected<int, int> exp1(1);
    if (exp1)
    {
        std::cout << exp1.value() << "\n";
    }
    std::expected<int, int> exp2(std::unexpected<int>(1));
    if (!exp2)
    {
        std::cout << exp2.error() << "\n";
    }
    exp1 = 2;
    if (exp1)
    {
        std::cout << exp1.value() << "\n";
    }
    exp2 = std::unexpected<int>(2);
    if (!exp2)
    {
        std::cout << exp2.error() << "\n";
    }
    std::expected<bool, int> expTrue = foo(true);
    if (expTrue)
    {
        std::cout << "true" << "\n";
    }
    else
    {
        std::cout << "false" << "\n";
    }
    std::expected<bool, int> expFalse = foo(false);
    if (expFalse)
    {
        std::cout << "true" << "\n";
    }
    else
    {
        std::cout << "false" << "\n";
    }
}
