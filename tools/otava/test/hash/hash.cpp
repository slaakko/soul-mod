import std.core;

int main()
{
    std::string abc = "abc";
    std::hash<std::string>()(abc);
    return 0;
}
