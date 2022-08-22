export module std.container.map;

import std.type.fundamental;
import std.functional;
import std.iterator.map;
import std.iterator.reverse;
import std.utilities.pair;

export namespace std {

template<class Key, class T, class Compare = less<Key>>
class map
{
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = pair<const Key, T>;
    using key_compare = Compare;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int64_t;
    using difference_type = int64_t;
    using iterator = std::map_iterator<value_type>;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    map();
    template<class InputIterator>
    map(InputIterator first, InputIterator last);
    map(const map& x);
    map(map&& x);
    ~map();
    map& operator=(const map& x);
    map& operator=(map&& x);
    
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
    mapped_type& operator[](const key_type& x);
    mapped_type& operator[](key_type&& x);
    mapped_type& at(const key_type& x);
    const mapped_type& at(const key_type& x) const;
    pair<iterator, bool> insert(const value_type& x);
    pair<iterator, bool> insert(value_type&& x);
    template<class P> 
    pair<iterator, bool> insert(P&& x);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    template<class P>
    iterator insert(const_iterator position, P&&);
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);
    
    iterator erase(iterator position);
    iterator erase(const_iterator position);
    size_type erase(const key_type& x);
    iterator erase(const_iterator first, const_iterator last);
    void swap(map&);
    void clear();
    template<class C2>
    void merge(map<Key, T, C2>& source);
    template<class C2>
    void merge(map<Key, T, C2>&& source);
    key_compare key_comp() const;
    
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
    template<class K> 
    iterator find(const K& x);
    template<class K> 
    const_iterator find(const K& x) const;
    size_type count(const key_type& x) const;
    template<class K> 
    size_type count(const K& x) const;
    bool contains(const key_type& x) const;
    template<class K> 
    bool contains(const K& x) const;
    iterator lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
    template<class K> 
    iterator lower_bound(const K& x);
    template<class K> 
    const_iterator lower_bound(const K& x) const;
    iterator upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
    template<class K> 
    iterator upper_bound(const K& x);
    template<class K> 
    const_iterator upper_bound(const K& x) const;
    pair<iterator, iterator> equal_range(const key_type& x);
    pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
    template<class K>
    pair<iterator, iterator> equal_range(const K& x);
    template<class K>
    pair<const_iterator, const_iterator> equal_range(const K& x) const; 
};

template<class Key, class T, class Compare>
bool operator==(const map<Key, T, Compare>& x, const map<Key, T, Compare>& y);
template<class Key, class T, class Compare>
void swap(map<Key, T, Compare>& x, map<Key, T, Compare>& y);
template<class Key, class T, class Compare, class Predicate>
typename map<Key, T, Compare>::size_type erase_if(map<Key, T, Compare>& c, Predicate pred);

} // namespace std
