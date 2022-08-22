export module std.container.vector;

import std.type.fundamental;
import std.iterator.reverse;

export namespace std {

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
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    vector();
    explicit vector(size_type n);
    vector(size_type n, const T& value);
    template<class InputIterator>
    vector(InputIterator first, InputIterator last);
    vector(const vector& x);
    vector(vector&& x);
    ~vector();
    vector& operator=(const vector& x);
    vector& operator=(vector&& x);
    template<class InputIterator>
    void assign(InputIterator first, InputIterator last);
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
    size_type capacity() const;
    void resize(size_type sz);
    void resize(size_type sz, const T& c);
    void reserve(size_type n);
    void shrink_to_fit();
    
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data();
    const T* data() const;

    void push_back(const T& x);
    void push_back(T&& x);
    void pop_back();

    iterator insert(const_iterator position, const T& x);
    iterator insert(const_iterator position, T&& x);
    iterator insert(const_iterator position, size_type n, const T& x);
    template<class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);
    void swap(vector& x);
    void clear();
};

template<class T>
bool operator==(const vector<T>& x, const vector<T>& y);
template<class T>
void swap(vector<T>& x, vector<T>& y);

} // namespace std
