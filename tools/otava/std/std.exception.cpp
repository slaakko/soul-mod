module std.exception;

namespace std {

exception::exception() : str(), c_str(nullptr)
{
}

exception::exception(const string& str_) : str(str_), c_str(nullptr)
{
}

exception::exception(const char* str_)  : str(), c_str(str_)
{
}

exception::~exception()
{
}

const char* exception::what() const
{
    if (c_str)
    {
        return c_str;
    }
    else
    {
        return str.c_str();
    }
}

const char* bad_alloc::what() const
{
    return "bad alloc";
}

logic_error::logic_error(const string& str_) : exception(str_)
{
}

logic_error::logic_error(const char* str_) : exception(str_)
{
}

domain_error::domain_error(const string& str_) : logic_error(str_)
{
}

domain_error::domain_error(const char* str_) : logic_error(str_)
{
}

invalid_argument::invalid_argument(const string& str_) : logic_error(str_)
{
}

invalid_argument::invalid_argument(const char* str_) : logic_error(str_)
{
}

length_error::length_error(const string& str_) : logic_error(str_)
{
}

length_error::length_error(const char* str_) : logic_error(str_)
{
}

out_of_range::out_of_range(const string& str_) : logic_error(str_)
{
}

out_of_range::out_of_range(const char* str_) : logic_error(str_)
{
}

runtime_error::runtime_error(const string& str_) : exception(str_)
{
}

runtime_error::runtime_error(const char* str_) : exception(str_)
{
}

range_error::range_error(const string& str_) : runtime_error(str_)
{
}

range_error::range_error(const char* str_) : runtime_error(str_)
{
}

overflow_error::overflow_error(const string& str_) : runtime_error(str_)
{
}

overflow_error::overflow_error(const char* str_) : runtime_error(str_)
{
}

underflow_error::underflow_error(const string& str_) : runtime_error(str_)
{
}

underflow_error::underflow_error(const char* str_) : runtime_error(str_)
{
}

utf_exception::utf_exception(const string& str_) : runtime_error(str_)
{
}

utf_exception::utf_exception(const char* str_) : runtime_error(str_)
{
}
} // namespace std
