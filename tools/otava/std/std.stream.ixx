export module std.stream;

import std.type.fundamental;

export namespace std {

template<class charT>
class basic_ios;
template<class charT>
class basic_streambuf;
template<class charT>
class basic_istream;

template<class charT>
class basic_ostream
{
public:
    basic_ostream<charT>& flush();
};

template<class charT>
class basic_iostream;
template<class charT>
class basic_stringbuf;
template<class charT>
class basic_istringstream;
template<class charT>
class basic_ostringstream;
template<class charT>
class basic_stringstream;
template<class charT>
class basic_filebuf;
template<class charT>
class basic_ifstream;
template<class charT>
class basic_ofstream;
template<class charT>
class basic_fstream;
template<class charT>
class basic_syncbuf;
template<class charT>
class basic_osyncstream;
template<class charT>
class istreambuf_iterator;
template<class charT>
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
// ostream cout;
// ostream cerr;
// ostream clog;
// ostream& endl(ostream& os);

} // namespace std
