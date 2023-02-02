// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module ort.threading;

void* create_mutex()
{
    return new std::mutex();
}

void destroy_mutex(void* mtx)
{
    std::mutex* m = static_cast<std::mutex*>(mtx);
    delete m;
}

void lock_mutex(void* mtx)
{
    std::mutex* m = static_cast<std::mutex*>(mtx);
    return m->lock();
}

void unlock_mutex(void* mtx)
{
    std::mutex* m = static_cast<std::mutex*>(mtx);
    return m->unlock();
}

bool trylock_mutex(void* mtx)
{
    std::mutex* m = static_cast<std::mutex*>(mtx);
    return m->try_lock();
}

void* create_recursive_mutex()
{
    return new std::recursive_mutex();
}

void destroy_recursive_mutex(void* mtx)
{
    std::recursive_mutex* m = static_cast<std::recursive_mutex*>(mtx);
    delete m;
}

void lock_recursive_mutex(void* mtx) 
{
    std::recursive_mutex* m = static_cast<std::recursive_mutex*>(mtx);
    m->lock();
}

void unlock_recursive_mutex(void* mtx)
{
    std::recursive_mutex* m = static_cast<std::recursive_mutex*>(mtx);
    m->unlock();
}

bool trylock_recursive_mutex(void* mtx)
{
    std::recursive_mutex* m = static_cast<std::recursive_mutex*>(mtx);
    return m->try_lock();
}

void* create_atomic_bool()
{
    return new std::atomic_bool();
}

void destroy_atomic_bool(void* handle)
{
    std::atomic_bool* a = static_cast<std::atomic_bool*>(handle);
    delete a;
}

bool load_atomic_bool(void* handle)
{
    std::atomic_bool* a = static_cast<std::atomic_bool*>(handle);
    return a->load();
}

void store_atomic_bool(void* handle, bool value)
{
    std::atomic_bool* a = static_cast<std::atomic_bool*>(handle);
    a->store(value);
}