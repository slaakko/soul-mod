export module cls;

import std.core;

export namespace ns {

class Class
{
public:
    Class();
    Class(int x_);
    virtual ~Class();
    virtual void Foo();
    virtual void Bar();
    int X() const { return x; }
private:
    int x;
};

} // namespace ns
