import std.core;

enum class Month : int8_t
{
    january = 1, february, march, april, may, june, july, august, september, october, november, december
};

class Date
{
public:
    Date() : year(0), month(Month::january), day(1)
    {
    }
private:
    int16_t year;
    Month month;
    int8_t day;
};

int main()
{
    Date date;
    return 0;
}
