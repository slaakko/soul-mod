module std.convert;

namespace std {

string to_string(int x)
{
    string s;
    int u = 0;
    bool neg = x < 0;
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
        s.append(1, static_cast<char>(static_cast<uint8_t>('0') + static_cast<uint8_t>(u % 10)));
        u /= 10;
    } while (u != 0);
    if (neg)
    {
        s.append(1, '-');
    }
    reverse(s.begin(), s.end());
    return s;
}

} // namespace std
