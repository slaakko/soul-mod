import std;

void foo(const std::string& msg)
{
    throw std::runtime_error(msg);
}

int main()
{
    std::string msg = "runtime error: foo";
    try
    {
        try
        {
            foo(msg);
        }
        catch (...)
        {
            throw;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
    return 0;
}
