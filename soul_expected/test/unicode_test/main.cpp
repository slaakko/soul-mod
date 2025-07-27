import std;
import util_expected;

int main()
{
    auto rv = util::Init();
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        return 1;
    }
    util::CodeFormatter formatter(std::cout);
    std::string m = "öhkömömmö";
    auto u = util::ToUpper(m);
    if (!u)
    {
        std::cerr << util::GetErrorMessage(u.error()) << "\n";
        return 1;
    }
    std::string us = *u;
    rv = formatter.WriteLine(m);
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        return 1;
    }
    rv = formatter.WriteLine(us);
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        return 1;
    }
    util::Done();
}