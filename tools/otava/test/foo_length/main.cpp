import std;

class foo
{
public:
    foo() : abc("abc") {}
    std::string str() const { return abc;  }
    int length() const { return str().length(); }
private:
    std::string abc;
};

int main()
{
    foo f;
    int x = f.length();
    std::cout << x << "\n";
}
