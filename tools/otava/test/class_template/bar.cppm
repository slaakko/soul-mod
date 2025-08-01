export module bar;

import t;

void y()
{
	Foo<int> fi;
	int x = 0;
	x = fi.foo(x);
	
	Foo<double> fd;
	double d = 1.0;
	d = fd.foo(d);
}
