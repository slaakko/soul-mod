export module std.functional;

import std.type.fundamental;

export namespace std {

template<class T>
struct equal_to
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct not_equal_to
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct greater
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct less
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct greater_equal
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct less_equal
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct compare_three_way
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct logical_and
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct logical_or
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct logical_not
{
    constexpr bool operator()(const T& x) const;
};

template<class T>
struct bit_and
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct bit_or
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct bit_xor
{
    constexpr bool operator()(const T& x, const T& y) const;
};

template<class T>
struct bit_not
{
    constexpr bool operator()(const T& x) const;
};

template<class T>
struct identity
{
    constexpr bool operator()(const T& x) const;
};

template<class T>
struct plus
{
    constexpr T operator()(const T& x, const T& y) const;
};

template<class T>
struct minus
{
    constexpr T operator()(const T& x, const T& y) const;
};

template<class T>
struct multiplies
{
    constexpr T operator()(const T& x, const T& y) const;
};

template<class T>
struct divides
{
    constexpr T operator()(const T& x, const T& y) const;
};

template<class T>
struct modulus
{
    constexpr T operator()(const T& x, const T& y) const;
};

template<class T>
struct negate
{
    constexpr T operator()(const T& x) const;
};

} // namespace std
