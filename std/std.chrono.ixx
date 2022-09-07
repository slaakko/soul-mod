export module std.chrono;

import std.type.fundamental;
import std.chrono.duration;
import std.utilities.ratio;

export namespace std::chrono {

using nanoseconds = duration<int64_t, std::nano>;
using microseconds = duration<int64_t, std::micro>;
using milliseconds = duration<int64_t, std::milli>;
using seconds = duration<int64_t, std::ratio<1, 1>>;
using minutes = duration<int64_t, std::ratio<60, 1>>;
using hours = duration<int64_t, std::ratio<3600, 1>>;

}
