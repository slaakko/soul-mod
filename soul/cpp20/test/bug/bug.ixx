export module bug;

class Foo
{
public:
	Foo(): flags() {}
	int get_flags() const { return static_cast<int>(flags); }
	enum class Flags
	{
		none = 0, foo = 1 << 0
	};
	Flags flags;
};
