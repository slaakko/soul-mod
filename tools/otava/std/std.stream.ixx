export module std.stream;

import std.type.fundamental;
import std.basic_string;
import std.utf;

export namespace std {

template<typename charT>
class basic_ios;
template<typename charT>
class basic_streambuf;
template<typename charT>
class basic_istream;

template<typename charT>
class basic_ostream
{
public:
    basic_ostream<charT>& flush();
    void write(const char* s)
    {
        prints(s);
    }
    void write(const string& s)
    {
        write(s.c_str());
    }
};

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, char c)
{
    basic_string<charT> str(1, c);
    s.write(to_utf8(str));
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, int x)
{
    string str = std::to_string(x);
    s.write(str);
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, int64_t x)
{
    string str = std::to_string(x);
    s.write(str);
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, const char* str)
{
    s.write(str);
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, const string& str)
{
    s.write(str);
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, const u16string& str)
{
    s.write(to_utf8(str));
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, const u32string& str)
{
    s.write(to_utf8(str));
    return s;
}

template<typename charT>
class basic_iostream;
template<typename charT>
class basic_stringbuf;
template<typename charT>
class basic_istringstream;
template<typename charT>
class basic_ostringstream;
template<typename charT>
class basic_stringstream;
template<typename charT>
class basic_filebuf;
template<typename charT>
class basic_ifstream;
template<typename charT>
class basic_ofstream;
template<typename charT>
class basic_fstream;
template<typename charT>
class basic_syncbuf;
template<typename charT>
class basic_osyncstream;
template<typename charT>
class istreambuf_iterator;
template<typename charT>
class ostreambuf_iterator;
using ios = basic_ios<char>;
using wios = basic_ios<wchar_t>;
using streambuf = basic_streambuf<char>;
using istream = basic_istream<char>;
using ostream = basic_ostream<char>;
using iostream = basic_iostream<char>;
using stringbuf = basic_stringbuf<char>;
using istringstream = basic_istringstream<char>;
using ostringstream = basic_ostringstream<char>;
using stringstream = basic_stringstream<char>;
using filebuf = basic_filebuf<char>;
using ifstream = basic_ifstream<char>;
using ofstream = basic_ofstream<char>;
using fstream = basic_fstream<char>;
using syncbuf = basic_syncbuf<char>;
using osyncstream = basic_osyncstream<char>;
using wstreambuf = basic_streambuf<wchar_t>;
using wistream = basic_istream<wchar_t>;
using wostream = basic_ostream<wchar_t>;
using wiostream = basic_iostream<wchar_t>;
using wstringbuf = basic_stringbuf<wchar_t>;
using wistringstream = basic_istringstream<wchar_t>;
using wostringstream = basic_ostringstream<wchar_t>;
using wstringstream = basic_stringstream<wchar_t>;
using wfilebuf = basic_filebuf<wchar_t>;
using wifstream = basic_ifstream<wchar_t>;
using wofstream = basic_ofstream<wchar_t>;
using wfstream = basic_fstream<wchar_t>;
using wsyncbuf = basic_syncbuf<wchar_t>;
using wosyncstream = basic_osyncstream<wchar_t>;

class ios_base
{
public:
    enum class openmode
    {
        app, ate, binary, in, out, trunc
    };
};

// istream cin;
ostream cout;
// ostream cerr;
// ostream clog;


template class basic_ostream<char>;

} // namespace std
