export module std.error;

import std.type.fundamental;
import std.string;

export namespace std {

class error_code
{
public:
    error_code();
    void clear();
    int value() const;
    string message() const;
    explicit operator bool() const;
};

} // namespace std
