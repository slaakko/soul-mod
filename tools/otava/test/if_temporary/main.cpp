import std;

bool TypesEqual(int a, int b)
{
    return a == b;
}

int foo(const std::string& name, const std::string& className)
{
    int a = 0;
    int b = 0;
    int s = 1;
    if (s == 1 && TypesEqual(a, b) && name == "~" + className) return 1;
    return 0;
}

int main()
{
    int x = foo("abc", "def");
}
