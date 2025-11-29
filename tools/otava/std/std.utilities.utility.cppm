export module std.utilities.utility;

import std.type_traits;
import std.trace;

export namespace std {

template<typename T>
constexpr remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

constexpr ssize_t align(ssize_t n, ssize_t alignment)
{
    return (n + alignment - 1) & -alignment;
}

template<typename T>
ssize_t slen(const T* s)
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

template<typename T>
void scpy(T* buf, const T* from)
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

template<typename T>
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

ssize_t grow_size(ssize_t size);

} // namespace std
