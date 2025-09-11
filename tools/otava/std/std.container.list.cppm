export module std.container.list;

import std.type.fundamental;
import std.iterator;

export namespace std {

template<typename T>
class list_node
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = T*;
    using reference = value_type&;
    using const_reference = const value_type&;

    list_node(const value_type& val_) : val(val_), nxt(nullptr), prv(nullptr) {}
    list_node(value_type&& val_) : val(std::move(val_)), nxt(nullptr), prv(nullptr) {}
    reference value() { return val; }
    const_reference value() const { return val; }
    pointer value_ptr() { return &val; }
    const_pointer value_ptr() const { return &val; }
    list_node<T>* get_next() { return nxt; }
    void set_next(list_node<T>* nxt_) { nxt = nxt_; }
    list_node<T>* get_prev() { return prv; }
    void set_prev(list_node<T>* prv_) { prv = prv_; }
private:
    value_type val;
    list_node<T>* nxt;
    list_node<T>* prv;
};

template<typename NodeT>
class list_iterator
{
public:
    using node_type = NodeT;
    using value_type = typename NodeT::value_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator_category = bidirectional_iterator_tag;

    list_iterator() : n(nullptr) {}
    list_iterator(node_type* n_) : n(n_) {}
    reference operator*() { return n->value(); }
    const_reference operator*() const { return n->value(); }
    pointer operator->() { return n->value_ptr(); }
    const_pointer operator->() const { return n->value_ptr(); }
    list_iterator& operator++() { n = n->get_next(); return *this; }
    list_iterator operator++(int) { list_iterator p = *this; n = n->get_next(); return p; }
    list_iterator& operator--() { n = n->get_prev(); return *this; }
    list_iterator operator--(int) { list_iterator p = *this; n = n->get_prev(); return p; }
    node_type* node() const { return n; }
private:
    NodeT* n;
};

template<typename NodeT>
bool operator==(const list_iterator<NodeT>& x, const list_iterator<NodeT>& y)
{
    return x.node() == y.node();
}

template<typename NodeT>
bool operator<(const list_iterator<NodeT>& x, const list_iterator<NodeT>& y)
{
    return x.node() < y.node();
}

template<typename T>
class list
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int64_t;
    using node_type = list_node<T>;
    using iterator = list_iterator<node_type>;
    using const_iterator = list_iterator<const node_type>;

    list() : head(nullptr), tail(nullptr), sz(0) {}
    explicit list(size_type n);
    list(size_type n, const T& value);
    list(const list& x);
    list(list&& x) : head(x.head), tail(x.tail), sz(x.sz)
    {
        x.head = nullptr;
        x.tail = nullptr;
        x.sz = 0;
    }
    ~list() { clear(); }
    list& operator=(const list& x);
    list& operator=(list&& x)
    {
        std::swap(head, x.head);
        std::swap(tail, x.tail);
        std::swap(sz, x.sz);
        return *this;
    }
    void assign(size_type n, const T& value);

    iterator begin() { return iterator(head); }
    const_iterator begin() const { return const_iterator(head); }
    iterator end() { return iterator(); }
    const_iterator end() const { return const_iterator(); }
    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator cend() const { return const_iterator(); }

    bool empty() const { return head == nullptr; }
    size_type size() const { return sz; }
    void resize(size_type sz);
    void resize(size_type sz, const T& c);

    reference front() { return head->value(); }
    const_reference front() const { return head->value(); }
    reference back() { return tail->value(); }
    const_reference back() const { return tail->value(); }

    void push_front(const T& x)
    {
        node_type* n = new node_type(x);
        n->set_next(head);
        if (head)
        {
            head->set_prev(n);
        }
        else
        {
            tail = n;
        }
        head = n;
        ++sz;
    }
    void push_front(T&& x)
    {
        node_type* n = new node_type(std::move(x));
        n->set_next(head);
        if (head)
        {
            head->set_prev(n);
        }
        else
        {
            tail = n;
        }
        head = n;
        ++sz;
    }
    void pop_front()
    {
        node_type* n = head;
        head = head->get_next();
        delete n;
        --sz;
        if (!head)
        {
            tail = nullptr;
        }
        else
        {
            node_type* p = nullptr;
            head->set_prev(p);
        }
    }
    void push_back(const T& x)
    {
        node_type* n = new node_type(x);
        n->set_prev(tail);
        if (tail)
        {
            tail->set_next(n);
        }
        else
        {
            head = n;
        }
        tail = n;
        ++sz;
    }
    void push_back(T&& x)
    {
        node_type* n = new node_type(std::move(x));
        n->set_prev(tail);
        if (tail)
        {
            tail->set_next(n);
        }
        else
        {
            head = n;
        }
        tail = n;
        ++sz;
    }
    void pop_back()
    {
        node_type* n = tail;
        tail = tail->get_prev();
        delete n;
        --sz;
        if (!tail)
        {
            head = nullptr;
        }
        else
        {
            node_type* p = nullptr;
            tail->set_next(p);
        }
    }

    iterator insert(const_iterator position, const T& x) 
    {
        if (position == end())
        {
            push_back(x);
            return iterator(tail);
        }
        else
        {
            node_type* p = position.node();
            if (p == head)
            {
                push_front(x);
                return iterator(head);
            }
            else
            {
                node_type* n = new node_type(x);
                n->set_next(p);
                n->set_prev(p->get_prev());
                p->get_prev()->set_next(n);
                p->set_prev(n);
                ++sz;
                return iterator(n);
            }
        }
    }
    iterator insert(const_iterator position, T&& x)
    {
        if (position == end())
        {
            push_back(std::move(x));
            return iterator(tail);
        }
        else
        {
            node_type* p = position.node();
            if (p == head)
            {
                push_front(std::move(x));
                return iterator(head);
            }
            else
            {
                node_type* n = new node_type(std::move(x));
                n->set_next(p);
                n->set_prev(p->get_prev());
                p->get_prev()->set_next(n);
                p->set_prev(n);
                ++sz;
                return iterator(n);
            }
        }
    }
    iterator insert(const_iterator position, size_type n, const T& x);
    iterator erase(const_iterator position)
    {
        node_type* p = position.node();
        if (p == head)
        {
            pop_front();
            return iterator(head);
        }
        else if (p == tail)
        {
            pop_back();
            return iterator(tail);
        }
        else
        {
            iterator it(p->get_next());
            p->get_prev()->set_next(p->get_next());
            p->get_next()->set_prev(p->get_prev());
            delete p;
            --sz;
            return it;
        }
    }
    iterator erase(const_iterator first, const_iterator last);
    void clear()
    {
        while (head)
        {
            node_type* n = head->get_next();
            delete head;
            head = n;
        }
        tail = nullptr;
        sz = 0;
    }
    
    void splice(const_iterator position, list& x);
    void splice(const_iterator position, list&& x);
    void splice(const_iterator position, list& x, const_iterator i);
    void splice(const_iterator position, list&& x, const_iterator i);
    void splice(const_iterator position, list& x, const_iterator first, const_iterator last);
    void splice(const_iterator position, list&& x, const_iterator first, const_iterator last);
    
    size_type remove(const T& value);
    size_type unique();
    
    void merge(list& x);
    void merge(list&& x);
    
    void sort();
    void reverse();
private:
    node_type* head;
    node_type* tail;
    size_type sz;
};

template<class T>
bool operator==(const list<T>& x, const list<T>& y);
template<class T>
void swap(list<T>& x, list<T>& y);

} // namespace std
