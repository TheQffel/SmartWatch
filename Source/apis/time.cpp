#include "updater.h"

namespace Api_Time
{
    String Days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    String Months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    int Year = 2000;
    int Month = 1;
    int Day = 1;
    int Hour = 12;
    int Minute = 0;
    int Second = 0;

    String DayName = "Unknown";
    String MonthName = "Unknown";

    bool Sync()
    {
        
    }

    void Update()
    {
        struct tm TimeInfo;
        getLocalTime(&TimeInfo, 100);
        Year = TimeInfo.tm_year+1900;
        Month = TimeInfo.tm_mon+1;
        Day = TimeInfo.tm_mday;
        Hour = TimeInfo.tm_hour;
        Minute = TimeInfo.tm_min;
        Second = TimeInfo.tm_sec;
        DayName = Days[TimeInfo.tm_wday-1];
        MonthName = Months[TimeInfo.tm_mon];
    }
}