export module rb_tree;

import std.core;

enum class rb_node_color
{
    red, black
};

class rb_node_base
{
public:
    rb_node_base(rb_node_base* parent_);
    virtual ~rb_node_base();
    rb_node_color get_color() const { return color; }
    void set_color(rb_node_color color_) { color = color_; }
    rb_node_base* get_parent() const { return parent; }
    rb_node_base** parent_ptr() const { return &parent; }
    void set_parent(rb_node_base* parent_) { parent = parent_; }
    rb_node_base* get_left() const { return left; }
    rb_node_base** left_ptr() { return &left; }
    void set_left(rb_node_base* left_) { left = left_; }
    rb_node_base* get_right() const { return right; }
    rb_node_base** right_ptr() { return &right; }
    void set_right(rb_node_base* right_) { right = right_; }
    bool is_header_node() const;
private:
    rb_node_base* parent;
    rb_node_base* left;
    rb_node_base* right;
    rb_node_color color;
};

rb_node_base* min(rb_node_base* n);
rb_node_base* max(rb_node_base* n);
rb_node_base* prev(rb_node_base* n);
rb_node_base* next(rb_node_base* n);
void rotate_left(rb_node_base* n, rb_node_base** root_ptr);
void rotate_right(rb_node_base* n, rb_node_base** root_ptr);
void rebalance_after_insert(rb_node_base* n, rb_node_base** root_ptr);
void rebalance_for_remove(rb_node_base* z, rb_node_base** root_ptr, rb_node_base** leftmost, rb_node_base** rightmost);

template<typename T>
class rb_node : public rb_node_base
{
public:
    using value_type = T;

    rb_node(const value_type& value_, rb_node_base* parent_) : rb_node_base(parent_), val(value_) {}
    const value_type& value() const { return val; }
    value_type& value() { return val; }
private:
    value_type val;
};

template<typename T, typename R, typename P>
class rb_node_iterator
{
public:
    using value_type = T;
    using reference_type = R;
    using pointer_type = P;
    using node_type = rb_node<value_type>;

    rb_node_iterator() : n(nullptr) {}
    rb_node_iterator(node_type* node_) : n(node_) {}
    reference_type operator*() { return n->value(); }
    pointer_type operator->() { return &(n->value()); }
    rb_node_iterator& operator++() { n = static_cast<node_type*>(next(n)); return *this; }
    rb_node_iterator operator++(int) { rb_node_iterator p = *this; n = static_cast<node_type*>(next(n)); return p; }
    rb_node_iterator& operator--() { n = static_cast<node_type*>(prev(n)); return *this; }
    rb_node_iterator operator--(int) { rb_node_iterator p = *this; n = static_cast<node_type*>(prev(n)); return p; }
    node_type* node() const { return n; }
private:
    node_type* n;
};

template<typename T, typename R, typename P>
inline bool operator==(const rb_node_iterator<T, R, P>& left, const rb_node_iterator<T, R, P>& right)
{
    return left.node() == right.node();
}

template<typename KeyType, typename ValueType, typename KeyOfValue, typename Compare>
class rb_tree
{
public:
    using key_type = KeyType;
    using value_type = ValueType;
    using node_type = rb_node<value_type>;
    using size_type = int64_t;
    using key_of_value = KeyOfValue;
    using compare = Compare;
    using const_iterator = rb_node_iterator<value_type, const value_type&, const value_type*>;
    using iterator = rb_node_iterator<value_type, value_type&, value_type*>;

    rb_tree() : header(), count(0), key_of(), comp()
    {
        init();
    }
    ~rb_tree()
    {
        clear();
    }
    void clear()
    {
        if (!header)
        {
            return;
        }
        node_type* r = root();
        if (r)
        {
            delete r;
            set_root(nullptr);
        }
    }
    bool empty() const { return count == 0; }
    size_type size() const { return count; }
    iterator begin()
    {
        if (!header) return end();
        return iterator(leftmost());
    }
    const_iterator begin() const
    {
        if (!header) return cend();
        return const_iterator(leftmost());
    }
    const_iterator cbegin() const
    {
        if (!header) return cend();
        return const_iterator(leftmost());
    }
    iterator end()
    {
        return iterator(header.get());
    }
    const_iterator end() const
    {
        return const_iterator(header.get());
    }
    const_iterator cend() const
    {
        return const_iterator(header.get());
    }
    std::pair<iterator, bool> insert(const value_type& value)
    {
        std::pair<iterator, bool> r;
        if (!header) init();
        node_type* x = root();
        node_type* p = header.get();
        bool c = true;
        while (x)
        {
            p = x;
            c = comp(key_of(value), key_of(x->value()));
/*
            if (c)
            {
                x = static_cast<node_type*>(x->get_left());
            }
            else
            {
                x = static_cast<node_type*>(x->get_right());
            }
*/
        }
/*
        iterator j(p);
        if (c)
        {
            if (j == begin())
            {
                return std::make_pair(insert(x, p, value), true);
            }
            else
            {
                --j;
            }
        }
        if (comp(key_of(j.node()->value()), key_of(value)))
        {
            return std::make_pair(insert(x, p, value), true);
        }
        return std::make_pair(j, false);
*/
        return r;
    }
    iterator insert(node_type* x, node_type* p, const value_type& value)
    {
        iterator i;
        return i;
/*
        if (!header) init();
        node_type* n = new rb_node(value, p);
        if (p == header.get() || x != nullptr || comp(key_of(value), key_of(p->value())))
        {
            p->set_left(n);
            if (p == header.get())
            {
                set_root(n);
                set_rightmost(n);
            }
            else if (p == leftmost())
            {
                set_leftmost(n);
            }
        }
        else
        {
            p->set_right(n);
            if (p == rightmost())
            {
                set_rightmost(n);
            }
        }
        rebalance_after_insert(n, root_ptr());
        ++count;
        return iterator(n);
*/
    }
private:
    void init()
    {
        header.reset(new rb_node<value_type>(value_type(), nullptr));
        header->set_color(rb_node_color::red);
        set_leftmost(header.get());
        set_rightmost(header.get());
    }
    node_type* root() 
    {
        return static_cast<node_type*>(header->get_parent());
    }
    void set_root(node_type* r)
    {
        header->set_parent(r);
    }
    node_type** root_ptr()
    {
        return header->parent_ptr();
    }
    node_type* leftmost()
    {
        return static_cast<node_type*>(header->get_left());
    }
    void set_leftmost(node_type* lm)
    {
        header->set_left(lm);
    }
    node_type* rightmost()
    {
        return static_cast<node_type*>(header->get_right());
    }
    void set_rightmost(node_type* rm)
    {
        header->set_right(rm);
    }
    std::unique_ptr<node_type> header;
    size_type count;
    key_of_value key_of;
    compare comp;
};
