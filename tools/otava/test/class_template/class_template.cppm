export module t;

import std;

template<typename T>
class Foo
{
public:
    T foo(const T& x)
	{
		return x;
	}
};
