import std;

class Foo
{
public:
    Foo() : abc("abc") {}
    const std::string& Str() const { return abc; }
private:
    std::string abc;
};

int main()
{
    std::unique_ptr<Foo> foo(new Foo());
    const std::string& str = foo->Str();
    std::cout << str << "\n";
}
