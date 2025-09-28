import std;

int main()
{
    std::map<string, int> m;
    for (int i = 0; i < 100; ++i)
    {
        m[std::to_string(i)] = i;
    }
}