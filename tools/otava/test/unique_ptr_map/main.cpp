import std;

class Foo
{
public:
    Foo() : s("foo") {}
private:
    std::string s;
};

int main()
{
    std::map<std::string, std::unique_ptr<Foo>> m;
    for (int i = 0; i < 100; ++i)
    {
        if ((i % 2) == 0)
        {
            m[std::to_string(i)] = std::unique_ptr<Foo>(new Foo());
        }
        else
        {
            m[std::to_string(i)] = std::unique_ptr<Foo>(); 
        }
    }
}
