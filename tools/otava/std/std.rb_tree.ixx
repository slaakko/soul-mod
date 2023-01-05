export module std.rb_tree;

import std.type.fundamental;

export namespace std {

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
    rb_node_base* get_left() const { return left; }
    void set_left(rb_node_base* left_) { left = left_; }
    rb_node_base* get_right() const { return right; }
    void set_right(rb_node_base* right_) { right = right_; }
private:
    rb_node_base* parent;
    rb_node_base* left;
    rb_node_base* right;
    rb_node_color color;
};

} // namespace std
