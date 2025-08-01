export module bazz;

import std;
import foo;

void bazz()
{
    int x = 1;
    int y = foo(x);
    double z = 2.0;
    double a = foo(z);
}
