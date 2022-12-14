import std.core;

class base
{
public:
    base() {}
};

class foo : public base
{
public:
    foo() {}
private:
    std::string m;
};

int main()
{
    foo f;
}
