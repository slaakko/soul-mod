export module std.utilities.unique_ptr;

import std.type.fundamental;

export namespace std {

template<class T>
class unique_ptr
{
public:
    using pointer = T*;
    using element_type = T;

    unique_ptr() : ptr(nullptr) {}
    explicit unique_ptr(pointer p) : ptr(p) {}
    unique_ptr(unique_ptr&& u) : ptr(u.ptr) { u.ptr = nullptr; }
    unique_ptr(nullptr_t) : ptr(nullptr) {}
    ~unique_ptr() { if (ptr) delete ptr; }
    unique_ptr& operator=(unique_ptr&& u) { std::swap(ptr, u.ptr); }
    unique_ptr operator=(nullptr_t) { if (ptr) delete ptr; ptr = nullptr; }
    T& operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }
    pointer get() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }
    pointer release() { pointer p = ptr; ptr = nullptr; return p; }
    void reset(pointer p) { if (ptr) delete ptr; ptr = p; }
    void reset() { if (ptr) delete ptr; ptr = nullptr; }
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
private:
    pointer ptr;
};

} // namespace std
