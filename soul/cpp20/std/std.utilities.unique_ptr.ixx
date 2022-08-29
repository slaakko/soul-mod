export module std.utilities.unique_ptr;

import std.type.fundamental;

export namespace std {

template<class T>
class unique_ptr
{
public:
    using pointer = T*;
    using element_type = T;
    unique_ptr();
    explicit unique_ptr(pointer p);
    unique_ptr(unique_ptr&& u);
    unique_ptr(nullptr_t);
    ~unique_ptr();
    unique_ptr& operator=(unique_ptr&& u);
    unique_ptr operator=(nullptr_t);
    T& operator*() const;
    pointer operator->() const;
    pointer get() const;
    explicit operator bool() const;
    pointer release();
    void reset(pointer p = pointer());
    void swap(unique_ptr& u);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
};

} // namespace std
