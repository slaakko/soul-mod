export module std.chrono.duration;

import std.type.fundamental;
import std.utilities.ratio;

export namespace std::chrono {

template<class Rep, class Period = std::ratio<1>>
class duration
{
public:
    using rep = Rep;
    using period = typename Period::type;
    
    duration();
    ~duration();
    duration(const duration&);
    duration& operator=(const duration&);
    constexpr rep count() const;
    duration operator+() const;
    duration operator-() const;
    duration& operator++();
    duration operator++(int);
    duration& operator--();
    duration operator--(int);
    duration& operator+=(const duration& d);
    duration& operator-=(const duration& d);
    duration& operator*=(const rep& rhs);
    duration& operator/=(const rep& rhs);
    duration& operator%=(const rep& rhs);
    duration& operator%=(const duration& rhs);

    static constexpr duration zero();
    static constexpr duration min();
    static constexpr duration max();
};

} // std::chrono
