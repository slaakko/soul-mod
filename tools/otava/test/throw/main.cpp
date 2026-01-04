import std;

int main()
{
    try
    {
        throw 1;
    }
    catch (int& ex)
    {
        std::cout << ex << "\n";
    }
}
