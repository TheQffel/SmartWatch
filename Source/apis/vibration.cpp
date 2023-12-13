#include "vibration.h"

#include "apis/console.h"

namespace Api_Vibration
{
    void Setup()
    {
        bool Result = true;

        SmartWatch->motor_begin();
        SmartWatch->motor->onec();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Motor initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize motor.");
        }
    }

    void Vibrate()
    {
        SmartWatch->motor->onec();
    }
}