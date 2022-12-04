import std.core;

int main()
{
    std::string s("foo\n");
    prints(s.c_str());

    std::string t("fuzzy", 3);
    prints(t.c_str());
    prints("\n");

    const char* us = "qwerty";
    //std::string u(us, us + 3);
    //prints(u.c_str());
    //prints("\n");
    return 0;
}
