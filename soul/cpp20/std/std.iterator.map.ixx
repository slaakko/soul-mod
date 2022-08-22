export module std.iterator.map;

import std.type.fundamental;

export namespace std {

template<class T>
class map_iterator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    
    map_iterator();
    template<class U>
    map_iterator& operator=(const map_iterator<U>& u);
    reference operator*() const;
    pointer operator->() const;
    map_iterator& operator++();
    map_iterator operator++(int);
    map_iterator& operator--();
    map_iterator operator--(int);
};

} // namespace std
