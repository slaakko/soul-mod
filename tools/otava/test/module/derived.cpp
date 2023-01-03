module drv;

namespace ns {

Derived::Derived() : Class(0)
{
}

Derived::Derived(int x_) : Class(x_)
{
}

void Derived::Bar()
{
    prints("Derived::Bar\n");
    std::string s = std::to_string(X());
    prints(s.c_str());
    prints("\n");
}

} // namespace ns
