export module std.algorithm;

import std.utilities.utility;

export namespace std {

template<typename T>
const T& min(const T& left, const T& right)
{
    if (left <= right) return left;
    else return right;
}

template<typename T>
const T& max(const T& left, const T& right)
{
    if (left >= right) return left;
    else return right;
}

template<typename T>
void swap(T& left, T& right)
{
    T temp(move(left));
    left = move(right);
    right = move(temp);
}

// reverse for random access iterators:

template<typename I> 
void reverse(I begin, I end)
{
    while (begin < end)
    {
        --end;
        swap(*begin, *end);
        ++begin;
    }
}

} // std
