import std;

bool foo(int index)
{
    return index < 2;
}

int main()
{
    int index = 0;
    while (bool b = foo(index))
    {
        std::cout << index << "\n";
        ++index;
    }
}
