import std.core;

struct  Foo
{
    Foo() {}
    ~Foo() {}
};

int main()
{
    std::vector<std::unique_ptr<Foo>> vec;
    std::unique_ptr<Foo> foo(new Foo());
    vec.push_back(std::move(foo));
    return 0;
}
