import std.core;

class foo
{
public:
	foo(int xyzzy_) : xyzzy(xyzzy_) {}
private:
	int xyzzy;
};

int main()
{
	foo f(1);
	return 0;
}
