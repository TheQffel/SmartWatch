#include "ir.h"

#include "apis/console.h"

namespace Api_Ir
{
    IRsend Ir(TWATCH_2020_IR_PIN);

    void Setup()
    {
        bool Result = true;

        Ir.begin();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Ir initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize ir.");
        }
    }

    bool Send(String Protocol, int Length, uint64_t Code)
    {
        const unsigned char Character[] = { (char)Code };

        Protocol = (Protocol + "    ").substring(0, 4);
        
        Protocol.toUpperCase();

        bool Result = false;

        if(Protocol == "BOSE") { Ir.sendBose(Code, Length); Result = true; }
        if(Protocol == "DELO") { Ir.sendDelonghiAc(Code, Length); Result = true; }
        if(Protocol == "EPSO") { Ir.sendEpson(Code, Length); Result = true; }
        if(Protocol == "FUJI") { Ir.sendFujitsuAC(Character, Length); Result = true; }
        if(Protocol == "GORE") { Ir.sendGorenje(Code, Length); Result = true; }
        if(Protocol == "HITA") { Ir.sendHitachiAC(Character, Length); Result = true; }
        if(Protocol == "JVC ") { Ir.sendJVC(Code, Length); Result = true; }
        if(Protocol == "LG  ") { Ir.sendLG(Code, Length); Result = true; }
        if(Protocol == "MITS") { Ir.sendMitsubishi(Code, Length); Result = true; }
        if(Protocol == "NEC ") { Ir.sendNEC(Code, Length); Result = true; }
        if(Protocol == "PANA") { Ir.sendPanasonic(Code, Length); Result = true; }
        if(Protocol == "PION") { Ir.sendPioneer(Code, Length); Result = true; }
        if(Protocol == "SAMS") { Ir.sendSAMSUNG(Code, Length); Result = true; }
        if(Protocol == "SANY") { Ir.sendSanyoAc(Character, Length); Result = true; }
        if(Protocol == "SHAR") { Ir.sendSharp(Code, Length); Result = true; }
        if(Protocol == "SONY") { Ir.sendSony(Code, Length); Result = true; }
        if(Protocol == "TOSH") { Ir.sendToshibaAC(Character, Length); Result = true; }
        if(Protocol == "TOTO") { Ir.sendToto(Code, Length); Result = true; }
        if(Protocol == "WHIR") { Ir.sendWhirlpoolAC(Character, Length); Result = true; }
        if(Protocol == "YORK") { Ir.sendYork(Character, Length); Result = true; }

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Ir code sent.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Unknown ir protocol: " + Protocol);
        }

        return Result;
    }
}