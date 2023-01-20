import std.core;

int main()
{
    std::string s("foo\n");
    prints(s.c_str(), 1);

    std::string t("fuzzy", 3);
    prints(t.c_str(), 1);
    prints("\n", 1);

    const char* us = "qwerty";
    std::string u(us, 3);
    prints(u.c_str(), 1);
    prints("\n", 1);

    std::string c(u);
    c.append(1, 'Q');
    prints(c.c_str(), 1);
    prints("\n", 1);

    std::string d(std::move(c));
    prints(d.c_str(), 1);
    prints("\n", 1);

    return 0;
}
