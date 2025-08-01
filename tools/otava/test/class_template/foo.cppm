export module foo;

import t;

void x()
{
	Foo<int> fi;
	int x = 0;
	x = fi.foo(x);
	
	Foo<double> fd;
	double d = 1.0;
	d = fd.foo(d);
}
