export module std.utilities.utility;

import std.type_traits;

export namespace std {

template<class T>
constexpr remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

} // namespace std
