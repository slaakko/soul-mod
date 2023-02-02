import std.core;

class Foo
{
public:
    Foo() : x(10) {}
    void foo() 
    {
        std::string s = std::to_string(x);
        prints(s.c_str(), 1);
        prints("\n", 1);
    }
private:
    int x;
};

class Ptr
{
public:
    Ptr(Foo* f_) : f(f_) {}
    Foo* operator->() const
    {
        return f;
    }
private:
    Foo* f;
};

void direct_call(Foo* f)
{
    f->foo();
}

void indirect_call(Foo* f)
{
    Ptr ptr(f);
    ptr->foo();
}

int main()
{
    Foo* f = new Foo();
    direct_call(f);
    indirect_call(f);
}
