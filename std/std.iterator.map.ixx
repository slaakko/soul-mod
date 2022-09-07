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
    reference operator*() const;
    pointer operator->() const;
    map_iterator& operator++();
    map_iterator operator++(int);
    map_iterator& operator--();
    map_iterator operator--(int);
};

} // namespace std
