import std.core;

int main()
{
    char* x = static_cast<char*>(malloc(1));
    x[0] = '\0';
    return 0;
}
