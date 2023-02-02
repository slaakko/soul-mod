module std.thread.mutex;

import std.crt;

namespace std {

mutex::mutex() : handle(create_mutex())
{
}

mutex::~mutex()
{
    destroy_mutex(handle);
}

void mutex::lock()
{
    lock_mutex(handle);
}

bool mutex::try_lock()
{
    return trylock_mutex(handle);
}

void mutex::unlock()
{
    unlock_mutex(handle);
}

recursive_mutex::recursive_mutex() : handle(create_recursive_mutex())
{
}

recursive_mutex::~recursive_mutex()
{
    destroy_recursive_mutex(handle);
}

void recursive_mutex::lock()
{
    lock_recursive_mutex(handle);
}

bool recursive_mutex::try_lock()
{
    return trylock_recursive_mutex(handle);
}

void recursive_mutex::unlock()
{
    unlock_recursive_mutex(handle);
}

} // namespace std
