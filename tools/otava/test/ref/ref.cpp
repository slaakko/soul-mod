import std.core;

class foo
{
public:
    foo(int& x_) : x(x_) { x = 1; }
private:
    int& x;
};

int main()
{
    int x = 0;
    foo f(x);
    std::cout << x << "\n";
    return 0;
}