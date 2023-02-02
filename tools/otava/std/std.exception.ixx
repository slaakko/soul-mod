export module std.exception;

import std.basic_string;

export namespace std {

class exception
{
public:
    exception();
    exception(const string& str_);
    exception(const char* str_);
    virtual ~exception();
    virtual const char* what() const;
private:
    string str;
    const char* c_str;
};

class bad_alloc : public exception
{
public:
    const char* what() const override;
};

class logic_error : public exception
{
public:
    explicit logic_error(const string& str_);
    explicit logic_error(const char* str_);
};

class domain_error : public logic_error
{
public:
    explicit domain_error(const string& str_);
    explicit domain_error(const char* str_);
};

class invalid_argument : public logic_error
{
public:
    explicit invalid_argument(const string& str_);
    explicit invalid_argument(const char* str_);
};

class length_error : public logic_error
{
public:
    explicit length_error(const string& str_);
    explicit length_error(const char* str_);
};

class out_of_range : public logic_error
{
public:
    explicit out_of_range(const string& str_);
    explicit out_of_range(const char* str_);
};

class runtime_error : public exception
{
public:
    explicit runtime_error(const string& str_);
    explicit runtime_error(const char* str_);
};

class range_error : public runtime_error
{
public:
    explicit range_error(const string& str_);
    explicit range_error(const char* str_);
};

class overflow_error : public runtime_error
{
public:
    explicit overflow_error(const string& str_);
    explicit overflow_error(const char* str_);
};

class underflow_error : public runtime_error
{
public:
    explicit underflow_error(const string& str_);
    explicit underflow_error(const char* str_);
};

class utf_exception : public runtime_error
{
public:
    explicit utf_exception(const string& str_);
    explicit utf_exception(const char* str_);
};

} // namespace std
