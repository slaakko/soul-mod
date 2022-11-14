export module std.iterator.list;

import std.type.fundamental;

export namespace std {

template<class T>
class list_iterator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    
    list_iterator();
    reference operator*() const;
    pointer operator->() const;
    list_iterator& operator++();
    list_iterator operator++(int);
    list_iterator& operator--();
    list_iterator operator--(int);
};

} // namespace std
