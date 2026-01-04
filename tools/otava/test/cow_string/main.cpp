import std;

int main()
{
    std::cow_string s0;
    std::cout << s0.c_str() << "\n";
    std::cow_string s1("cow");
    std::cout << s1.c_str() << "\n";
    std::cow_string s2(s1);
    std::cout << s2.c_str() << "\n";
}
