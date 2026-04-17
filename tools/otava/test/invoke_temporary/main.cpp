import std;

std::string bazz(const std::string& s)
{
    std::string bazz("bazz");
    return bazz.c_str();
}

std::string bar(const std::string& s)
{
    std::string bar("bar");
    return bar + "." + s;
}

std::string foo(const std::string& s)
{
    std::string f("foo");
    return bar(bazz(s));
}

int main()
{
    std::string s("s");
    std::sting f = foo("foo");
    std::cout << f << "\n";
}
