import std.core;

int main()
{ 
    const char* a = "abc";
    std::string b = "def";
    std::string s = a + b;
    std::cout << s << "\n";
    return 0;
}
