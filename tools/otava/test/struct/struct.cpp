import std.core;

struct Foo
{
    int x;
    int y;
};

int main()
{
    Foo foo;
	foo.x = 1;
	foo.y = 2;
	
	Foo bar = foo;
	
    return 0;
}
