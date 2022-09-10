export module std.chrono.time_point;

import std.type.fundamental;

export namespace std::chrono {

template<class Clock, class Duration = Clock::duration>
class time_point
{
public:
    using clock = Clock;
    using duration = Duration;
    using rep = typename duration::rep;
    using period = typename duration::period;
    
    time_point();
    explicit time_point(const duration& d);
    duration time_since_epoch() const;
    time_point& operator++();
    time_point operator++(int);
    time_point& operator--();
    time_point operator--(int);
    time_point& operator+=(const duration& d);
    time_point& operator-=(const duration& d);
    
    static constexpr time_point min();
    static constexpr time_point max();
};

} // std::chrono
