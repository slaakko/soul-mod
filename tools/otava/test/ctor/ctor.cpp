import std.core;

class foo
{
public:
	foo();
private:
	int x;
};

foo::foo() : x(0)
{
}

int main()
{
	foo f;
	return 0;
}
