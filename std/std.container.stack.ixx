export module std.container.stack;

import std.type.fundamental;

export namespace std {

template<typename T, typename Container = vector>
class stack
{
public:
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;
    using container_type = Container;
protected:
    Container c;
public: 
    stack();
    explicit stack(const Container&);
    explicit stack(Container&&);
    bool empty() const;
    size_type size() const;
    reference top();
    const_reference top() const;
    void push(const value_type& x);
    void push(value_type&& x);
    void pop();
    void swap(stack& s);
};

template<class T, class Container>
void swap(stack<T, Container>& x, stack<T, Container>& y);

} // namespace std
