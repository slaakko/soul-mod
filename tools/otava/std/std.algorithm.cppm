export module std.algorithm;

import std.utilities.utility;
import std.type_traits;
import std.utilities.pair;

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

template<typename T, typename R>
inline const T& select_0_2(const T& a, const T& b, R r)
{
    if (r(b, a)) return b;
    return a;
}

template<typename T, typename R>
inline const T& select_1_2(const T& a, const T& b, R r)
{
    if (r(b, a)) return a;
    return b;
}

template<typename T, typename R>
inline const T& select_0_3(const T& a, const T& b, const T& c, R r)
{
    return select_0_2(select_0_2(a, b, r), c, r);
}

template<typename T, typename R>
inline const T& select_2_3(const T& a, const T& b, const T& c, R r)
{
    return select_1_2(select_1_2(a, b, r), c, r);
}

template<typename T, typename R>
inline const T& select_1_3_ab(const T& a, const T& b, const T& c, R r)
{
    if (!r(c, b)) return b;
    return select_1_2(a, c, r);
}

template<typename T, typename R>
inline const T& select_1_3(const T& a, const T& b, const T& c, R r)
{
    if (r(b, a)) return select_1_3_ab(b, a, c, r);
    return select_1_3_ab(a, b, c, r);
}

template<typename T, typename R>
inline const T& median(const T& a, const T& b, const T& c, R r)
{
    return select_1_3(a, b, c, r);
}

template<typename T>
inline const T& median(const T& a, const T& b, const T& c)
{
    return median(a, b, c, less<T>());
}

template<typename I, typename T, typename R>
I unguarded_partition(I begin, I end, const T& pivot, R r)
{
    while (true)
    {
        while (r(*begin, pivot))
        {
            ++begin;
        }
        --end;
        while (r(pivot, *end))
        {
            --end;
        }
        if (begin >= end)
        {
            return begin;
        }
        swap(*begin, *end);
        ++begin;
    }
}

template<typename I, typename T, typename R>
void unguarded_linear_insert(I last, const T& val, R r)
{
    I next = last;
    --next;
    while (r(val, *next))
    {
        *last = *next;
        last = next;
        --next;
    }
    *last = val;
}

template<typename I, typename T, typename R>
void unguarded_linear_insert(I last, T&& val, R r)
{
    I next = last;
    --next;
    while (r(val, *next))
    {
        *last = std::move(*next);
        last = next;
        --next;
    }
    *last = std::move(val);
}

template<typename I, typename O>
O copy_backward(I begin, I end, O to)
{
    while (begin != end)
    {
        --to;
        --end;
        *to = *end;
    }
    return to;
}

template<typename I, typename R>
void linear_insert(I first, I last, R r)
{
    iter_value_t<I> val = *last;
    if (r(val, *first))
    {
        copy_backward(first, last, last + 1);
        *first = val;
    }
    else
    {
        unguarded_linear_insert(last, val, r);
    }
}

template<typename I, typename R>
void insertion_sort(I begin, I end, R r)
{
    if (begin == end)
    {
        return;
    }
    for (I i = begin + 1; i != end; ++i)
    {
        linear_insert(begin, i, r);
    }
}

template<typename I>
void insertion_sort(I begin, I end)
{
    insertion_sort(begin, end, less<iter_value_t<I>>());
}

const int64_t insertion_sort_threshold = 16;

template<typename I, typename R>
void partial_quick_sort(I begin, I end, R r)
{
    while (end - begin > insertion_sort_threshold)
    {
        iter_value_t<I> pivot = median(*begin, *(begin + (end - begin) / 2), *(end - 1), r);
        I cut = unguarded_partition(begin, end, pivot, r);
        partial_quick_sort(cut, end, r);
        end = cut;
    }
}

template<typename I, typename R>
void sort(I begin, I end, R r)
{
    if (begin != end)
    {
        partial_quick_sort(begin, end, r);
        insertion_sort(begin, end, r);
    }
}

template<typename I>
void sort(I begin, I end)
{
    sort(begin, end, less<iter_value_t<I>>());
}

template<typename I, typename R>
I adjacent_find(I begin, I end, R r)
{
    if (begin != end)
    {
        I i = begin;
        ++i;
        while (i != end)
        {
            if (r(*begin, *i))
            {
                return begin;
            }
            begin = i;
            ++i;
        }
    }
    return end;
}

template<typename I>
I adjacent_find(I begin, I end)
{
    return adjacent_find(begin, end, equal_to<iter_value_t<I>>());
}

template<typename I, typename R>
I unique(I begin, I end, R r)
{
    begin = adjacent_find(begin, end, r);
    if (begin != end)
    {
        I i = begin;
        ++i;
        ++i;
        while (i != end)
        {
            if (!r(*begin, *i))
            {
                *++begin = std::move(*i);
            }
            ++i;
        }
        ++begin;
    }
    return begin;
}

template<typename I>
I unique(I begin, I end)
{
    return unique(begin, end, equal_to<iter_value_t<I>>());
}

template<typename I>
ssize_t distance(I first, I last)
{
    return last - first;
}

template<typename I>
I iter_next(I i, ssize_t n)
{
    return i + n;
}

template<typename I, typename T>
I lower_bound(I first, I last, const T& value)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (value > *middle)
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
        else
        {
            len = half;
        }
    }
    return first;
}

template<typename I, typename T, typename R>
I lower_bound(I first, I last, const T& value, R r)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (r(*middle, value))
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
        else
        {
            len = half;
        }
    }
    return first;
}

template<typename I, typename T>
I upper_bound(I first, I last, const T& value)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (value < *middle)
        {
            len = half;
        }
        else
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
    }
    return first;
}

template<typename I, typename T, typename R>
I upper_bound(I first, I last, const T& value, R r)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (r(value, *middle))
        {
            len = half;
        }
        else
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
    }
    return first;
}

template<typename I, typename T>
pair<I, I> equal_range(I first, I last, const T& value)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (*middle < value)
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
        else if (value < *middle)
        {
            len = half;
        }
        else
        {
            I left = lower_bound(first, middle, value);
            I end = iter_next(first, len);
            ++middle;
            I right = upper_bound(middle, end, value);
            return pair<I, I>(left, right);
        }
    }
    return pair<I, I>(first, first);
}

template<typename I, typename T, typename R>
pair<I, I> equal_range(I first, I last, const T& value, R r)
{
    ssize_t len = distance(first, last);
    while (len > 0)
    {
        ssize_t half = len >> 1;
        I middle = iter_next(first, half);
        if (r(*middle, value))
        {
            first = middle;
            ++first;
            len -= half - 1;
        }
        else if (r(value, *middle))
        {
            len = half;
        }
        else
        {
            I left = lower_bound(first, middle, value, r);
            I end = iter_next(first, len);
            ++middle;
            I right = upper_bound(middle, end, value, r);
            return pair<I, I>(left, right);
        }
    }
    return pair<I, I>(first, first);
}

} // std
