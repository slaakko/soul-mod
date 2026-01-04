import std;

int main()
{
    try
    {
        while (true)
        {
            long long int gigabyte = 1024ll * 1024ll * 1024ll;
            operator new(gigabyte);
        }
    }
    catch (const std::bad_alloc& ex)
    {
        std::cerr << "memory allocation failed: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
