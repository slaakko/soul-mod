export module std.algorithm;

import std.utilities.utility;

export namespace std {

template<class T>
const T& min(const T& left, const T& right)
{
    if (left <= right) return left;
    else return right;
}

template<class T>
const T& max(const T& left, const T& right)
{
    if (left >= right) return left;
    else return right;
}

template<class T>
void swap(T& left, T& right)
{
    T temp(move(left));
    left = move(right);
    right = move(temp);
}

} // std
