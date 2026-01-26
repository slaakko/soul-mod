import std;

int main()
{
    try
    {
        std::string abc("abc");
        std::cout << abc << "\n";
    }
    catch (...)
    {
        return 1;
    }
    return 0;
}
