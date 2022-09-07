export module std.chrono.clock;

import std.type.fundamental;
import std.chrono.duration;
import std.chrono.time_point;

export namespace std::chrono {

class steady_clock
{
public:
	using rep = int64_t;
	using period = nano;
	using duration = chrono::duration<rep, period>;
	using time_point = chrono::time_point<steady_clock, duration>;
	static constexpr bool is_steady = true;
	static time_point now();
};

using file_clock = steady_clock;

} // std::chrono
