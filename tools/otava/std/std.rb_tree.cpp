module std.rb_tree;

namespace std {

rb_node_base::rb_node_base(rb_node_base* parent_) : parent(parent_), left(nullptr), right(nullptr), color(rb_node_color::black)
{
}

rb_node_base::~rb_node_base()
{
    if (left && left != this)
    {
        delete left;
    }
    if (right && right != this)
    {
        delete right;
    }
}

} // namespace std
