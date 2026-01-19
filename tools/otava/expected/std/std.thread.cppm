export module std.thread;

import std.type.fundamental;
import std.chrono.time_point;
import std.chrono.duration;

export namespace std {

class thread;
class jthread;

namespace this_thread {

void yield();

template<class Clock, class Duration>
void sleep_until(const std::chrono::time_point<Clock, Duration>& absTime);
template<class Rep, class Period>
void sleep_for(const std::chrono::duration<Rep, Period>& rel_time);

} // namespace this_thread

} // namespace std
