export module std.stream;

import std.type.fundamental;
import std.basic_string;
import std.utf;
import std.atexit;

export namespace std {

enum class fmtflags
{
    none = 0, dec = 1 << 0, oct = 1 << 1, hex = 1 << 2, basefield = dec | oct | hex
};

constexpr fmtflags operator|(fmtflags left, fmtflags right)
{
    return fmtflags(int(left) | int(right));
}

constexpr fmtflags operator&(fmtflags left, fmtflags right)
{
    return fmtflags(int(left) & int(right));
}

constexpr fmtflags operator~(fmtflags f)
{
    return fmtflags(~int(f));
}

class ios_base
{
public:
    ios_base();
    virtual ~ios_base();
    enum class openmode
    {
        app, ate, binary, in, out, trunc
    };
    fmtflags flags() const;
    void flags(fmtflags f_);
    void setf(fmtflags f_);
    void unsetf(fmtflags f_);
private:
    fmtflags fl;
};

template<typename charT>
class basic_ios : public ios_base
{
public:
    virtual void write(const char* s) = 0;
};

template<typename charT>
class basic_streambuf;
template<typename charT>
class basic_istream;

template<typename charT>
class basic_ostream : public basic_ios<charT>
{
public:
    basic_ostream() : handle(1)
    {
    }
    explicit basic_ostream(int handle_) : handle(handle_)
    {
    }
    basic_ostream<charT>& flush()
    {
        flush_handle(handle);
        return *this;
    }
    void write(const char* s) override
    {
        ort_io_write(handle, s);
    }
    void write(const string& s) 
    {
        write(s.c_str());
    }
private:
    int handle;
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
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, long long x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
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
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, bool x)
{
    if (x) return s << "true"; else return s << "false";
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, long x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, unsigned long x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, unsigned long long x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, double x)
{
    string str(to_string(x));
    return s << str;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, const void* x)
{
    unsigned long long value = *static_cast<const unsigned long long*>(x);
    return s << value;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, nullptr_t)
{
    return s << "nullptr";
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, short x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>&operator<<(basic_ostream<charT>&s, unsigned short x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, unsigned int x)
{
    fmtflags f = s.flags();
    if ((f & fmtflags::dec) != fmtflags::none)
    {
        string str = to_string(x);
        s.write(str);
    }
    else if ((f & fmtflags::oct) != fmtflags::none)
    {
        string str = to_octstring(x);
        s.write(str);
    }
    else if ((f & fmtflags::hex) != fmtflags::none)
    {
        string str = to_hexstring(x);
        s.write(str);
    }
    return s;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, float x)
{
    string str(to_string(x));
    return s << str;
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, ios_base& (*f)(ios_base&))
{
    return f(s);
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, basic_ios<charT>& (*f)(basic_ios<charT>&))
{
    return f(s);
}

template<typename charT>
basic_ostream<charT>& operator<<(basic_ostream<charT>& s, basic_ostream<charT>& (*f)(basic_ostream<charT>&))
{
    return f(s);
}

ios_base& dec(std::ios_base& strm);
ios_base& hex(std::ios_base& strm);
ios_base& oct(std::ios_base& strm);

template<typename charT>
basic_ostream<charT>& endl(basic_ostream<charT>& strm)
{
    strm << "\n";
    return strm.flush();
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
class basic_ofstream : public basic_ostream<charT>
{
public:
    basic_ofstream(const char* filename) : file(nullptr)
    {
        open(filename, std::ios_base::openmode::out);
    }
    basic_ofstream(const char* filename, std::ios_base::openmode mode) : file(nullptr)
    {
        open(filename, mode);
    }
    basic_ofstream(const std::string& filename) : file(nullptr)
    {
        open(filename.c_str(), std::ios_base::openmode::out);
    }
    basic_ofstream(const std::string& filename, std::ios_base::openmode mode) : file(nullptr)
    {
        open(filename.c_str(), mode);
    }
    ~basic_ofstream()
    {
        if (file)
        {
            fclose(file);
        }
    }
    void write(const char* s) override
    {
        std::fputs(s, file);
    }
private:
    void open(const char* filename, std::ios_base::openmode mode)
    {
        if (mode == std::ios_base::openmode::out)
        {
            file = std::fopen(filename, "w");
        }
        else if (mode == std::ios_base::openmode::app)
        {
            file = std::fopen(filename, "a");
        }
    }
    FILE* file;
};

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

extern ostream cout;
extern ostream cerr;

/*
template class basic_ostream<char>;
template class basic_stringstream<char>;
*/

} // namespace std
