import std.core;

class foo_iterator
{
public:
};

class Foo
{
public:
    std::pair<foo_iterator, bool> insert()
    {
        std::pair<foo_iterator, bool> p;
        return p;
    }
};

int main()
{
    Foo foo;
    std::pair<foo_iterator, bool> r = foo.insert();
}