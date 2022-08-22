export module std.container.set;

import std.type.fundamental;
import std.functional;
import std.iterator.set;
import std.iterator.reverse;

export namespace std {

template<class Key, class Compare = less<Key>>
class set
{
public:
    using key_type = Key;
    using key_compare = Compare;
    using value_type = Key;
    using value_compare = Compare;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int64_t;
    using difference_type = int64_t;
    using iterator = std::set_iterator<value_type>;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    explicit set(const Compare& comp);
    template<class InputIterator>
    set(InputIterator first, InputIterator last, const Compare& comp = Compare());
    set(const set& x);
    set(set&& x);
    ~set();
    set& operator=(const set& x);
    set& operator=(set&& x);
    
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
    pair<iterator,bool> insert(const value_type& x);
    pair<iterator,bool> insert(value_type&& x);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);
    
    iterator erase(iterator position);
    iterator erase(const_iterator position);
    size_type erase(const key_type& x);
    iterator erase(const_iterator first, const_iterator last);
    void swap(set&);
    void clear();
    
    template<class C2>
    void merge(set<Key, C2>& source);
    template<class C2>
    void merge(set<Key, C2>&& source);
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

template<class Key, class Compare>
bool operator==(const set<Key, Compare>& x, const set<Key, Compare>& y);
template<class Key, class Compare>
void swap(set<Key, Compare>& x, set<Key, Compare>& y);
template<class Key, class Compare, class Predicate>
typename set<Key, Compare>::size_type erase_if(set<Key, Compare>& c, Predicate pred);

} // namespace std
