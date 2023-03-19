export module std.container.vector;

import std.type.fundamental;
import std.utilities.utility;
import std.type_traits;
import std.crt;
import std.algorithm;
import std.new_delete_op;

export namespace std {

template<typename T>
void constructive_copy(T* to, T* from, ssize_t count)
{
    for (ssize_t i = 0; i < count; ++i)
    {
        new (to) T(*from);
        ++to;
        ++from;
    }
}

template<typename T>
void constructive_move(T* to, T* from, ssize_t count)
{
    for (ssize_t i = 0; i < count; ++i)
    {
        new (to) T(std::move(*from));
        ++to;
        ++from;
    }
}

template<typename T>
void destroy(T* elements, ssize_t count)
{
    for (ssize_t i = 0; i < count; ++i)
    {
        elements->T::~T();
        ++elements;
    }
}

template<typename T>
class vector
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int64_t;
    using difference_type = int64_t;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    vector() : elements(nullptr), sz(0), res(0) {}
    explicit vector(size_type n) : elements(nullptr), sz(n), res(0)
    {
        reserve(sz);
        for (size_type i = 0; i < sz; ++i)
        {
            new (elements + i) T();
        }
    }
    vector(size_type n, const value_type& value) : elements(nullptr), sz(n), res(0)
    {
        reserve(sz);
        for (size_type i = 0; i < sz; ++i)
        {
            new (elements + i) T(value);
        }
    }
    vector(const vector& that) : elements(nullptr), sz(that.sz), res(0)
    {
        if (sz > 0)
        {
            reserve(sz);
            constructive_copy(elements, that.elements, sz);
        }
    }
    vector(vector&& that) : elements(that.elements), sz(that.sz), res(that.res)
    {
        that.elements = static_cast<T*>(nullptr);
        that.sz = 0;
        that.res = 0;
    }
    ~vector()
    {
        destroy();
    }
    vector& operator=(const vector& that)
    {
        destroy();
        sz = that.sz;
        reserve(sz);
        constructive_copy(elements, that.elements, sz);
        return *this;
    }
    vector& operator=(vector&& that)
    {
        std::swap(elements, that.elements);
        std::swap(sz, that.sz);
        std::swap(res, that.res);
        return *this;
    }
    void assign(size_type n, const T& value);
    
    iterator begin() { return elements; }
    const_iterator begin() const { return elements; }
    iterator end()
    {
        if (elements)
        {
            return elements + sz;
        }
        else
        {
            return nullptr;
        }
    }
    const_iterator end() const
    {
        if (elements)
        {
            return elements + sz;
        }
        else
        {
            return nullptr;
        }
    }
    const_iterator cbegin() const { return elements; }
    const_iterator cend() const
    {
        if (elements)
        {
            return elements + sz;
        }
        else
        {
            return nullptr;
        }
    }

    bool empty() const { return sz == 0; }
    size_type size() const { return sz; }
    size_type max_size() const;
    size_type capacity() const { return res; }
    void resize(size_type new_sz)
    {
        if (new_sz != sz)
        {
            if (new_sz < sz)
            {
                for (size_type i = new_sz; i < sz; ++i)
                {
                    T* p = elements + i;
                    p->T::~T();
                }
            }
            else if (new_sz > sz)
            {
                reserve(new_sz);
                for (size_type i = sz; i < new_sz; ++i)
                {
                    new (elements + i) T();
                }
            }
            sz = new_sz;
        }
    }
    void resize(size_type new_sz, const T& c)
    {
        if (new_sz != sz)
        {
            if (new_sz < sz)
            {
                for (size_type i = new_sz; i < sz; ++i)
                {
                    T* p = elements + i;
                    p->T::~T();
                }
            }
            else if (new_sz > sz)
            {
                reserve(new_sz);
                for (size_type i = sz; i < new_sz; ++i)
                {
                    new (elements + i) T(c);
                }
            }
            sz = new_sz;
        }
    }
    void reserve(size_type n)
    {
        if (n > res)
        {
            grow(n);
        }
    }
    void shrink_to_fit();
    
    reference operator[](size_type n)
    {
        return elements[n];
    }
    const_reference operator[](size_type n) const
    {
        return elements[n];
    }
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front()
    {
        return elements[0];
    }
    const_reference front() const
    {
        return elements[0];
    }
    reference back()
    {
        return elements[sz - 1];
    }
    const_reference back() const
    {
        return elements[sz - 1];
    }
    pointer data() { return elements; }
    const_pointer data() const { return elements; }

    void push_back(const T& x)
    {
        reserve(sz + 1);
        new (elements + sz) T(x);
        ++sz;
    }
    void push_back(T&& x)
    {
        reserve(sz + 1);
        new (elements + sz) T(std::move(x));
        ++sz;
    }
    void pop_back()
    {
        --sz;
        elements[sz]->T::~T();
    }

    iterator insert(const_iterator position, const T& x)
    {
        reserve(sz + 1);
        constructive_move(end(), end() - 1, end() - position);
        new (position) T(x);
        ++sz;
    }
    iterator insert(const_iterator position, T&& x)
    {
        reserve(sz + 1);
        constructive_move(end(), end() - 1, end() - position);
        new (position) T(std::move(x));
        ++sz;
    }
    iterator insert(const_iterator position, size_type n, const T& x);
    iterator erase(const_iterator position)
    {
        erase(position, position + 1);
    }
    iterator erase(iterator first, iterator last)
    {
        size_type n = last - first;
        for (iterator i = first; i != last; ++i)
        { 
            i->T::~T();
        }
        size_type m = end() - last;
        constructive_move(first, last, m);
        sz -= n;
    }
    void clear()
    {
        destroy();
    }
private:
    void destroy()
    {
        if (sz > 0)
        {
            destroy(elements, sz);
            sz = 0;
        }
        if (res > 0)
        {
            free(elements);
            elements = static_cast<T*>(nullptr);
            res = 0;
        }
    }
    void grow(size_type min_res)
    {
        min_res = std::grow_size(min_res);
        value_type* new_elements = static_cast<value_type*>(malloc(min_res * sizeof(value_type)));
        if (elements)
        {
            constructive_move(new_elements, elements, sz);
            size_type save_sz = sz;
            destroy();
            sz = save_sz;
        }
        elements = new_elements;
        res = min_res;
    }
    T* elements;
    size_type sz;
    size_type res;
};

template<class T>
bool operator==(const vector<T>& x, const vector<T>& y)
{
    if (x.size() != y.size()) return false;
    typename vector<T>::size_type n = x.size();
    for (typename vector<T>::size_type i = 0; i < n; ++i)
    {
        if (x[i] != y[i]) return false;
    }
    return true;
}

} // namespace std
