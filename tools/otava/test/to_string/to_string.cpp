import std.core;

int main()
{
    std::string s = std::to_string(10);
    prints(s.c_str());
    prints("\n");
    std::string s1 = std::to_string(100);
    prints(s1.c_str());
    prints("\n");
    std::string s2 = std::to_string(-100);
    prints(s2.c_str());
    prints("\n");
    std::string s3 = std::to_string(1000);
    prints(s3.c_str());
    prints("\n");
    std::string s4 = std::to_string(10000);
    prints(s4.c_str());
    prints("\n");
    std::string s5 = std::to_string(100000);
    prints(s5.c_str());
    prints("\n");
    std::string s6 = std::to_string(1000000);
    prints(s6.c_str());
    prints("\n");
    std::string s7 = std::to_string(10000000);
    prints(s7.c_str());
    prints("\n");
    return 0;
}
