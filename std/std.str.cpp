module std.str;

import std.crt;

namespace std {

str::str()
{
    mem = malloc(16ull);
}

str::~str()
{
    free(mem);
}
	
} // namespace std
