export module std.container.set;

import std.type.fundamental;
import std.functional;
import std.utilities.pair;
import std.container.rb_tree;

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
    using tree_type = std::rb_tree<key_type, value_type, identity<value_type>, key_compare>;
    using iterator = tree_type::iterator;
    using const_iterator = tree_type::const_iterator;
    
    set() : tree() {}
    set(const set& x) : tree(x.tree) {}
    set(set&& x) : tree(std::move(x.tree)) {}
    set& operator=(const set& x) { tree = x.tree; return *this; }
    set& operator=(set&& x) { std::swap(tree, x.tree); return *this; }
    
    iterator begin() { return tree.begin(); }
    const_iterator begin() const { return tree.cbegin(); }
    iterator end() { return tree.end(); }
    const_iterator end() const { return tree.cend(); }
    const_iterator cbegin() const { return tree.cbegin(); }
    const_iterator cend() const { return tree.cend(); }

    bool empty() const { return tree.empty(); }
    size_type size() const { return tree.size(); }
    size_type max_size() const;
    std::pair<iterator, bool> insert(const value_type& x) { return tree.insert(x); }
    //std::pair<iterator, bool> insert(value_type&& x);
    //iterator insert(const_iterator position, const value_type& x);
    //iterator insert(const_iterator position, value_type&& x);
    
    iterator erase(const iterator& position) { tree.erase(position); }
    //iterator erase(const_iterator position);
    //size_type erase(const key_type& x);
    //iterator erase(const_iterator first, const_iterator last);
    void clear() { tree.clear(); }
    
    key_compare key_comp() const { return tree.cmp(); }
    
    iterator find(const key_type& x) { return tree.find(x); }
    const_iterator find(const key_type& x) const { return tree.cfind(x); }
    size_type count(const key_type& x) const;
    bool contains(const key_type& x) const;
    iterator lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
    iterator upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
    pair<iterator, iterator> equal_range(const key_type& x);
    pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
private:
    tree_type tree;
};

template<class Key, class Compare>
bool operator==(const set<Key, Compare>& x, const set<Key, Compare>& y);

} // namespace std
