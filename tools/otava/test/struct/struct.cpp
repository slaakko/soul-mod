import std.core;

struct Foo
{
    int x;
    int y;
};

void f()
{
	std::str s;
}

int main()
{
    Foo foo;
	foo.x = 1;
	foo.y = 2;
	
	Foo bar = foo;
	f();
	
    return 0;
}
