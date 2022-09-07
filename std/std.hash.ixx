export module std.hash;

import std.type.fundamental;

export namespace std {

template<class T>
struct hash
{
	size_t operator()(const T& x) const;
};

} // namespace std
