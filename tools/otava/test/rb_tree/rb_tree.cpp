module rb_tree;

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

bool rb_node_base::is_header_node() const
{
    return color == rb_node_color::red && parent && parent->get_parent() == this;
}

rb_node_base* min(rb_node_base* n)
{
    rb_node_base* left = n->get_left();
    while (left)
    {
        n = left;
        left = n->get_left();
    }
    return n;
}

rb_node_base* max(rb_node_base* n)
{
    rb_node_base* right = n->get_right();
    while (right)
    {
        n = right;
        right = n->get_right();
    }
    return n;
}

rb_node_base* prev(rb_node_base* n)
{
    if (n->is_header_node())
    {
        return n->get_right();
    }
    else
    {
        rb_node_base* left = n->get_left();
        if (left)
        {
            return max(left);
        }
        else
        {
            rb_node_base* u = n->get_parent();
            rb_node_base* left = u->get_left();
            while (n == left)
            {
                n = u;
                u = u->get_parent();
                left = u->get_left();
            }
            return u;
        }
    }
}

rb_node_base* next(rb_node_base* n)
{
    rb_node_base* right = n->get_right();
    if (right)
    {
        return min(right);
    }
    else
    {
        rb_node_base* u = n->get_parent();
        rb_node_base* right = u->get_right();
        while (n == right)
        {
            n = u;
            u = u->get_parent();
            right = u->get_right();
        }
        if (n->get_right() != u)
        {
            return u;
        }
        return n;
    }
}

void rotate_left(rb_node_base* n, rb_node_base** root_ptr)
{
    rb_node_base* u = n->get_right();
    rb_node_base* left = u->get_left();
    n->set_right(left);
    if (left)
    {
        left->set_parent(n);
    }
    rb_node_base* parent = n->get_parent();
    u->set_parent(parent);
    if (n == *root_ptr)
    {
        *root_ptr = u;
    }
    else
    {
        if (n == parent->get_left())
        {
            parent->set_left(u);
        }
        else
        {
            parent->set_right(u);
        }
    }
    u->set_left(n);
    n->set_parent(u);
}

void rotate_right(rb_node_base* n, rb_node_base** root_ptr)
{
    rb_node_base* u = n->get_left();
    rb_node_base* right = u->get_right();
    u->set_left(right);
    if (right)
    {
        right->set_parent(n);
    }
    rb_node_base* parent = n->get_parent();
    u->set_parent(parent);
    if (n == *root_ptr)
    {
        *root_ptr = u;
    }
    else
    {
        if (n == parent->get_right())
        {
            parent->set_right(u);
        }
        else
        {
            parent->set_left(u);
        }
    }
    u->set_right(n);
    n->set_parent(u);
}

void rebalance_after_insert(rb_node_base* n, rb_node_base** root_ptr)
{
    n->set_color(rb_node_color::red);
    while (n != *root_ptr && n->get_parent()->get_color() == rb_node_color::red)
    {
        if (n->get_parent() == n->get_parent()->get_parent()->get_left())
        {
            rb_node_base* u = n->get_parent()->get_parent()->get_right();
            if (u && u->get_color() == rb_node_color::red)
            {
                n->get_parent()->set_color(rb_node_color::black);
                u->set_color(rb_node_color::black);
                n->get_parent()->get_parent()->set_color(rb_node_color::red);
                n = n->get_parent()->get_parent();
            }
            else
            {
                if (n == n->get_parent()->get_right())
                {
                    n = n->get_parent();
                    rotate_left(n, root_ptr);
                }
                n->get_parent()->set_color(rb_node_color::black);
                n->get_parent()->get_parent()->set_color(rb_node_color::red);
                rotate_right(n->get_parent()->get_parent(), root_ptr);
            }
        }
        else
        {
            rb_node_base* u = n->get_parent()->get_parent()->get_left();
            if (u && u->get_color() == rb_node_color::red)
            {
                n->get_parent()->set_color(rb_node_color::black);
                u->set_color(rb_node_color::black);
                n->get_parent()->get_parent()->set_color(rb_node_color::red);
                n = n->get_parent()->get_parent();
            }
            else
            {
                if (n == n->get_parent()->get_left())
                {
                    n = n->get_parent();
                    rotate_right(n, root_ptr);
                }
                n->get_parent()->set_color(rb_node_color::black);
                n->get_parent()->get_parent()->set_color(rb_node_color::red);
                rotate_left(n->get_parent()->get_parent(), root_ptr);
            }
        }
    }
    rb_node_base* root = *root_ptr;
    root->set_color(rb_node_color::black);
}

void rebalance_for_remove(rb_node_base* z, rb_node_base** root_ptr, rb_node_base** leftmost, rb_node_base** rightmost)
{

}
