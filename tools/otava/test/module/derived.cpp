module drv;

namespace ns {

Derived::Derived() : Class(0), y(0)
{
}

Derived::Derived(int x_, int y_) : Class(x_), y(y_)
{
}

void Derived::Bar()
{
    prints("Derived::Bar\n");
    prints("x = ");
    std::string s = std::to_string(X());
    prints(s.c_str());
    prints("\n");
    prints("y = ");
    std::string t = std::to_string(y);
    prints(t.c_str());
    prints("\n");
}

} // namespace ns
