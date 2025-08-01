// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.time;

import std;

export namespace util {

enum class Month : std::int8_t
{
    january = 1, february, march, april, may, june, july, august, september, october, november, december
};

int GetMonthDays(Month month, int year);

class Date
{
public:
    inline Date() : year(0), month(Month::january), day(1)
    {
    }
    inline Date(short year_, Month month_, std::int8_t day_) : year(year_), month(month_), day(day_)
    {
    }
    inline std::int16_t Year() const
    {
        return year;
    }
    inline Month GetMonth() const
    {
        return month;
    }
    inline std::int8_t Day() const
    {
        return day;
    }
    Date AddDays(int n);
    Date AddMonths(int n);
    Date AddYears(int n);
    std::string ToString() const;
    std::string ToString(bool omitDashes) const;
private:
    std::int16_t year;
    Month month;
    std::int8_t day;
};

Date GetCurrentDate();

bool operator==(const Date& left, const Date& right);

inline bool operator!=(const Date& left, const Date& right)
{
    return !(left == right);
}

bool operator<(const Date& left, const Date& right);

inline bool operator>(const Date& left, const Date& right)
{
    return right < left;
}

inline bool operator<=(const Date& left, const Date& right)
{
    return !(right > left);
}

inline bool operator>=(const Date& left, const Date& right)
{
    return !(left < right);
}

Date ParseDate(const std::string& dateStr);

class DateTime
{
public:
    inline DateTime() : date(), secs(0)
    {
    }
    inline DateTime(const Date& date_) : date(date_), secs(0)
    {
    }
    inline DateTime(const Date& date_, std::int32_t secs_) : date(date_), secs(secs_)
    {
    }
    inline Date GetDate() const
    {
        return date;
    }
    inline std::int32_t Hours() const
    {
        return secs / 3600;
    }
    inline std::int32_t Minutes() const
    {
        return secs / 60;
    }
    inline std::int32_t Seconds() const
    {
        return secs;
    }
    std::string ToString() const;
    std::string ToString(bool omitDashes, bool omitColons, bool omitMins, bool omitSecs) const;
private:
    Date date;
    std::int32_t secs;
};

DateTime GetCurrentDateTime();

bool operator==(const DateTime& left, const DateTime& right);

inline bool operator!=(const DateTime& left, const DateTime& right)
{
    return !(left == right);
}

bool operator<(const DateTime& left, const DateTime& right);

inline bool operator>(const DateTime& left, const DateTime& right)
{
    return right < left;
}

inline bool operator<=(const DateTime& left, const DateTime& right)
{
    return !(right > left);
}

inline bool operator>=(const DateTime& left, const DateTime& right)
{
    return !(left < right);
}

DateTime ParseDateTime(const std::string& dateTimeStr);

const int secsInDay = 24 * 3600;

std::string FormatTimeMs(std::int32_t milliseconds);

std::int64_t CurrentMs();

std::int64_t GetCurrentTime();

std::string DurationStr(const std::chrono::nanoseconds& duration);

std::time_t Time();

std::time_t MkTime(const DateTime& dt);

DateTime ToDateTime(std::time_t time);

std::string TimeToString(std::time_t time);

} // namespace soulng::util
