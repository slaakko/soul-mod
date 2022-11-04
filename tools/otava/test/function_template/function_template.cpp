import std.core;

template<class T>
const T& min(const T& x, const T& y)
{
    if (x <= y) return x;
    else return y;
}

int main()
{
    int r = min(1, 2);
	return 0;
}
