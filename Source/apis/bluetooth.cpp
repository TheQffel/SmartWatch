#include "bluetooth.h"

#include "apis/console.h"

namespace Api_Bluetooth
{
    bool ScanAutoConnect = false;

    void Setup()
    {
        bool Result = true;

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Bluetooth initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize bluetooth.");
        }
    }

    void Loop()
    {
        if(ScanAutoConnect)
        {

        }
    }

    bool Connected()
    {
        return btStarted();
    }

    void Connect()
    {

    }

    void Disconnect()
    {

    }

    void Autoconnect()
    {

    }

    void Toggle(bool State)
    {
        if(State)
        {
            if(btStart())
            {
                Api_Console::Log(Api_Console::LogType::Ok, "Bluetooth enabled successfully.");
            }
            else
            {
                Api_Console::Log(Api_Console::LogType::Error, "Failed to enable bluetooth.");
            }

            delay(100);
            Autoconnect();
        }
        else
        {
            Disconnect();
            delay(100);

            if(btStop())
            {
                Api_Console::Log(Api_Console::LogType::Ok, "Bluetooth disabled successfully.");
            }
            else
            {
                Api_Console::Log(Api_Console::LogType::Error, "Failed to disable bluetooth.");
            }

        }
    }

    void Main()
    {

    }
}