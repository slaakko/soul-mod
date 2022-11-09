export module std.type_traits;

import std.type.fundamental;

export namespace std {

template<class T>
struct remove_reference
{
    using type = T;
};

template<class T>
struct remove_reference<T&&>
{
    using type = T;
};

template<class T>
struct remove_reference<T&>
{
    using type = T;
};

template<class T>
using remove_reference_t = typename remove_reference<T>::type;

} // namespace std
