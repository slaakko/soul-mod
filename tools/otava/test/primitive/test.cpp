module test;

int foo(int x, double y)
{
	return x;
}

double foo(double x, int y)
{
	return x;
}

int main()
{
	foo(1, 1);
}
