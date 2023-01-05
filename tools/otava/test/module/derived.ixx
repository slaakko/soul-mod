export module drv;

import std.core;
import cls;

export namespace ns {

class Derived : public Class
{
public:
    Derived();
    Derived(int x_, int y_);
    void Bar() override;
private:
    int y;
};

} // namespace ns
