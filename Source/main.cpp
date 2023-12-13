#include "main.h"

TTGOClass* SmartWatch = 0;
String OsVersion = "1.24.0";

String Apps[] = { "Appstore", "Browser", "Calc", "Calendar", "Camera", "Clock", "Crypto", "Desktop", "Discord", "Files", "Gallery", "Maps", "Mesenger", "Music", "Notes", "Paint", "Radio", "Recorder", "Remote", "Settings", "Spotify", "Steam", "Terminal", "Weather", "" };

String Icon1 = "";
String Icon2 = "";
String Icon3 = "";
String Icon4 = "";
String Icon5 = "";

bool WifiState = false;
bool BluetoothState = false;
int AppsNumber = 0;
int PagesNumber = 0;
bool Panel = false;
int Timeout = 0;
int Page = 0;

// Utils:
#include "apis/accel.h"
#include "apis/battery.h"
#include "apis/bios.h"
#include "apis/bluetooth.h"
#include "apis/console.h"
#include "apis/display.h"
#include "apis/gps.h"
#include "apis/ir.h"
#include "apis/settings.h"
#include "apis/time.h"
#include "apis/touch.h"
#include "apis/vibration.h"
#include "apis/wifi.h"

// Guis:
#include "guis/alert.h"
#include "guis/keyboard.h"

// Apps:
#include "apps/appstore.h"
#include "apps/browser.h"
#include "apps/calc.h"
#include "apps/calendar.h"
#include "apps/camera.h"
#include "apps/clock.h"
#include "apps/crypto.h"
#include "apps/desktop.h"
#include "apps/discord.h"
#include "apps/files.h"
#include "apps/gallery.h"
#include "apps/maps.h"
#include "apps/mesenger.h"
#include "apps/music.h"
#include "apps/notes.h"
#include "apps/paint.h"
#include "apps/radio.h"
#include "apps/recorder.h"
#include "apps/remote.h"
#include "apps/settings.h"
#include "apps/spotify.h"
#include "apps/steam.h"
#include "apps/terminal.h"
#include "apps/weather.h"

void DisplayIcons(String IconA, String IconB, String IconC, String IconD, String IconE, uint16_t Color, bool Force = false)
{
    if(Force)
    {
        Icon1 = "1";
        Icon2 = "2";
        Icon3 = "3";
        Icon4 = "4";
        Icon5 = "5";
    }

    if(Icon1 != IconA)
    {
        Icon1 = IconA;

        if(Icon1.length() > 1)
        {
            Api_Display::DrawBmp("/System/Icons/" + Icon1 + ".bmp", 90, 5);
        }
        else
        {
            Api_Display::DrawRectangle(90, 5, 25, 25, Color);
        }
    }
    
    if(Icon2 != IconB)
    {
        Icon2 = IconB;

        if(Icon2.length() > 1)
        {
            Api_Display::DrawBmp("/System/Icons/" + Icon2 + ".bmp", 120, 5);
        }
        else
        {
            Api_Display::DrawRectangle(120, 5, 25, 25, Color);
        }
    }

    if(Icon3 != IconC)
    {
        Icon3 = IconC;

        if(Icon3.length() > 1)
        {
            Api_Display::DrawBmp("/System/Icons/" + Icon3 + ".bmp", 150, 5);
        }
        else
        {
            Api_Display::DrawRectangle(150, 5, 25, 25, Color);
        }
    }

    if(Icon4 != IconD)
    {
        Icon4 = IconD;

        if(Icon4.length() > 1)
        {
            Api_Display::DrawBmp("/System/Icons/" + Icon4 + ".bmp", 180, 5);
        }
        else
        {
            Api_Display::DrawRectangle(180, 5, 25, 25, Color);
        }
    }

    if(Icon5 != IconE)
    {
        Icon5 = IconE;

        if(Icon5.length() > 1)
        {
            Api_Display::DrawBmp("/System/Icons/" + Icon5 + ".bmp", 210, 5);
        }
        else
        {
            Api_Display::DrawRectangle(210, 5, 25, 25, Color);
        }
    }
}

void ChangePage(bool OnlyIcons)
{
    Panel = false;

    if(Page > PagesNumber) { Page = 0; }
    if(Page < 0) { Page = PagesNumber; }

    if(!OnlyIcons)
    {
        Api_Display::DrawRectangle(0, 0, 240, 35, Color_Brown_Medium);
        Api_Display::DrawRectangle(0, 35, 240, 205, Color_Brown_Light);
    }

    if((Page * 6) + 0 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 0];
        Api_Display::DrawRectangle(20, 55, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 20, 55);
        Api_Display::DrawText(Name, 45 - (Name.length() * 3), 115, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(20, 55, 50, 70, Color_Brown_Light);
    }
    
    if((Page * 6) + 1 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 1];
        Api_Display::DrawRectangle(95, 55, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 95, 55);
        Api_Display::DrawText(Name, 120 - (Name.length() * 3), 115, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(95, 55, 50, 70, Color_Brown_Light);
    }
    
    if((Page * 6) + 2 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 2];
        Api_Display::DrawRectangle(170, 55, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 170, 55);
        Api_Display::DrawText(Name, 195 - (Name.length() * 3), 115, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(170, 55, 50, 70, Color_Brown_Light);
    }

    if((Page * 6) + 3 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 3];
        Api_Display::DrawRectangle(20, 150, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 20, 150);
        Api_Display::DrawText(Name, 45 - (Name.length() * 3), 210, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(20, 150, 50, 70, Color_Brown_Light);
    }
    
    if((Page * 6) + 4 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 4];
        Api_Display::DrawRectangle(95, 150, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 95, 150);
        Api_Display::DrawText(Name, 120 - (Name.length() * 3), 210, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(95, 150, 50, 70, Color_Brown_Light);
    }
    
    if((Page * 6) + 5 < AppsNumber)
    {
        String Name = Apps[Page * 6 + 5];
        Api_Display::DrawRectangle(170, 150, 50, 70, Color_Brown_Light);
        Api_Display::DrawBmp("/System/Apps/" + Name + ".bmp", 170, 150);
        Api_Display::DrawText(Name, 195 - (Name.length() * 3), 210, 1, Color_Black_Dark, Color_Brown_Light);
    }
    else
    {
        Api_Display::DrawRectangle(170, 150, 50, 70, Color_Brown_Light);
    }

    if(!OnlyIcons)
    {
        DisplayIcons(Icon1, Icon2, Icon3, Icon4, Icon5, Color_Brown_Medium, true);
    }
}

void DisplayCenter(bool OnlyIcons)
{
    Panel = true;

    if(!OnlyIcons)
    {
        Api_Display::DrawRectangle(0, 0, 240, 35, Color_Black_Medium);
        Api_Display::DrawRectangle(0, 35, 240, 205, Color_Black_Light);
    }
    
    int Pos = 20 + (Api_Display::GetBrightness() * 20);
    Api_Display::DrawRectangle(0, 160, 240, 80, Color_Black_Light);
    Api_Display::DrawRectangle(40, 190, 160, 15, Color_White_Medium);
    SmartWatch->tft->fillCircle(40, 197, 7, Color_White_Medium);
    SmartWatch->tft->fillCircle(200, 197, 7, Color_White_Medium);
    SmartWatch->tft->fillCircle(Pos, 197, 17, Color_Grey_Light);

    if(WifiState)
    {
        Api_Display::DrawBmp("/System/Icons/WifiOn.bmp", 25, 55);
    }
    else
    {
        Api_Display::DrawBmp("/System/Icons/WifiOff.bmp", 25, 55);
    }

    if(BluetoothState)
    {
        Api_Display::DrawBmp("/System/Icons/BtOn.bmp", 135, 55);
    }
    else
    {
        Api_Display::DrawBmp("/System/Icons/BtOff.bmp", 135, 55);
    }

    if(!OnlyIcons)
    {
        DisplayIcons(Icon1, Icon2, Icon3, Icon4, Icon5, Color_Black_Medium, true);
    }
}

void setup()
{
    Api_Console::Setup();
    Api_Bios::Setup();
    Api_Time::Setup();
    Api_Settings::Setup();
    Api_Battery::Setup();
    Api_Display::Setup();
    Api_Touch::Setup();
    Api_Accel::Setup();
    Api_Gps::Setup();
    Api_Ir::Setup();
    Api_Wifi::Setup();
    Api_Bluetooth::Setup();
    Api_Vibration::Setup();

    Api_Bios::Checksum(1000);
    Api_Bios::Logo(5000);

    for (int i = 0; i < 111; i++)
    {
        if(Apps[i] == "")
        {
            AppsNumber = i;
            break;
        }
    }

    PagesNumber = AppsNumber/6;
    if(AppsNumber%6 == 0)
    {
        PagesNumber--;
    }

    Api_Console::Log(Api_Console::LogType::Info, "Smart watch setup done.");

    Api_Wifi::Toggle(WifiState);
    Api_Bluetooth::Toggle(BluetoothState);

    ChangePage(false);
}

void loop()
{
    if (Api_Touch::ReadTouch())
    {
        Timeout = 0;

        if(Api_Touch::Swipe)
        {
            if(Api_Touch::SwipeHorizontal)
            {
                if(Panel)
                {
                    if(Api_Touch::SwipeY > 180 && Api_Touch::SwipeY < 220)
                    {
                        if(Api_Touch::SwipeX > 30 && Api_Touch::SwipeX < 50) { Api_Display::SetBrightness(1); }
                        if(Api_Touch::SwipeX > 50 && Api_Touch::SwipeX < 70) { Api_Display::SetBrightness(2); }
                        if(Api_Touch::SwipeX > 70 && Api_Touch::SwipeX < 90) { Api_Display::SetBrightness(3); }
                        if(Api_Touch::SwipeX > 90 && Api_Touch::SwipeX < 110) { Api_Display::SetBrightness(4); }
                        if(Api_Touch::SwipeX > 110 && Api_Touch::SwipeX < 130) { Api_Display::SetBrightness(5); }
                        if(Api_Touch::SwipeX > 130 && Api_Touch::SwipeX < 150) { Api_Display::SetBrightness(6); }
                        if(Api_Touch::SwipeX > 150 && Api_Touch::SwipeX < 170) { Api_Display::SetBrightness(7); }
                        if(Api_Touch::SwipeX > 170 && Api_Touch::SwipeX < 190) { Api_Display::SetBrightness(8); }
                        if(Api_Touch::SwipeX > 190 && Api_Touch::SwipeX < 210) { Api_Display::SetBrightness(9); }
                    }

                    DisplayCenter(true);
                }
                else
                {
                    if(Api_Touch::TouchX > Api_Touch::SwipeX)
                    {
                        Page++;
                        ChangePage(true);
                    }
                    if(Api_Touch::TouchX < Api_Touch::SwipeX)
                    {
                        Page--;
                        ChangePage(true);
                    }
                }
            }
            if(Api_Touch::SwipeVertical)
            {
                if(Panel)
                {
                    ChangePage(false);
                }
                else
                {
                    DisplayCenter(false);
                }
            }
        }
        else
        {
            if(Panel)
            {
                bool Mode = true;

                if(Api_Touch::TouchX > 20 && Api_Touch::TouchX < 110 && Api_Touch::TouchY > 50 && Api_Touch::TouchY < 130)
                {
                    if(Api_Touch::Click)
                    {
                        WifiState = !WifiState;

                        if(WifiState && BluetoothState)
                        {
                            Gui_Alert::ShowOk("Error", "You cannot use    WiFi and BlueTooth    at the same time.");

                            WifiState = !WifiState;
                        }
                        else
                        {
                            Api_Wifi::Toggle(WifiState);
                        }
                    }
                    
                    if(Api_Touch::Hold)
                    {
                        Mode = false;
                        
                        Api_Wifi::Main();
                    }
                }

                if(Api_Touch::TouchX > 130 && Api_Touch::TouchX < 220 && Api_Touch::TouchY > 50 && Api_Touch::TouchY < 130)
                {
                    if(Api_Touch::Click)
                    {
                        BluetoothState = !BluetoothState;

                        if(WifiState && BluetoothState)
                        {
                            Gui_Alert::ShowOk("Error", "You cannot use    WiFi and BlueTooth    at the same time.");

                            BluetoothState = !BluetoothState;
                        }
                        else
                        {
                            Api_Bluetooth::Toggle(BluetoothState);
                        }
                    }

                    if(Api_Touch::Hold)
                    {
                        Mode = false;

                        Api_Bluetooth::Main();
                    }
                }

                if(Api_Touch::TouchY > 180 && Api_Touch::TouchY < 220)
                {
                    if(Api_Touch::TouchX > 30 && Api_Touch::TouchX < 50) { Api_Display::SetBrightness(1); }
                    if(Api_Touch::TouchX > 50 && Api_Touch::TouchX < 70) { Api_Display::SetBrightness(2); }
                    if(Api_Touch::TouchX > 70 && Api_Touch::TouchX < 90) { Api_Display::SetBrightness(3); }
                    if(Api_Touch::TouchX > 90 && Api_Touch::TouchX < 110) { Api_Display::SetBrightness(4); }
                    if(Api_Touch::TouchX > 110 && Api_Touch::TouchX < 130) { Api_Display::SetBrightness(5); }
                    if(Api_Touch::TouchX > 130 && Api_Touch::TouchX < 150) { Api_Display::SetBrightness(6); }
                    if(Api_Touch::TouchX > 150 && Api_Touch::TouchX < 170) { Api_Display::SetBrightness(7); }
                    if(Api_Touch::TouchX > 170 && Api_Touch::TouchX < 190) { Api_Display::SetBrightness(8); }
                    if(Api_Touch::TouchX > 190 && Api_Touch::TouchX < 210) { Api_Display::SetBrightness(9); }
                }

                DisplayCenter(Mode);
            }
            else
            {
                int App = -1;

                if(Api_Touch::TouchX > 15 && Api_Touch::TouchX < 75 && Api_Touch::TouchY > 50 && Api_Touch::TouchY < 120) { App = 0; }
                if(Api_Touch::TouchX > 90 && Api_Touch::TouchX < 150 && Api_Touch::TouchY > 50 && Api_Touch::TouchY < 120) { App = 1; }
                if(Api_Touch::TouchX > 165 && Api_Touch::TouchX < 225 && Api_Touch::TouchY > 50 && Api_Touch::TouchY < 120) { App = 2; }
                if(Api_Touch::TouchX > 15 && Api_Touch::TouchX < 75 && Api_Touch::TouchY > 145 && Api_Touch::TouchY < 215) { App = 3; }
                if(Api_Touch::TouchX > 90 && Api_Touch::TouchX < 150 && Api_Touch::TouchY > 145 && Api_Touch::TouchY < 215) { App = 4; }
                if(Api_Touch::TouchX > 165 && Api_Touch::TouchX < 225 && Api_Touch::TouchY > 145 && Api_Touch::TouchY < 215) { App = 5; }

                if(App > -1 && App < AppsNumber)
                {
                    Api_Console::Log(Api_Console::LogType::Info, "App launched: " + Apps[App + (6 * Page)]);

                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Appstore")) { App_Appstore::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Browser")) { App_Browser::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Calc")) { App_Calc::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Calendar")) { App_Calendar::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Camera")) { App_Camera::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Clock")) { App_Clock::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Crypto")) { App_Crypto::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Desktop")) { App_Desktop::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Discord")) { App_Discord::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Files")) { App_Files::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Gallery")) { App_Gallery::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Maps")) { App_Maps::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Mesenger")) { App_Mesenger::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Music")) { App_Music::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Notes")) { App_Notes::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Paint")) { App_Paint::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Radio")) { App_Radio::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Recorder")) { App_Recorder::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Remote")) { App_Remote::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Settings")) { App_Settings::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Spotify")) { App_Spotify::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Steam")) { App_Steam::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Terminal")) { App_Terminal::Main(); }
                    if(Apps[App + (6 * Page)].equalsIgnoreCase("Weather")) { App_Weather::Main(); }

                    Api_Console::Log(Api_Console::LogType::Info, "Back to main menu.");
                    
                    ChangePage(false);
                }
            }
        }
    }

    String IconWifi = "";
    String IconBluetooth = "";
    String IconBattery = "";

    if(WifiState)
    {
        if(Api_Wifi::Connected()) { IconWifi = "WifiYes"; }
        else { IconWifi = "WifiNo"; }
    }

    if(BluetoothState)
    {
        if(Api_Bluetooth::Connected()) { IconBluetooth = "BtYes"; }
        else { IconBluetooth = "BtNo"; }
    }

    int Percentage = Api_Battery::Percentage();

    if(Api_Battery::Chargeing())
    {
        IconBattery = "ChargeNormal";
        if(Percentage < 10) { IconBattery = "ChargeEmpty"; }
        if(Percentage > 90) { IconBattery = "ChargeFull";  }
    }
    else
    {
        IconBattery = "Battery";
        if(Percentage > 10) { IconBattery = "BatteryEmpty"; }
        if(Percentage > 30) { IconBattery = "BatteryLow"; }
        if(Percentage > 50) { IconBattery = "BatteryMedium"; }
        if(Percentage > 70) { IconBattery = "BatteryHigh"; }
        if(Percentage > 90) { IconBattery = "BatteryFull"; }
    }

    Api_Time::Update();

    String Text = Api_Time::TimeText(true, true, false, true);

    if(Panel)
    {
        Api_Display::DrawText(Text, 10, 10, 2, Color_White_Light, Color_Black_Medium);
        DisplayIcons("", "", IconBluetooth, IconWifi, IconBattery, Color_Black_Medium);
    }
    else
    {
        Api_Display::DrawText(Text, 10, 10, 2, Color_White_Light, Color_Brown_Medium);
        DisplayIcons("", "", IconBluetooth, IconWifi, IconBattery, Color_Brown_Medium);
    }

    delay(50);

    if(WifiState) { Api_Wifi::Loop(); }
    if(BluetoothState) { Api_Bluetooth::Loop(); }

    delay(50);

    if(Timeout++ > 500 || Api_Touch::ReadButton())
    {
        Icon1 = "";
        Icon2 = "";
        Icon3 = "";
        Icon4 = "";
        Icon5 = "";

        Api_Wifi::Toggle(false);
        Api_Bluetooth::Toggle(false);

        App_Clock::Main(true);
        ChangePage(false);

        Api_Wifi::Toggle(WifiState);
        Api_Bluetooth::Toggle(BluetoothState);

        Timeout = 0;
    }
}