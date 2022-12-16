import std.core;

int main()
{
    unsigned x;
    uint8_t y = static_cast<uint8_t>(x % static_cast<unsigned>(10));
    return 0;
}
