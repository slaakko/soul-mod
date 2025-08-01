export module foo;

import std;

template<typename T>
T foo(const T& x)
{
	return x;
}
