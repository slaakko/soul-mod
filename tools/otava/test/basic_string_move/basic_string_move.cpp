import std.core;

int main()
{
    std::basic_string<char> foo("foo");
    std::basic_string<char> bar(std::move(foo));
    return 0;
}
