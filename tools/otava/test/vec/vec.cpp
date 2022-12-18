import std.core;

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
class vec
{
public:
    using size_type = ssize_t;
    using value_type = T;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    vec() : elements(nullptr), sz(0), res(0) {}
    explicit vec(size_type n) : elements(nullptr), sz(n), res(0) 
    {
        reserve(sz);
        for (size_type i = 0; i < sz; ++i)
        {
            new (elements + i) T();
        }
    }
    vec(size_type n, const value_type& value) : elements(nullptr), sz(n), res(0) 
    {
        reserve(sz);
        for (size_type i = 0; i < sz; ++i)
        {
            new (elements + i) T(value);
        }
    }
    iterator begin() { return elements; }
    const_iterator begin() const { return elements; }
    const_iterator cbegin() { return elements; }
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
    size_type capacity() const { return res; }
    void push_back(const value_type& element)
    {
        reserve(sz + 1);
        new (elements + sz) T(element);
        ++sz;
    }
    void push_back(value_type&& element)
    {
        reserve(sz + 1);
        new (elements + sz) T(std::move(element));
        ++sz;
    }
    void reserve(size_type min_res)
    {
        if (min_res > res)
        {
            grow(min_res);
        }
    }
private:
    void grow(size_type min_res)
    {
        min_res = std::grow_size(min_res);
        T* new_elements = static_cast<T*>(malloc(min_res * sizeof(T)));
        if (elements)
        {
            std::constructive_move(new_elements, elements, sz);
            size_type save_sz = sz;
            destroy();
            sz = save_sz;
        }
        elements = new_elements;
        res = min_res;
    }
    void destroy()
    {
        if (sz > 0)
        {
            std::destroy(elements, sz);
            sz = 0;
        }
        if (res > 0)
        {
            free(elements);
            elements = nullptr;
            res = 0;
        }
    }
    T* elements;
    size_type sz;
    size_type res;
};

} // namespace std

int main()
{
    std::vec<int> v;
    v.push_back(1);
    std::string s = std::to_string(v.size());
    prints(s.c_str());
    prints("\n");
    return 0;
}

