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
