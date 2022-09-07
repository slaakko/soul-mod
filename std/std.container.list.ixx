export module std.container.list;

import std.type.fundamental;
import std.iterator.list;
import std.iterator.reverse;

export namespace std {

template<typename T>
class list
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int64_t;
    using iterator = std::list_iterator<value_type>;
    using const_iterator = std::list_iterator<const value_type&>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    list();
    explicit list(size_type n);
    list(size_type n, const T& value);
    list(const list& x);
    list(list&& x);
    list& operator=(const list& x);
    list& operator=(list&& x);
    void assign(size_type n, const T& value);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void resize(size_type sz);
    void resize(size_type sz, const T& c);

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    void push_back(const T& x);
    void push_back(T&& x);
    void pop_back();

    iterator insert(const_iterator position, const T& x);
    iterator insert(const_iterator position, T&& x);
    iterator insert(const_iterator position, size_type n, const T& x);
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);
    void swap(list& x);
    void clear();
    
    void splice(const_iterator position, list& x);
    void splice(const_iterator position, list&& x);
    void splice(const_iterator position, list& x, const_iterator i);
    void splice(const_iterator position, list&& x, const_iterator i);
    void splice(const_iterator position, list& x, const_iterator first, const_iterator last);
    void splice(const_iterator position, list&& x, const_iterator first, const_iterator last);
    
    size_type remove(const T& value);
    size_type unique();
    
    void merge(list& x);
    void merge(list&& x);
    
    void sort();
    void reverse();
};

template<class T>
bool operator==(const list<T>& x, const list<T>& y);
template<class T>
void swap(list<T>& x, list<T>& y);

} // namespace std
