export module std.basic_string;

import std.type.fundamental;
import std.utilities.utility;
import std.type_traits;
import std.rt;
import std.algorithm;

export namespace std {

char32_t nul = 0;

template<typename charT>
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
    
    static const size_type npos = -1;
    
    inline basic_string() : chars(nullptr), len(0), res(0) 
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
    basic_string(const basic_string& that, size_type pos) : chars(nullptr), len(slen(that.chars + pos)), res(0)
    {
        if (len > 0)
        {
            reserve(len);
            scpy(chars, that.chars + pos);
        }
    }
    basic_string(const basic_string& that, size_type pos, size_type n) : chars(nullptr), len(0), res(0)
    {
        size_type ln = min(slen(that.chars + pos), n);
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
    basic_string(const charT* begin, const charT* end) : basic_string<charT>(begin, end - begin)
    {
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
    inline basic_string(basic_string&& that) : chars(that.chars), len(that.len), res(that.res)
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
        swap(chars, that.chars);
        swap(len, that.len);
        swap(res, that.res);
        return *this;
    }
    basic_string& operator=(const charT* s)
    {
        deallocate();
        len = slen(s);
        reserve(len);
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
    inline iterator begin() 
    { 
        return chars; 
    }
    inline const_iterator begin() const 
    { 
        return chars; 
    }
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
    inline const_iterator cbegin() const 
    { 
        return chars; 
    }
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
    inline size_type size() const 
    { 
        return len; 
    }
    inline size_type length() const 
    { 
        return len; 
    }
    size_type max_size() const;
    void resize(size_type n, charT c);
    void resize(size_type n);
    inline size_type capacity() const 
    { 
        return res; 
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
    void shrink_to_fit();
    inline void clear() 
    { 
        deallocate; 
    }
    inline bool empty() const 
    { 
        return len == 0; 
    }
    inline const_reference operator[](size_type pos) const
    {
        return chars[pos];
    }
    inline reference operator[](size_type pos)
    {
        return chars[pos];
    }
    const_reference at(size_type n) const;
    reference at(size_type n);
    inline const charT& front() const
    {
        return chars[0];
    }
    inline charT& front()
    {
        return chars[0];
    }
    inline const charT& back() const
    {
        return chars[len - 1];
    }
    inline charT& back()
    {
        return chars[len - 1];
    }
    inline basic_string& operator+=(const basic_string& str)
    {
        return append(str);
    }
    inline basic_string& operator+=(const charT* s)
    {
        return append(s);
    }
    inline basic_string& operator+=(charT c)
    {
        return append(1, c);
    }
    inline basic_string& append(const basic_string& str)
    {
        append_from(str.c_str(), str.length());
        return *this;
    }
    inline basic_string& append(const basic_string& str, size_type pos)
    {
        append_from(str.c_str() + pos, str.length() - pos);
        return *this;
    }
    inline basic_string& append(const basic_string& str, size_type pos, size_type n)
    {
        append_from(str.c_str() + pos, n);
        return *this;
    }
    inline basic_string& append(const charT* s, size_type n)
    {
        append_from(s, n);
        return *this;
    }
    inline basic_string& append(const charT* s)
    {
        append_from(s, slen(s));
        return *this;
    }
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
    inline void push_back(charT c)
    {
        append(1, c);
    }
    basic_string& assign(const basic_string& str)
    {
        clear();
        return append(str);
    }
    basic_string& assign(basic_string&& that)
    {
        std::swap(chars, that.chars);
        std::swap(len, that.len);
        std::swap(res, that.res);
        return *this;
    }
    basic_string& assign(const basic_string& str, size_type pos)
    {
        clear();
        return append(str, pos);
    }
    basic_string& assign(const basic_string& str, size_type pos, size_type n)
    {
        clear();
        return append(str, pos, n);
    }
    basic_string& assign(const charT* s, size_type n)
    {
        clear();
        append_from(s, n);
        return *this;
    }
    basic_string& assign(const charT* s)
    {
        clear();
        append_from(s, slen(s));
        return *this;
    }
    basic_string& assign(size_type n, charT c)
    {
        clear();
        return append(n, c);
    }
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
    inline void swap(basic_string& that)
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
    inline const charT* data() const 
    { 
        return chars; 
    }
    inline charT* data() 
    { 
        return chars; 
    }
    inline size_type find(const basic_string& str) const
    {
        return find(str, 0);
    }
    size_type find(const basic_string& str, size_type pos) const
    {
        if (str.empty()) return pos;
        size_type p = find(str[0], pos);
        while (p != npos)
        {
            bool found = true;
            for (size_type i = 1; i < str.length(); ++i)
            {
                if (chars[i + p] != str[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return p;
            }
            p = find(str[0], p + 1);
        }
        return npos;
    }
    inline size_type find(const charT* s) const
    {
        return find(s, 0);
    }
    inline size_type find(const charT* s, size_type pos) const
    {
        return find(s, slen(s), pos);
    }
    size_type find(const charT* s, size_type n, size_type pos) const
    {
        if (n == 0) return pos;
        size_type p = find(s[0], pos);
        while (p != npos)
        {
            bool found = true;
            for (size_type i = 1; i < n; ++i)
            {
                if (chars[i + p] != s[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return p;
            }
            p = find(s[0], p + 1);
        }
        return npos;
    }
    inline size_type find(charT c) const
    {
        return find(c, 0);
    }
    size_type find(charT c, size_type pos) const
    {
        if (!chars) return npos;
        for (size_type i = pos; i < len; ++i)
        {
            if (chars[i] == c)
            {
                return i;
            }
        }
        return npos;
    }
    inline size_type rfind(const basic_string& str) const
    {
        return rfind(str, npos);
    }
    size_type rfind(const basic_string& str, size_type pos) const
    {
        if (str.empty()) return pos;
        size_type p = rfind(str[0], pos);
        while (p != npos)
        {
            bool found = true;
            for (size_type i = 1; i < str.length(); ++i)
            {
                if (chars[i + p] != str[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return p;
            }
            p = rfind(str[0], p - 1);
        }
        return npos;
    }
    inline size_type rfind(const charT* s) const
    {
        return rfind(s, slen(s));
    }
    inline size_type rfind(const charT* s, size_type n) const
    {
        return rfind(s, n, npos);
    }
    size_type rfind(const charT* s, size_type n, size_type pos) const
    {
        if (n == 0) return pos;
        size_type p = rfind(s[0], pos);
        while (p != npos)
        {
            bool found = true;
            for (size_type i = 1; i < n; ++i)
            {
                if (chars[i + p] != s[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return p;
            }
            p = rfind(s[0], p - 1);
        }
        return npos;
    }
    inline size_type rfind(charT c) const
    {
        return rfind(c, npos);
    }
    size_type rfind(charT c, size_type pos) const
    {
        if (!chars) return npos;
        if (pos == npos)
        {
            pos = len - 1;
        }
        for (size_type i = pos; i >= 0; --i)
        {
            if (chars[i] == c)
            {
                return i;
            }
        }
        return npos;
    }
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
    
    basic_string substr() const
    {
        if (chars)
        {
            return basic_string<charT>(chars);
        }
        else
        {
            return basic_string<charT>();
        }
    }
    basic_string substr(size_type pos) const
    {
        if (pos >= 0 && pos < len)
        {
            return basic_string<charT>(chars + pos);
        }
        else
        {
            return basic_string<charT>();
        }
    }
    basic_string substr(size_type pos, size_type n) const
    {
        if (pos >= 0 && pos < len)
        {
            return basic_string<charT>(chars + pos, n);
        }
        else
        {
            return basic_string<charT>();
        }
    }
   
    int compare(const basic_string& str) const;
    int compare(size_type pos1, size_type n1, const basic_string& str) const;
    int compare(size_type pos1, size_type n1, const basic_string& str, size_type pos2, size_type n2 = npos) const;
    int compare(const charT* s) const;
    int compare(size_type pos1, size_type n1, const charT* s) const;
    int compare(size_type pos1, size_type n1, const charT* s, size_type n2) const;
    
    inline bool starts_with(charT x) const
    {
        if (empty()) return false;
        return chars[0] == x;
    }
    bool starts_with(const charT* s) const
    {
        size_type n = slen(s);
        if (len < n) return false;
        for (size_type i = 0; i < n; ++i)
        {
            if (chars[i] != s[i]) return false;
        }
        return true;
    }
    inline bool starts_with(const basic_string<charT>& s) const
    {
        return starts_with(s.c_str());
    }
    inline bool ends_with(charT x) const
    {
        if (empty()) return false;
        return chars[len - 1] == x;
    }
    bool ends_with(const charT* s) const
    {
        size_type n = len;
        size_type m = slen(s);
        if (n < m) return false;
        for (size_type i = 0; i < m; ++i)
        {
            if (chars[i + n - m] != s[i]) return false;
        }
        return true;
    }
    inline bool ends_with(const basic_string<charT>& s) const
    {
        return ends_with(s.c_str());
    }
    inline bool contains(charT x) const
    {
        return find(x) != npos;
    }
    inline bool contains(const charT* s) const
    {
        return find(s) != npos;
    }
private:
    void append_from(const charT* s, size_type n)
    {
        size_type newlen = len + n;
        if (newlen > 0)
        {
            reserve(newlen);
            newlen = len + slencpy(chars + len, s, n);
        }
        len = newlen;
    }
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

template<typename charT>
basic_string<charT> operator+(const basic_string<charT>& lhs, const basic_string<charT>& rhs)
{
    basic_string<charT> result(lhs);
    result.append(rhs);
    return result;
}

template<typename charT>
basic_string<charT> operator+(const charT* lhs, const basic_string<charT>& rhs)
{
    basic_string<charT> result(lhs);
    result.append(rhs);
    return result;
}

template<typename charT>
basic_string<charT> operator+(const basic_string<charT>& lhs, const charT* rhs)
{
    basic_string<charT> result(lhs);
    result.append(rhs);
    return result;
}

template<typename charT>
bool operator==(const basic_string<charT>& lhs, const basic_string<charT>& rhs)
{
    ssize_t len = lhs.length();
    if (len != rhs.length()) return false;
    for (ssize_t i = 0; i < len; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template<typename charT>
bool operator==(const basic_string<charT>& lhs, const charT* rhs)
{
    ssize_t len = lhs.length();
    if (len != slen(rhs)) return false;
    for (ssize_t i = 0; i < len; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template<typename charT>
bool operator==(const charT* lhs, const basic_string<charT>& rhs)
{
    ssize_t len = slen(lhs);
    if (len != rhs.length()) return false;
    for (ssize_t i = 0; i < len; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template<typename charT>
bool operator<(const basic_string<charT>& lhs, const basic_string<charT>& rhs)
{
    ssize_t leftLen = lhs.length();
    ssize_t rightLen = rhs.length();
    if (leftLen == 0 && rightLen > 0) return true;
    if (leftLen > 0 && rightLen == 0) return false;
    ssize_t n = min(leftLen, rightLen);
    for (ssize_t i = 0; i < n; ++i)
    {
        charT l = lhs[i];
        charT r = rhs[i];
        if (l < r) return true;
        if (l > r) return false;
    }
    if (leftLen < rightLen) return true;
    return false;
}

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
// string to_string(long double val);

char hex_char(int nibble);

template<typename T>
string to_hex(const T& x)
{
    string s;
    int n = sizeof(x);
    for (int i = 0; i < n; ++i)
    {
        uint8_t b = x & 0xFF;
        s.append(1, hex_char(b & 0x0F));
        s.append(1, hex_char(b >> 4));
        x = x >> 8;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

string to_hexstring(uint8_t x);
string to_hexstring(uint16_t x);
string to_hexstring(uint32_t x);
string to_hexstring(uint64_t x);

template<typename T>
string to_oct(const T& x)
{
    uint8_t zero = 0;
    string s;
    do
    {
        uint8_t b = x;
        s.append(1, static_cast<char>(static_cast<int>(b & 7) + static_cast<int>('0')));
        x = x >> 3;
    } while (x != 0);
    if (s[s.length() - 1] != '0')
    {
        s.append(1, '0');
    }
    std::reverse(s.begin(), s.end());
    return s;
}

string to_octstring(uint8_t x);
string to_octstring(uint16_t x);
string to_octstring(uint32_t x);
string to_octstring(uint64_t x);

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
