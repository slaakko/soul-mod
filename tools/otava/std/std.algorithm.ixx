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

template<typename I, typename T>
I find(I begin, I end, const T& value)
{
    while (begin != end)
    {
        if (*begin == value)
        {
            return begin;
        }
        ++begin;
    }
    return end;
}

template<typename I, typename P>
I find_if(I begin, I end, P p)
{
    while (begin != end)
    {
        if (p(*begin))
        {
            return begin;
        }
        ++begin;
    }
}

template<typename I, typename O, typename T>
O remove_copy(I begin, I end, O result, const T& value)
{
    while (begin != end)
    {
        if (*begin == value)
        {
            *result = *begin;
            ++result;
        }
        ++begin;
    }
    return result;
}

template<typename I, typename T>
I remove(I begin, I end, const T& value)
{
    begin = find(begin, end, value);
    if (begin == end)
    {
        return begin;
    }
    else
    {
        I i = begin;
        ++i;
        return remove_copy(i, end, begin, value);
    }
}

} // std
