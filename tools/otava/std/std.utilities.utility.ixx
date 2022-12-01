export module std.utilities.utility;

import std.type_traits;

export namespace std {

template<class T>
constexpr remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

constexpr ssize_t align(ssize_t n, ssize_t alignment)
{
    return (n + alignment - 1) & -alignment;
}

template<class T>
constexpr ssize_t slen(const T* s)
{
    ssize_t len = 0;
    if (s)
    {
        while (*s)
        {
            ++len;
            ++s;
        }
    }
    return len;
}

template<class T>
constexpr void scpy(T* buf, const T* from)
{
    if (from)
    {
        while (*from)
        {
            *buf++ = *from++;
        }
    }
    *buf = T();
}

template<class T>
ssize_t slencpy(T* buf, const T* from, ssize_t length)
{
    ssize_t resultLen = 0;
    if (from)
    {
        while (resultLen < length)
        {
            if (!*from) break;
            *buf++ = *from++;
            ++resultLen;
        }
    }
    *buf = T();
    return resultLen;
}

ssize_t grow_size(ssize_t size)
{
    if (size < 8) return 8;
    if (size < 64) return 64;
    if (size < 512) return 512;
    if (size < 4096) return 4096;
    return 2 * align(size, 4096);
}

} // namespace std
