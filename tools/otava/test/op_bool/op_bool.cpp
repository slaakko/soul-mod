import std;

class foo
{
public:
    foo(bool x_) : x(x_) {}
    operator bool() const { return x; }
private:
    bool x;
};

int main()
{
    foo f0(true);
    if (f0)
    {
        std::cout << "true" << "\n";
    }
    else
    {
        std::cout << "false" << "\n";
    }
    if (!f0)
    {
        std::cout << "false" << "\n";
    }
    else
    {
        std::cout << "true" << "\n";
    }
    foo f1(false);
    if (f1)
    {
        std::cout << "true" << "\n";
    }
    else
    {
        std::cout << "false" << "\n";
    }
    if (!f1)
    {
        std::cout << "false" << "\n";
    }
    else
    {
        std::cout << "true" << "\n";
    }
}
