import std.core;

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

template<class T>
constexpr remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

} // namespace std
