export module std.exception;

import std.basic_string;

export namespace std {

class exception
{
public:
    exception();
    exception(const exception&);
    exception& operator=(const exception&);
    virtual ~exception();
    virtual const char* what() const;
private:
    string str;
};

class logic_error : public exception
{
public:
    explicit logic_error(const string& what);
    explicit logic_error(const char* what);
};

class domain_error : public logic_error
{
public:
    explicit domain_error(const string& what);
    explicit domain_error(const char* what);
};

class invalid_argument : public logic_error
{
public:
    explicit invalid_argument(const string& what);
    explicit invalid_argument(const char* what);
};

class length_error : public logic_error
{
public:
    explicit length_error(const string& what);
    explicit length_error(const char* what);
};

class out_of_range : public logic_error
{
public:
    explicit out_of_range(const string& what);
    explicit out_of_range(const char* what);
};

class runtime_error : public exception
{
public:
    explicit runtime_error(const string& what);
    explicit runtime_error(const char* what);
};

class range_error : public runtime_error
{
public:
    explicit range_error(const string& what);
    explicit range_error(const char* what);
};

class overflow_error : public runtime_error
{
public:
    explicit overflow_error(const string& what);
    explicit overflow_error(const char* what);
};

class underflow_error : public runtime_error
{
public:
    explicit underflow_error(const string& what);
    explicit underflow_error(const char* what);
};

} // namespace std
