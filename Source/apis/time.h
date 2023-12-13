#include "main.h"

namespace Api_Time
{
    void Setup();

    extern bool SyncScheduled;

    extern String Days[7];
    extern String Months[12];

    extern int Year;
    extern int Month;
    extern int Day;
    extern int Hour;
    extern int Minute;
    extern int Second;

    void Update(bool SkipSync = false);

    String TimeText(bool PrintHour, bool PrintMinute, bool PrintSecond, bool Order);
    String DateText(bool PrintYear, bool PrintMonth, bool PrintDay, bool Order);

    String DayName(int DayNumber);
    String MonthName(int MonthNumber);

    int WeekDay(int WeekDay, int WeekMonth, int WeekYear);
    int DaysInMonth(int MonthDay, int YearDay);
}