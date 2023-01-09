export module std.basic_string;

import std.type.fundamental;
import std.iterator.reverse;
import std.utilities.utility;
import std.type_traits;
import std.crt;
import std.algorithm;

export namespace std {

char32_t nul = 0;

template<class charT>
class basic_string
{
public:
    using value_type = charT;
    using size_type = int64_t;
    using difference_type = int64_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = pointer;
    using const_iterator = const_pointer;
    //using reverse_iterator = std::reverse_iterator<iterator>;
    //using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    static const size_type npos = -1;
    
    basic_string() : chars(nullptr), len(0), res(0)
    {
    }
    basic_string(const basic_string& that) : chars(nullptr), len(that.len), res(0)
    {
        if (len > 0)
        {
            reserve(len);
            scpy(chars, that.chars);
        }
    }
    basic_string(const basic_string& that, size_type pos)  : chars(nullptr), len(slen(that.chars + pos)), res(0)
    {
        if (len > 0)
        {
            reserve(len);
            scpy(chars, that.chars + pos);
        }
    }
    basic_string(const basic_string& that, size_type pos, size_type n) : chars(nullptr), len(0), res(0)
    {
        size_type ln = std::min(slen(that.chars + pos), n);
        if (ln > 0)
        {
            reserve(ln);
            len = slencpy(chars, that.chars + pos, n);
        }
    }
    basic_string(const charT* s, size_type n) : chars(nullptr), len(0), res(0)
    {
        if (n > 0)
        {
            reserve(n);
            len = slencpy(chars, s, n);
        }
    }
    basic_string(const charT* s) : chars(nullptr), len(slen(s)), res(0)
    {
        if (len > 0)
        {
            reserve(len);
            scpy(chars, s);
        }
    }
    basic_string(size_type n, charT c) : chars(nullptr), len(n), res(0)
    {
        if (n > 0)
        {
            reserve(n);
            for (size_type i = 0; i < n; ++i)
            {
                chars[i] = c;
            }
            chars[n] = '\0';
        }
    }
    basic_string(basic_string&& that) : chars(that.chars), len(that.len), res(that.res)
    {
        that.chars = nullptr;
        that.len = 0;
        that.res = 0;
    }
    ~basic_string()
    {
        deallocate();
    }
    basic_string& operator=(const basic_string& that)
    {
        deallocate();
        reserve(that.len);
        len = that.len;
        if (len > 0)
        {
            scpy(chars, that.chars);
        }
        return *this;
    }
    basic_string& operator=(basic_string&& that)
    {
        std::swap(chars, that.chars);
        std::swap(len, that.len);
        std::swap(res, that.res);
        return *this;
    }
    basic_string& operator=(const charT* s)
    {
        deallocate();
        reserve(slen(s));
        scpy(chars, s);
        return *this;
    }
    basic_string& operator=(charT c)
    {
        deallocate();
        reserve(1);
        chars[0] = c;
        chars[1] = '\0';
        return *this;
    }
    iterator begin() { return chars; }
    const_iterator begin() const { return chars; }
    iterator end()
    {
        if (chars)
        {
            return chars + len;
        }
        else
        {
            return nullptr;
        }
    }
    const_iterator end() const
    {
        if (chars)
        {
            return chars + len;
        }
        else
        {
            return nullptr;
        }
    }
    //reverse_iterator rbegin();
    //const_reverse_iterator rbegin() const;
    //reverse_iterator rend();
    //const_reverse_iterator rend() const;
    const_iterator cbegin() const { return chars; }
    const_iterator cend() const
    {
        if (chars)
        {
            return chars + len;
        }
        else
        {
            return nullptr;
        }
    }
    //const_reverse_iterator crbegin() const;
    //const_reverse_iterator crend() const;
    
    size_type size() const { return len; }
    size_type length() const { return len; }
    size_type max_size() const;
    void resize(size_type n, charT c);
    void resize(size_type n);
    size_type capacity() const { return res; }
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
    void shrink_to_fit();
    void clear() { deallocate; }
    bool empty() const { return len == 0; }
    
    const_reference operator[](size_type pos) const 
    {
        return chars[pos];
    }
    reference operator[](size_type pos)
    {
        return chars[pos];
    }
    const_reference at(size_type n) const
    {
        return chars[n];
    }
    reference at(size_type n)
    {
        return chars[n];
    }
    const charT& front() const
    {
        return chars[0];
    }
    charT& front()
    {
        return chars[0];
    }
    const charT& back() const
    {
        return chars[len - 1];
    }
    charT& back()
    {
        return chars[len - 1];
    }
    
    basic_string& operator+=(const basic_string& str);
    basic_string& operator+=(const charT* s);
    basic_string& operator+=(charT c);
    basic_string& append(const basic_string& str);
    basic_string& append(const basic_string& str, size_type pos, size_type n = npos);
    basic_string& append(const charT* s, size_type n);
    basic_string& append(const charT* s);
    basic_string& append(size_type n, charT c)
    {
        if (n > 0)
        {
            reserve(len + n);
            for (size_type i = 0; i < n; ++i)
            {
                chars[len] = c;
                ++len;
            }
            chars[len] = '\0';
        }
        return *this;
    }
    void push_back(charT c);
    
    basic_string& assign(const basic_string& str);
    basic_string& assign(basic_string&& str);
    basic_string& assign(const basic_string& str, size_type pos, size_type n = npos);
    basic_string& assign(const charT* s, size_type n);
    basic_string& assign(const charT* s);
    basic_string& assign(size_type n, charT c);

    basic_string& insert(size_type pos, const basic_string& str);
    basic_string& insert(size_type pos1, const basic_string& str, size_type pos2, size_type n = npos);
    basic_string& insert(size_type pos, const charT* s, size_type n);
    basic_string& insert(size_type pos, const charT* s);
    basic_string& insert(size_type pos, size_type n, charT c);
    iterator insert(const_iterator p, charT c);
    iterator insert(const_iterator p, size_type n, charT c);

    basic_string& erase(size_type pos = 0, size_type n = npos);
    iterator erase(const_iterator p);
    iterator erase(const_iterator first, const_iterator last);
    
    void pop_back();
    
    basic_string& replace(size_type pos1, size_type n1, const basic_string& str);
    basic_string& replace(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos);
    basic_string& replace(size_type pos, size_type n1, const charT* s, size_type n2);
    basic_string& replace(size_type pos, size_type n1, const charT* s);
    basic_string& replace(size_type pos, size_type n1, size_type n2, charT c);
    basic_string& replace(const_iterator i1, const_iterator i2, const basic_string& str);
    basic_string& replace(const_iterator i1, const_iterator i2, const charT* s, size_type n);
    basic_string& replace(const_iterator i1, const_iterator i2, const charT* s);
    basic_string& replace(const_iterator i1, const_iterator i2, size_type n, charT c);
    
    size_type copy(const charT* s, size_type n, size_type pos = 0) const;
    void swap(basic_string& that)
    {
        std::swap(chars, that.chars);
        std::swap(len, that.len);
        std::swap(res, that.res);
    }
    const charT* c_str() const
    {
        if (chars)
        {
            return chars;
        }
        else
        {
            return static_cast<const charT*>(static_cast<void*>(&nul));
        }
    }
    const charT* data() const { return chars; }
    charT* data() { return chars; }
    
    size_type find(const basic_string& str, size_type pos = 0) const;
    size_type find(const charT* s, size_type n, size_type pos) const;
    size_type find(const charT* s, size_type pos) const;
    size_type find(charT c, size_type pos = 0) const;
    size_type rfind(const basic_string& str, size_type pos = npos) const;
    size_type rfind(const charT* s, size_type n, size_type pos) const;
    size_type rfind(const charT* s, size_type pos = npos) const;
    size_type rfind(charT c, size_type pos = npos) const;
    
    size_type find_first_of(const basic_string& str, size_type pos = 0) const;
    size_type find_first_of(const charT* s, size_type pos, size_type n) const;
    size_type find_first_of(const charT* s, size_type pos = 0) const;
    size_type find_first_of(charT c, size_type pos = 0) const;
    
    size_type find_last_of(const basic_string& str, size_type pos = npos) const;
    size_type find_last_of(const charT* s, size_type pos, size_type n) const;
    size_type find_last_of(const charT* s, size_type pos = npos) const;
    size_type find_last_of(charT c, size_type pos = npos) const;
    
    size_type find_first_not_of(const basic_string& str, size_type pos = 0) const;
    size_type find_first_not_of(const charT* s, size_type pos, size_type n) const;
    size_type find_first_not_of(const charT* s, size_type pos = 0) const;
    size_type find_first_not_of(charT c, size_type pos = 0) const;

    size_type find_last_not_of(const basic_string& str, size_type pos = npos) const;
    size_type find_last_not_of(const charT* s, size_type pos, size_type n) const;
    size_type find_last_not_of(const charT* s, size_type pos = npos) const;
    size_type find_last_not_of(charT c, size_type pos = npos) const;
    
    basic_string substr(size_type pos = 0, size_type n = npos) const;
    
    int compare(const basic_string& str) const;
    int compare(size_type pos1, size_type n1, const basic_string& str) const;
    int compare(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos) const;
    int compare(const charT* s) const;
    int compare(size_type pos1, size_type n1, const charT* s) const;
    int compare(size_type pos1, size_type n1, const charT* s, size_type n2) const;
    
    bool starts_with(charT x) const;
    bool starts_with(const charT* s) const;
    bool ends_with(charT x) const;
    bool ends_with(const charT* s) const;
    bool contains(charT x) const;
    bool contains(const charT* s) const;
private:
    void grow(size_type min_res)
    {
        min_res = std::grow_size(min_res);
        charT* new_chars = static_cast<charT*>(malloc(min_res * sizeof(charT)));
        if (chars)
        {
            scpy(new_chars, chars);
            free(chars);
        }
        chars = new_chars;
        res = min_res;
    }
    void deallocate()
    {
        len = 0;
        if (res != 0)
        {
            free(chars);
            res = 0;
        }
        chars = nullptr;
    }
    charT* chars;
    size_type len;
    size_type res;
};

template<class charT>
basic_string<charT> operator+(const basic_string& lhs, const basic_string& rhs);
template<class charT>
basic_string<charT> operator+(basic_string&& lhs, const basic_string& rhs);
template<class charT>
basic_string<charT> operator+(const basic_string& lhs, basic_string&& rhs);
template<class charT>
basic_string<charT> operator+(basic_string&& lhs, basic_string&& rhs);
template<class charT>
basic_string<charT> operator+(const charT* lhs, const basic_string& rhs);
template<class charT>
basic_string<charT> operator+(const charT* lhs, basic_string&& rhs);
template<class charT>
basic_string<charT> operator+(charT lhs, const basic_string& rhs);
template<class charT>
basic_string<charT> operator+(charT lhs, basic_string&& rhs);
template<class charT>
basic_string<charT> operator+(const basic_string& lhs, const charT* rhs);
template<class charT>
basic_string<charT> operator+(basic_string&& lhs, const charT* rhs);
template<class charT>
basic_string<charT> operator+(const basic_string& lhs, charT rhs);
template<class charT>
basic_string<charT> operator+(basic_string&& lhs, charT rhs);

template<class charT>
bool operator==(const basic_string& lhs, const basic_string& rhs);
template<class charT>
bool operator==(const basic_string& lhs, const charT* rhs);
template<class charT>
bool operator==(const charT* lhs, const basic_string& rhs);

using string = basic_string<char>;
using u8string = basic_string<char8_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;
using wstring = basic_string<wchar_t>;

string to_string(int val);
string to_string(unsigned val);
string to_string(long val);
string to_string(unsigned long val);
string to_string(long long val);
string to_string(unsigned long long val);
string to_string(float val);
string to_string(double val);
string to_string(long double val);

/*
wstring to_wstring(int val);
wstring to_wstring(unsigned val);
wstring to_wstring(long val);
wstring to_wstring(unsigned long val);
wstring to_wstring(long long val);
wstring to_wstring(unsigned long long val);
wstring to_wstring(float val);
wstring to_wstring(double val);
wstring to_wstring(long double val);
*/

int stoi(const string& str, size_t* idx = nullptr, int base = 10);
long stol(const string& str, size_t* idx = nullptr, int base = 10);
unsigned long stoul(const string& str, size_t* idx = nullptr, int base = 10);
long long stoll(const string& str, size_t* idx = nullptr, int base = 10);
unsigned long long stoull(const string& str, size_t* idx = nullptr, int base = 10);
float stof(const string& str, size_t* idx = nullptr);
double stod(const string& str, size_t* idx = nullptr);
long double stold(const string& str, size_t* idx = nullptr);

int stoi(const wstring& str, size_t* idx = nullptr, int base = 10);
long stol(const wstring& str, size_t* idx = nullptr, int base = 10);
unsigned long stoul(const wstring& str, size_t* idx = nullptr, int base = 10);
long long stoll(const wstring& str, size_t* idx = nullptr, int base = 10);
unsigned long long stoull(const wstring& str, size_t* idx = nullptr, int base = 10);
float stof(const wstring& str, size_t* idx = nullptr);
double stod(const wstring& str, size_t* idx = nullptr);
long double stold(const wstring& str, size_t* idx = nullptr);

template class basic_string<char>; // explicit instantiation for char type
template class basic_string<char16_t>; // explicit instantiation for char16_t type
template class basic_string<char32_t>; // explicit instantiation for char32_t type

} // namespace std
