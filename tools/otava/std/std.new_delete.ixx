export module std.new_delete_op;

import std.crt;

export void* operator new(size_t size);
export void* operator new(size_t size, void* placement);
export void operator delete(void* object);
