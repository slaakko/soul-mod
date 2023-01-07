export module operator_bool;

import std.core;

class cont
{
public:
    explicit operator bool() const { return ptr != nullptr; }
private:
    void* ptr;
};
