import std.core;

void find_empty()
{
    std::string s;
    std::string str;
    std::string::size_type p = s.find(str);
    std::cout << p << "\n";
    std::string abc = "abc";
    p = s.find(abc);
    std::cout << p << "\n";
    p = s.find("");
    std::cout << p << "\n";
    p = s.find("abc");
    std::cout << p << "\n";
}

void find_abc()
{
    std::string s = "abc";
    std::string str;
    std::string::size_type p = s.find(str);
    std::cout << p << "\n";
    std::string abc = "abc";
    p = s.find(abc);
    std::cout << p << "\n";
    p = s.find("");
    std::cout << p << "\n";
    p = s.find("abc");
    std::cout << p << "\n";
}

void rfind()
{
    std::string path = "/home/user/helena";
    std::string::size_type p = path.rfind('/');
    std::cout << p << "\n";
    p = path.rfind("/");
    std::cout << p << "\n";
    std::string s = "/";
    p = path.rfind(s);
    std::cout << p << "\n";
}

int main()
{
    find_empty();
    find_abc();
    rfind();
}
