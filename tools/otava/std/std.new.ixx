export module std.new_op;

import std.type.fundamental;

void* operator new(size_t size);
void* operator new(size_t size, void* placement);
