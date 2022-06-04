#include "main.h"

TTGOClass* SmartWatch = 0;
String OsVersion = "1.21.0";

String Apps[] = {"Appstore", "Calc", "Browser", "Calendar", "Camera", "Clock", /*"Desktop",*/ "Files", "Gallery", "Maps", "Music", "Notes", "Paint", "Radio", "Recorder", "Remote", "Settings", "Terminal", "Weather", ""};

int AppsNumber = 0;
int PagesNumber = 0;
int Page = 0;

// Utils:
#include "apis\display.h"
#include "apis\time.h"
#include "apis\touch.h"
#include "apis\wifi.h"

// Guis:
#include "guis\keyboard.h"

// Apps:
#include "apps\settings.h"

void sleep()
{
    Api_Wifi::Toggle(false);

    SmartWatch->rtc->syncToRtc();
    SmartWatch->power->clearIRQ();
    SmartWatch->bma->readInterrupt();

    gpio_wakeup_enable((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable((gpio_num_t)BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
    gpio_wakeup_enable((gpio_num_t)RTC_INT, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable((gpio_num_t)TOUCH_INT, GPIO_INTR_LOW_LEVEL);

    setCpuFrequencyMhz(80);
    esp_sleep_enable_gpio_wakeup();
    esp_light_sleep_start();
    setCpuFrequencyMhz(240);
    
    SmartWatch->power->clearIRQ();
    SmartWatch->bma->readInterrupt();
    SmartWatch->rtc->syncToSystem();
    
    Api_Wifi::Toggle(true);
}

void PrintDirectory(fs::File Directory)
{
    while (true)
    {
        fs::File File = Directory.openNextFile();
        if (! File)
        {
            break;
        }
        Serial.print(File.name());
        Serial.print("\t\t");
        Serial.println(File.size(), DEC);
        File.close();
    }
}

void ChangePage()
{
    if(Page > PagesNumber)
    {
        Page = 0;
    }
    if(Page < 0)
    {
        Page = PagesNumber;
    }

    SmartWatch->tft->fillRect(0, 0, 240, 35, SmartWatch->tft->color565(250-50, 250-100, 250-150));
    SmartWatch->tft->fillRect(0, 35, 240, 205, SmartWatch->tft->color565(250-0, 250-75, 250-125));
    SmartWatch->tft->textcolor = SmartWatch->tft->color565(25, 25, 25);
    SmartWatch->tft->textbgcolor = SmartWatch->tft->color565(250-0, 250-75, 250-125);
    SmartWatch->tft->setTextSize(1);

    for(int i = 0; i < 6; i++)
    {
        if(Apps[Page*6+i] == "")
        {
            break;
        }

        int PosX = 0;
        int PosY = 0;

        if(i == 0) { PosX = 20; PosY = 55; }
        if(i == 1) { PosX = 95; PosY = 55; }
        if(i == 2) { PosX = 170; PosY = 55; }
        if(i == 3) { PosX = 20; PosY = 150; }
        if(i == 4) { PosX = 95; PosY = 150; }
        if(i == 5) { PosX = 170; PosY = 150; }

        Api_Display::DrawBmp("/System/Apps/" + Apps[Page*6+i] + ".bmp", PosX, PosY);
        
        PosX += 25;
        PosY += 60;

        PosX -= Apps[Page*6+i].length()*3;
        SmartWatch->tft->drawString(Apps[Page*6+i], PosX, PosY);
    }
}

bool irq = false;

void setup()
{
    SmartWatch = TTGOClass::getWatch();
    SmartWatch->begin();

    pinMode(AXP202_INT, INPUT_PULLUP);
    pinMode(BMA423_INT1, INPUT_PULLUP);
    pinMode(RTC_INT, INPUT_PULLUP);
    pinMode(TOUCH_INT, INPUT_PULLUP);

    SmartWatch->rtc->check();
    SmartWatch->rtc->syncToSystem();

    SmartWatch->motor_begin();
    SmartWatch->motor->onec();

    SmartWatch->power->begin();
    SmartWatch->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
    SmartWatch->power->setChargeControlCur(300);
    
    SmartWatch->bma->begin();
    SmartWatch->bma->enableAccel();
    SmartWatch->bma->enableFeature(BMA423_STEP_CNTR, true);
    SmartWatch->bma->enableFeature(BMA423_TILT, true);
    SmartWatch->bma->resetStepCounter();
    SmartWatch->bma->enableTiltInterrupt();

    struct bma423_axes_remap AxelData;
    AxelData.x_axis = 0;
    AxelData.x_axis_sign = 1;
    AxelData.y_axis = 1;
    AxelData.y_axis_sign = 1;
    AxelData.z_axis = 2;
    AxelData.z_axis_sign = 1;
    SmartWatch->bma->set_remap_axes(&AxelData);

    Serial.begin(115200);
    Serial.println("Starting...");
    
    SmartWatch->openBL();
    SmartWatch->bl->adjust(100);
    SmartWatch->tft->setRotation(0);
    SmartWatch->tft->setTextSize(1);
    SmartWatch->tft->setTextWrap(false, false);

    SPIFFS.begin();

    WiFi.setHostname("KubekSzklanySmartWatch");

	delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("ESP32:"), 5, 5); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("TTGO Smart-Watch v.2020"), 100, 5);
	delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Processor:"), 5, 15); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("2x 240 Mhz"), 180, 15);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Memory:"), 5, 25); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("520 KB"), 200, 25);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Disk:"), 5, 35); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("16 MB"), 210, 35);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Display:"), 5, 45); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("Touch Screen 240 x 240"), 105, 45);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("WiFi:"), 5, 55); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("802.11 b/g/n"), 165, 55);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Bluetooth:"), 5, 65); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("BLE v. 4.2"), 180, 65);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Speakers:"), 5, 75); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("MAX98357A"), 185, 75);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Touch Sensor:"), 5, 85); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("FT6236U"), 195, 85);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Display Module:"), 5, 95); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("ST7789V"), 195, 95);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Power Sensor:"), 5, 105); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("AXP202"), 200, 105);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Clock Module:"), 5, 115); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("PCF8563"), 195, 115);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Axis Sensor:"), 5, 125); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("BMA423"), 200, 125);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Infrared Module:"), 5, 135); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("Standard Diode"), 155, 135);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 25, 25); SmartWatch->tft->drawString(F("Vibrations Sensor:"), 5, 145); delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 255, 0); SmartWatch->tft->drawString(F("Standard Motor"), 155, 145);

    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 125, 250); SmartWatch->tft->drawString(F("Bios checksum done!"), 5, 160);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 125, 250); SmartWatch->tft->drawString(F("Launching boot loader..."), 5, 170);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 125, 250); SmartWatch->tft->drawString(F("Searching for system..."), 5, 180);
    delay(250); SmartWatch->tft->textcolor = SmartWatch->tft->color565(0, 125, 250); SmartWatch->tft->drawString(F("Found: KubekSzklany OS"), 5, 190);
   
    delay(500);
    SmartWatch->tft->setTextSize(2);
    SmartWatch->tft->textcolor = SmartWatch->tft->color565(250, 175, 0);
    SmartWatch->tft->drawString(F("W E L C O M E !"), 10, 215);
    delay(500); 

    SmartWatch->tft->fillScreen(0);

    Api_Display::DrawBmp("/System/OsLogo.bmp", 60, 60);

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

    delay(2500);

    ChangePage();
}

int Timeout = 0;
bool Clock = false;

void RunApp(int AppIndex)
{
    //Appstore, Calc, Browser, Calendar, Camera, Clock, Desktop, Files, Gallery, Maps, Music, Notes, Paint, Radio, Recorder, Remote, Settings, Terminal, Weather

    switch (AppIndex)
    {
        //case 0: { App_AppStore::Main(); break; }
        //case 1: { App_Calc::Main(); break; }
        //case 2: { App_Browser::Main(); break; }
        //case 3: { App_Calendar::Main(); break; }
        case 4: { /*App_Camera::Main();*/ Api_Display::PrintScreen(); break; }
        //case 5: { App_Clock::Main(); break; }
        //case X: { App_Desktop::Main(); break; }
        //case 5: { App_Files::Main(); break; }
        //case 7: { App_Gallery::Main(); break; }
        //case 8: { App_Maps::Main(); break; }
        //case 9: { App_Music::Main(); break; }
        //case 10: { App_Notes::Main(); break; }
        //case 11: { App_Paint::Main(); break; }
        //case 12: { App_Radio::Main(); break; }
        //case 13: { App_Recorder::Main(); break; }
        //case 14: { App_Remote::Main(); break; }
        case 15: { App_Settings::Main(); break; }
        //case 16: { App_Terminal::Main(); break; }
        //case 17: { App_Weather::Main(); break; }
        default: { break; };
    }
    ChangePage();
}

void loop()
{
    if(Clock)
    {
        if(Timeout % 10 == 0)
        {
            Api_Time::Update();

            SmartWatch->tft->fillCircle(120, 120, 70, 0);

            float HourAngle = (((Api_Time::Hour + 9) % 12) * 30 * PI) / 180;
            int HourX = 120 + (40 * cos(HourAngle));
            int HourY = 120 + (40 * sin(HourAngle));

            float MinuteAngle = (((Api_Time::Minute + 45) % 60) * 6 * PI) / 180;
            int MinuteX = 120 + (60 * cos(MinuteAngle));
            int MinuteY = 120 + (60 * sin(MinuteAngle));

            float SecondAngle = (((Api_Time::Second + 45) % 60) * 6 * PI) / 180;
            int SecondX = 120 + (65 * cos(SecondAngle));
            int SecondY = 120 + (65 * sin(SecondAngle));

            SmartWatch->tft->drawLine(120, 120, HourX, HourY, SmartWatch->tft->color565(250, 250, 250));
            SmartWatch->tft->drawLine(120, 120, MinuteX, MinuteY, SmartWatch->tft->color565(250, 250, 250));
            SmartWatch->tft->drawLine(120, 120, SecondX, SecondY, SmartWatch->tft->color565(250, 0, 0));
        }

        if(Api_Touch::ReadTouch())
        {
            Clock = false;
            ChangePage();
        }
    }
    else
    {
        if (Api_Touch::ReadTouch())
        {
            Timeout = 0;

            if(Api_Touch::Swipe)
            {
                if(Api_Touch::SwipeX + 100 < Api_Touch::TouchX)
                {
                    Page++;
                    ChangePage();
                }
                if(Api_Touch::SwipeX - 100 > Api_Touch::TouchX)
                {
                    Page--;
                    ChangePage();
                }
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

                if(App > -1)
                {
                    RunApp(App + 6 * Page);
                }
            }
        }

        Api_Time::Update();

        String Text = "";

        if(Api_Time::Hour < 10) { Text += "0"; }
        Text += Api_Time::Hour;
        Text += ":";
        if(Api_Time::Minute < 10) { Text += "0"; }
        Text += Api_Time::Minute;
        /*Text += ":";
        if(Second < 10) { Text += "0"; }
        Text += Second;
        Text += " ";
        if(Day < 10) { Text += "0"; }
        Text += Day;
        Text += "-";
        if(Month < 10) { Text += "0"; }
        Text += Month;
        Text += "-";
        Text += Year;*/
        Text += "    ";
        if(btStarted())
        {
            Text += "B  ";
        }
        else
        {
            Text += "   ";
        }
        if(WiFi.status() == WL_CONNECTED)
        {
            Text += "W  ";
        }
        else
        {
            Text += "   ";
        }
        Text += (SmartWatch->power->getBattPercentage());
        Text += "%";

        SmartWatch->tft->setTextSize(2);
        SmartWatch->tft->textcolor = SmartWatch->tft->color565(250, 250, 250);
        SmartWatch->tft->textbgcolor = SmartWatch->tft->color565(250-50, 250-100, 250-150);
        SmartWatch->tft->drawString(Text, 10, 10);

    }
    
    delay(100);

    Timeout++;

    if(Timeout > 250)
    {
        Api_Display::Toggle(false);
        sleep();
        Clock = true;
        SmartWatch->tft->fillScreen(0);
        Api_Display::DrawBmp("/System/Clock.bmp", 0, 0);
        Api_Display::Toggle(true);
        Timeout = 0;
    }
}