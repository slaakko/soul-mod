export module std.utilities.unique_ptr;

import std.type.fundamental;
import std.basic_string;

export namespace std {

template<class T>
class unique_ptr
{
public:
    using pointer = T*;
    using element_type = T;

    inline unique_ptr() : ptr(nullptr) {}
    inline explicit unique_ptr(pointer p) : ptr(p) {}
    inline unique_ptr(unique_ptr&& u) : ptr(u.ptr) { u.ptr = nullptr; }
    inline unique_ptr(nullptr_t) : ptr(nullptr) {}
    ~unique_ptr() { if (ptr) delete ptr; }
    inline unique_ptr& operator=(unique_ptr&& u) { std::swap(ptr, u.ptr); return *this; }
    inline unique_ptr& operator=(nullptr_t) { if (ptr) delete ptr; ptr = nullptr; return *this; }
    inline T& operator*() const { return *ptr; }
    inline pointer operator->() const { return ptr; }
    inline pointer get() const { return ptr; }
    inline explicit operator bool() const { return ptr != nullptr; }
    inline pointer release() { pointer p = ptr; ptr = nullptr; return p; }
    inline void reset(pointer p) { if (ptr) delete ptr; ptr = p; }
    inline void reset() { if (ptr) delete ptr; ptr = nullptr; }
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
private:
    pointer ptr;
};

} // namespace std
