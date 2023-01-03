export module drv;

import std.core;
import cls;

export namespace ns {

class Derived : public Class
{
public:
    Derived();
    Derived(int x_);
    void Bar() override;
};

} // namespace ns
