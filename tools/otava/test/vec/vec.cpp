import std.core;

template<typename T>
class vec
{
public:
    using size_type = ssize_t;
    using value_type = T;
    vec() : elements(nullptr), sz(0), res(0) {}
    size_type size() const { return sz; }
    size_type capacity() const { return res; }
private:
    T* elements;
    size_type sz;
    size_type res;
};

int main()
{
    vec<int> v;
    int s = v.size();
    return 0;
}
