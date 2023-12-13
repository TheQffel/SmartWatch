#include "bios.h"

#include "apis/console.h"
#include "apis/display.h"

namespace Api_Bios
{
    void Setup()
    {
        SmartWatch = TTGOClass::getWatch();
        SmartWatch->begin();

        pinMode(AXP202_INT, INPUT_PULLUP);
        pinMode(BMA423_INT1, INPUT_PULLUP);
        pinMode(RTC_INT, INPUT_PULLUP);
        pinMode(TOUCH_INT, INPUT_PULLUP);

        bool Result = SPIFFS.begin();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Bios initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize bios.");
        }
    }

    void Checksum(int Sleep)
    {
        Api_Display::Clear();

        delay(100);
        
        Api_Display::DrawText(F("ESP32:"), 5, 5, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("TTGO Smart-Watch v.2023"), 100, 5, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Processor:"), 5, 15, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("2x 240 Mhz"), 180, 15, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Memory:"), 5, 25, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("512 KB"), 205, 25, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Disk:"), 5, 35, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("16 MB"), 210, 35, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Display:"), 5, 45, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("Touch Screen 240 x 240"), 105, 45, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("WiFi:"), 5, 55, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("802.11 b/g/n"), 165, 55, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Bluetooth:"), 5, 65, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("BLE v. 4.2"), 180, 65, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Speakers:"), 5, 75, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("MAX98357A"), 185, 75, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Touch Sensor:"), 5, 85, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("FT6236U"), 195, 85, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Display Module:"), 5, 95, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("ST7789V"), 195, 95, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Power Sensor:"), 5, 105, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("AXP202"), 200, 105, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Clock Module:"), 5, 115, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("PCF8563"), 195, 115, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Axis Sensor:"), 5, 125, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("BMA423"), 200, 125, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Infrared Module:"), 5, 135, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("Standard Diode"), 155, 135, 1, Color_Green_Medium, Color_Black_Dark);
        
        delay(100);
        
        Api_Display::DrawText(F("Vibrations Sensor:"), 5, 145, 1, Color_Red_Medium, Color_Black_Dark);
        Api_Display::DrawText(F("Standard Motor"), 155, 145, 1, Color_Green_Medium, Color_Black_Dark);

        delay(250);
        
        Api_Display::DrawText(F("Bios checksum done!"), 5, 160, 1, Color_Blue_Light, Color_Black_Dark);
        
        delay(250);
        
        Api_Display::DrawText(F("Launching boot loader..."), 5, 170, 1, Color_Blue_Light, Color_Black_Dark);
        
        delay(250);
        
        Api_Display::DrawText(F("Searching for system..."), 5, 180, 1, Color_Blue_Light, Color_Black_Dark);
        
        delay(250);
        
        Api_Display::DrawText(F("Found: KubekSzklany OS"), 5, 190, 1, Color_Blue_Light, Color_Black_Dark);
    
        delay(Sleep/2);
        
        Api_Display::DrawText(F("W E L C O M E !"), 20, 215, 2, Color_Yellow_Dark, Color_Black_Dark);
        
        delay(Sleep); 
        
        Api_Display::Clear();
    }

    void Logo(int Sleep)
    {
        Api_Display::Clear();

        Api_Display::DrawBmp("/System/OsLogo.bmp", 60, 60);

        delay(Sleep);

        Api_Display::Clear();
    }
}