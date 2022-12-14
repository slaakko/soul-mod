module std.new_op;

import std.crt;

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new(size_t size, void* placement)
{
    return placement;
}
