export module bar;

import std;
import foo;

void bar()
{
    int x = 1;
    int y = foo(x);
    double z = 2.0;
    double a = foo(z);
}
