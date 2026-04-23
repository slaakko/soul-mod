import std;

enum class Flags : std::int32_t
{
    none = 0, bound = 1 << 0, specialization = 1 << 1, trivialDestructor = 1 << 2, returnsClass = 1 << 3, conversion = 1 << 4, fixedIrName = 1 << 5, inline_ = 1 << 6,
    generated = 1 << 7, skip = 1 << 8, containsReturnStatement = 1 << 9, containsStatics = 1 << 10, containsNodeWithNoSource = 1 << 11, skipInvokeChecking = 1 << 12,
    containsLocalVariableWithDestructor = 1 << 13,
};

struct Function
{
    Function() : flags(Flags::none) {}
    inline bool IsConversion() const noexcept { return GetFlag(Flags::conversion); }
    inline void SetConversion() noexcept { SetFlag(Flags::conversion); }
    inline bool GetFlag(Flags flag) const noexcept { return (flags & flag) != Flags::none; }
    inline void SetFlag(Flags flag) noexcept { flags = flags | flag; }
    Flags flags;
};

int main()
{
    Function foo;
    foo.SetConversion();
    bool c = foo.IsConversion();
    std::cout << c << "\n";
}
