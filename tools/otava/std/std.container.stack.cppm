export module std.container.stack;

import std.type.fundamental;

export namespace std {

template<typename T, typename Container = vector<T>>
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
    stack() : c()
    {
    }
    explicit stack(const Container& c_) : c(c_)
    {
    }
    explicit stack(Container&& that) : c(std::move(that.c))
    {
    }
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void push(value_type&& x) { c.push_back(std::move(x)); }
    void pop() { c.pop_back(); }
};

} // namespace std
