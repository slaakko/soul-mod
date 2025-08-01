import std;
import foo;
import bar;
import bazz;

template<class T>
const T& min(const T& x, const T& y)
{
    if (x <= y) return x;
    else return y;
}

int main()
{
    int r = min(1, 2);
    bar();
    bazz();
	return 0;
}
