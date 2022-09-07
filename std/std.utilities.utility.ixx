export module std.utilities.utility;

import std.type.fundamental;

export namespace std {

template<class T>
T&& move(T&& x);

} // namespace std
