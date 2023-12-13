#include "console.h"

#include "apis/time.h"

namespace Api_Console
{
    char* Logs;

    void Setup()
    {
        Serial.begin(9600);

        Logs = (char*)ps_malloc(25 * 65);

        for(int i = 0; i < 10; i++)
        {
            Log(LogType::Other, "");
        }

        Log(LogType::Ok, "Console initialized sucessfully.");
    }

    int Color(int Index)
    {
        Index = Index * 65;

        int Result = Color_White_Medium; // Color_Grey_Medium;
        if(Logs[Index] == Api_Console::LogType::Error) { Result = Color_Red_Medium; }
        if(Logs[Index] == Api_Console::LogType::Warning) { Result = Color_Yellow_Medium; }
        if(Logs[Index] == Api_Console::LogType::Ok) { Result = Color_Green_Medium; }
        if(Logs[Index] == Api_Console::LogType::Info) { Result = Color_Blue_Light; }

        return Result;
    }

    String Message(int Index, bool DateTime)
    {
        Index = (Index * 65) + 1;

        String Result = "";

        for (int i = 0; i < 64; i++)
        {
           Result += Logs[Index + i];
        }

        if(!DateTime)
        {
            Result = Result.substring(20);
        }

        Result.trim();
        
        return Result;
    }

    void Log(LogType Type, String Message)
    {
        Message.trim();

        if(Api_Time::Year > 2000)
        {
            Api_Time::Update(true);
        }

        int Index = (25 * 65);

        String Date = String(1000000 + ((Api_Time::Year % 100) * 10000) + (Api_Time::Month * 100) + (Api_Time::Day * 1));
        String Time = String(1000000 + (Api_Time::Hour * 10000) + (Api_Time::Minute * 100) + (Api_Time::Second * 1));

        for (int i = 65; i < Index; i++)
        {
            Logs[i - 65] = Logs[i];
        }

        Index = Index - 65;

        for (int i = 0; i < 65; i++)
        {
            Logs[Index + i] = ' ';
        }

        Logs[Index] = Type;

        Logs[Index +  1] = '[';
        Logs[Index +  2] = Date[1];
        Logs[Index +  3] = Date[2];
        Logs[Index +  4] = '/';
        Logs[Index +  5] = Date[3];
        Logs[Index +  6] = Date[4];
        Logs[Index +  7] = '/';
        Logs[Index +  8] = Date[5];
        Logs[Index +  9] = Date[6];
        Logs[Index + 10] = ' ';
        Logs[Index + 11] = Time[1];
        Logs[Index + 12] = Time[2];
        Logs[Index + 13] = ':';
        Logs[Index + 14] = Time[3];
        Logs[Index + 15] = Time[4];
        Logs[Index + 16] = ':';
        Logs[Index + 17] = Time[5];
        Logs[Index + 18] = Time[6];
        Logs[Index + 19] = ']';
        Logs[Index + 20] = ' ';

        Index = Index + 21;

        int Length = Message.length();
        if(Length > 44) { Length = 44; }

        for (int i = 0; i < Length; i++)
        {
            Logs[Index + i] = Message[i];
        }
        
        Serial.println(Message);
    }
}