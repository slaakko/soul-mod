import std.core;

int main()
{
    std::string s("foo\n");
    prints(s.c_str());

    std::string t("fuzzy", 3);
    prints(t.c_str());
    prints("\n");

    const char* us = "qwerty";
    std::string u(us, 3);
    prints(u.c_str());
    prints("\n");

    std::string c(u);
    c.append(1, 'Q');
    prints(c.c_str());
    prints("\n");

    std::string d(std::move(c));
    prints(d.c_str());
    prints("\n");

    return 0;
}
