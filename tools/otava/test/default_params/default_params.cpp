import std;

void bar()
{
	std::cout << "bar" << "\n";
}

template<typename T>
class Foo
{
public:
    void foo(T x, int y = 0, int z = 1)
    {
		bar();
    }
};

int main()
{
	Foo<int> f;
	f.foo(1);
}
