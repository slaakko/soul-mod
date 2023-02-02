module std.atomic;

import std.crt;

namespace std {

atomic_bool::atomic_bool() : handle(create_atomic_bool())
{
}

atomic_bool::~atomic_bool()
{
    destroy_atomic_bool(handle);
}

atomic_bool::operator bool()
{
    return load_atomic_bool(handle);
}

atomic_bool& atomic_bool::operator=(bool value)
{
    store_atomic_bool(handle, value);
    return *this;
}

} // namespace std
