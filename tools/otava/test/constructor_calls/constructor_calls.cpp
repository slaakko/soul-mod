import std.core;

class base
{
public:
    base(int x_);
private:
    int xyzzy;
};

base::base(int x_) : xyzzy(x_)
{
}

class derived : public base
{
public:
    derived(int x_);
    derived();
};

derived::derived(int x_) : base(x_)
{
}

derived::derived() : derived(1)
{
}

int main()
{
    return 0;
}
