import std.core;

void print(const char* s)
{
    prints(s, 1);
}

void print(const std::string& s)
{
    prints(s.c_str(), 1);
}

int main()
{
    print("foo\n");
    return 0;
}
