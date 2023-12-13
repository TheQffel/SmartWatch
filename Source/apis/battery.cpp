#include "battery.h"

#include "apis/console.h"

namespace Api_Battery
{
    bool LastState = false;
    int BatteryLevel = -99;

    void Setup()
    {
        bool Result = true;

        SmartWatch->power->begin();
        SmartWatch->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
        SmartWatch->power->enableIRQ(AXP202_PEK_LONGPRESS_IRQ, true);
        SmartWatch->power->setChargeControlCur(300);

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Battery initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize battery.");
        }
    }

    int Percentage()
    {
        LastState = Chargeing();
        int Battery = (Voltage()-3400)/7;
        if(LastState) { Battery -= 15; }
        if(Battery > 100) { Battery = 100; }
        if(Battery < 0) { Battery = 0; }

        if(BatteryLevel < -9) { BatteryLevel = Battery; }
        if(LastState && BatteryLevel < Battery) { BatteryLevel++; }
        if(!LastState && BatteryLevel > Battery) { BatteryLevel--; }

        return BatteryLevel;
    }

    int Voltage()
    {
        return (int)SmartWatch->power->getBattVoltage();
    }

    bool Chargeing()
    {
        return SmartWatch->power->isChargeing();
    }

    void Reset()
    {
        BatteryLevel = -99;
    }
}