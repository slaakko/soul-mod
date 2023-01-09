module std.basic_string;

namespace std {

template<typename T>
string to_string_signed(T x)
{
    string s;
    T u = static_cast<T>(0);
    bool neg = x < static_cast<T>(0);
    if (neg)
    {
        u = -x;
    }
    else
    {
        u = x;
    }
    do
    {
        s.append(1, static_cast<char>(static_cast<uint8_t>('0') + static_cast<uint8_t>(u % static_cast<T>(10))));
        u /= static_cast<T>(10);
    } while (u != static_cast<T>(0));
    if (neg)
    {
        s.append(1, '-');
    }
    reverse(s.begin(), s.end());
    return s;
}

template<typename T>
string to_string_unsigned(T x)
{
    string s;
    do
    {
        s.append(1, static_cast<char>(static_cast<uint8_t>('0') + static_cast<uint8_t>(x % static_cast<T>(static_cast<uint8_t>(10)))));
        x /= static_cast<T>(static_cast<uint8_t>(10));
    } while (x != static_cast<T>(static_cast<uint8_t>(10)));
    reverse(s.begin(), s.end());
    return s;
}

string to_string(int val)
{
    return to_string_signed(val);
}

string to_string(unsigned val)
{
    return to_string_unsigned(val);
}

string to_string(long val)
{
    return to_string_signed(val);
}

string to_string(unsigned long val)
{
    return to_string_unsigned(val);
}

string to_string(long long val)
{
    return to_string_signed(val);
}

string to_string(unsigned long long val)
{
    return to_string_unsigned(val);
}

} // namespace std