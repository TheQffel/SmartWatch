#include "time.h"

#include "apis/console.h"
#include "apis/settings.h"
#include "apis/wifi.h"

namespace Api_Time
{
    bool SyncScheduled = true;

    String Days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    String Months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

    int Year = 2000;
    int Month = 1;
    int Day = 1;
    int Hour = 0;
    int Minute = 0;
    int Second = 0;

    void Setup()
    {
        bool Result = true;

        SmartWatch->rtc->check();
        SmartWatch->rtc->syncToSystem();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Rtc initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize rtc.");
        }
    }

    void Update(bool SkipSync)
    {
        if(SyncScheduled && !SkipSync)
        {
            if (Api_Wifi::Connected())
            {
                configTime(Api_Settings::Timezone() * 900, 0, "pool.ntp.org");

                Api_Console::Log(Api_Console::LogType::Info, "Synchronized time and date.");

                SyncScheduled = false;
            }
        }

        struct tm TimeInfo;
        getLocalTime(&TimeInfo, 100);
        Year = TimeInfo.tm_year+1900;
        Month = TimeInfo.tm_mon+1;
        Day = TimeInfo.tm_mday;
        Hour = TimeInfo.tm_hour;
        Minute = TimeInfo.tm_min;
        Second = TimeInfo.tm_sec;
    }

    String DayName(int DayNumber)
    {
        return Days[(DayNumber - 1) % 7];
    }

    String MonthName(int MonthNumber)
    {
        return Months[(MonthNumber - 1) % 12];
    }

    String TimeText(bool PrintHour, bool PrintMinute, bool PrintSecond, bool Order)
    {
        if(!PrintHour && !PrintMinute && !PrintSecond)
        {
            return "";
        }

        String Text = "";

        if(Order)
        {
            if(PrintHour)
            {
                Text += ':';
                if (Hour < 10)
                { Text += '0'; }
                Text += String(Hour);
            }
            if(PrintMinute)
            {
                Text += ':';
                if (Minute < 10)
                { Text += '0'; }
                Text += String(Minute);
            }
            if(PrintSecond)
            {
                Text += ':';
                if (Second < 10)
                { Text += '0'; }
                Text += String(Second);
            }
        }
        else
        {
            if(PrintSecond)
            {
                Text += ':';
                if (Second < 10)
                { Text += '0'; }
                Text += String(Second);
            }
            if(PrintMinute)
            {
                Text += ':';
                if (Minute < 10)
                { Text += '0'; }
                Text += String(Minute);
            }
            if(PrintHour)
            {
                Text += ':';
                if (Hour < 10)
                { Text += '0'; }
                Text += String(Hour);
            }
        }

        return Text.substring(1);
    }

    String DateText(bool PrintYear, bool PrintMonth, bool PrintDay, bool Order)
    {
        if(!PrintYear && !PrintMonth && !PrintDay)
        {
            return "";
        }

        String Text = "";

        if(Order)
        {
            if(PrintYear)
            {
                Text += '/';
                if (Year < 10)
                { Text += '0'; }
                Text += String(Year);
            }
            if(PrintMonth)
            {
                Text += '/';
                if (Month < 10)
                { Text += '0'; }
                Text += String(Month);
            }
            if(PrintDay)
            {
                Text += '/';
                if (Day < 10)
                { Text += '0'; }
                Text += String(Day);
            }
        }
        else
        {
            if(PrintDay)
            {
                Text += '/';
                if (Day < 10)
                { Text += '0'; }
                Text += String(Day);
            }
            if(PrintMonth)
            {
                Text += '/';
                if (Month < 10)
                { Text += '0'; }
                Text += String(Month);
            }
            if(PrintYear)
            {
                Text += '/';
                if (Year < 10)
                { Text += '0'; }
                Text += String(Year);
            }
        }

        return Text.substring(1);
    }

    int WeekDay(int WeekDay, int WeekMonth, int WeekYear)
    {
        int Result = SmartWatch->rtc->getDayOfWeek(WeekDay, WeekMonth, WeekYear);
        if(Result == 0) { Result = 7; }
        return Result;
    }

    int DaysInMonth(int MonthDay, int YearDay)
    {
        if(MonthDay == 1 || MonthDay == 3 || MonthDay == 5 || MonthDay == 7 || MonthDay == 8 || MonthDay == 10 || MonthDay == 12)
        {
            return 31;
        }
        if(MonthDay == 4 || MonthDay == 6 || MonthDay == 9 || MonthDay == 11)
        {
            return 30;
        }
        if(YearDay % 4 == 0)
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
}