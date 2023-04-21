import std.core;

template <typename charT>
class foo_string
{
public:
    using size_type = int64_t;

    foo_string() : chars(nullptr), len(0), res(0) {}
    foo_string(const charT* s) : chars(nullptr), len(std::slen(s)), res(0)
    {
        if (len > 0)
        {
            reserve(len);
            std::scpy(chars, s);
        }
    }
    foo_string(foo_string&& that) : chars(that.chars), len(that.len), res(that.res)
    {
        that.chars = nullptr;
        that.len = 0;
        that.res = 0;
    }
    void reserve(size_type n)
    {
        if (n > 0)
        {
            size_type min_res = n + 1;
            if (min_res > res)
            {
                grow(min_res);
            }
        }
    }
    void grow(size_type min_res)
    {
        min_res = std::grow_size(min_res);
        charT* new_chars = static_cast<charT*>(malloc(min_res * sizeof(charT)));
        if (chars)
        {
            std::scpy(new_chars, chars);
            free(chars);
        }
        chars = new_chars;
        res = min_res;
    }
private:
    charT* chars;
    size_type len;
    size_type res;
};

int main()
{
    foo_string<char> s("foo");
    foo_string<char> t = std::move(s);
    return 0;
}
