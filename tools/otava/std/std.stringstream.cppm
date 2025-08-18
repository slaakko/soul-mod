export module std.stringstream;

import std.stream;

export namespace std {

template<typename CharT>
class basic_istringstream : public basic_istream<CharT>
{
public:
    basic_istringstream() : basic_istream<CharT>(), s()
    {
    }
    std::basic_string<CharT> str() const
    {
        return s;
    }
    void str(std::basic_string<CharT>&& s)
    {
        this->s = s;
    }
private:
    std::basic_string<CharT> s;
};

template<typename CharT>
class basic_ostringstream : public basic_ostream<CharT>
{
public:
    basic_ostringstream() : basic_ostream<CharT>(), s()
    {
    }
    void write(const char* s) override
    {
        while (*s)
        {
            char c = *s++;
            this->s.append(1, c);
        }
    }
    std::basic_string<CharT> str() const
    {
        return s;
    }
    void str(std::basic_string<CharT>&& s)
    {
        this->s = s;
    }
private:
    std::basic_string<CharT> s;
};

template<typename CharT>
class basic_stringstream : public basic_iostream<CharT>
{
public:
    basic_stringstream() : basic_iostream<CharT>(), s()
    {
    }
    void write(const char* s) override
    {
        while (*s)
        {
            char c = *s++;
            this->s.append(1, c);
        }
    }
    std::basic_string<CharT> str() const
    {
        return s;
    }
    void str(std::basic_string<CharT>&& s)
    {
        this->s = s;
    }
private:
    std::basic_string<CharT> s;
};

using istringstream = basic_istringstream<char>;
using ostringstream = basic_ostringstream<char>;
using stringstream = basic_stringstream<char>;

} // namespace std
