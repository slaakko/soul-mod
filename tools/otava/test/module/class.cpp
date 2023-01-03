module cls;

namespace ns {

Class::Class() : x(0)
{
}

Class::Class(int x_) : x(x_)
{
}

Class::~Class()
{
}

void Class::Foo()
{
    prints("Class::Foo\n");
    std::string s = std::to_string(x);
    prints(s.c_str());
    prints("\n");
}

void Class::Bar()
{
    prints("Class::Bar\n");
    std::string s = std::to_string(x);
    prints(s.c_str());
    prints("\n");
}

} // namespace ns
