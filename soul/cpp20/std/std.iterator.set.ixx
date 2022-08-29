export module std.iterator.set;

import std.type.fundamental;

export namespace std {

template<class T>
class set_iterator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    
    set_iterator();
    reference operator*() const;
    pointer operator->() const;
    set_iterator& operator++();
    set_iterator operator++(int);
    set_iterator& operator--();
    set_iterator operator--(int);
};

} // namespace std
