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
    
    constexpr duration() = default;
    duration(const duration&) = default;
    duration& operator=(const duration&) = default;
    constexpr rep count() const { return rep; }
    duration operator+() const;
    duration operator-() const;
    duration& operator++()
    {
        ++rep_;
        return *this;
    }
    duration operator++(int)
    {
        return duration(rep_++);
    }
    duration& operator--()
    {
        --rep;
        return *this;
    }
    duration operator--(int)
    {
        return duration(rep_--);
    }
    duration& operator+=(const duration& d)
    {
        rep_ += d.count();
        return *this;
    }
    duration& operator-=(const duration& d)
    {
        rep_ -= d.count();
        return *this;
    }
    duration& operator*=(const rep& rhs)
    {
        rep_ *= rhs;
        return *this;
    }
    duration& operator/=(const rep& rhs)
    {
        rep_ /= rhs;
        return *this;
    }
    duration& operator%=(const rep& rhs)
    {
        rep_ %= rhs;
        return *this;
    }
    duration& operator%=(const duration& rhs)
    {
        rep_ %= rhs.count();
        return *this;
    }

    static constexpr duration zero();
    static constexpr duration min();
    static constexpr duration max();
private:
    Rep rep_;
};

} // std::chrono
