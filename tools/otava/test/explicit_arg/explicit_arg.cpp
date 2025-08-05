import std;

enum class Flags
{
    none = 0, foo = 1
};

inline Flags operator|(Flags left, Flags right)
{
    return Flags(int(left) | int(right));
}

int main()
{
    Flags x = Flags::none | Flags::foo;
}
