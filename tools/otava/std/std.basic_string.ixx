export module std.basic_string;

import std.type.fundamental;
import std.iterator.reverse;
import std.string;

export namespace std {

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
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    static const size_type npos = -1;
    
    basic_string();
    basic_string(const basic_string& str);
    basic_string(const basic_string& str, size_type pos);
    basic_string(const basic_string& str, size_type pos, size_type n);
    basic_string(const charT* s, size_type n);
    basic_string(const charT* s);
    basic_string(size_type n, charT c);
    basic_string(basic_string&&);
    ~basic_string();
    
    basic_string& operator=(const basic_string& str);
    basic_string& operator=(basic_string&& str);
    basic_string& operator=(const charT* s);
    basic_string& operator=(charT c);
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    
    size_type size() const;
    size_type length() const;
    size_type max_size() const;
    void resize(size_type n, charT c);
    void resize(size_type n);
    size_type capacity() const;
    void reserve(size_type n);
    void shrink_to_fit();
    void clear();
    bool empty() const;
    
    const_reference operator[](size_type pos) const;
    reference operator[](size_type pos);
    const_reference at(size_type n) const;
    reference at(size_type n);
    const charT& front() const;
    charT& front();
    const charT& back() const;
    charT& back();
    
    basic_string& operator+=(const basic_string& str);
    basic_string& operator+=(const charT* s);
    basic_string& operator+=(charT c);
    basic_string& append(const basic_string& str);
    basic_string& append(const basic_string& str, size_type pos, size_type n = npos);
    basic_string& append(const charT* s, size_type n);
    basic_string& append(const charT* s);
    basic_string& append(size_type n, charT c);
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
    void swap(basic_string& str);
    const charT* c_str() const;
    const charT* data() const;
    charT* data();
    
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

template<class charT>
void swap(basic_string& lhs, basic_string& rhs);

// using string = basic_string<char>;
using u8string = basic_string<char8_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;
using wstring = basic_string<wchar_t>;

/*
string to_string(int val);
string to_string(unsigned val);
string to_string(long val);
string to_string(unsigned long val);
string to_string(long long val);
string to_string(unsigned long long val);
string to_string(float val);
string to_string(double val);
string to_string(long double val);
*/

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

} // namespace std
