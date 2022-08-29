export module std.iterator.unordered_map;

import std.type.fundamental;

export namespace std {

template<class T>
class unordered_map_iterator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    
    unordered_map_iterator();
    reference operator*() const;
    pointer operator->() const;
    unordered_map_iterator& operator++();
    unordered_map_iterator operator++(int);
    unordered_map_iterator& operator--();
    unordered_map_iterator operator--(int);
};

} // namespace std
