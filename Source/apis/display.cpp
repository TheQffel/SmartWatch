#include "display.h"

#include "apis/console.h"

namespace Api_Display
{
    uint16_t* ScreenData;
    uint8_t* ColorsData;

    int Brightness = 5;

    void Setup()
    {
        bool Result = true;

        SmartWatch->bl->begin();
        SmartWatch->bl->on();
        SetBrightness(Brightness);

        SmartWatch->tft->init();
        SmartWatch->tft->setRotation(0);
        SmartWatch->tft->setTextSize(1);
        SmartWatch->tft->setTextWrap(false, false);

        ScreenData = (uint16_t*)ps_malloc(250 * 250 * 2);
        ColorsData = (uint8_t*)ps_malloc(250 * 250 * 3);

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Display initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize display.");
        }
    }

    void Toggle(bool State)
    {
        if(State)
        {
            SmartWatch->bl->on();
            SmartWatch->displayWakeup();

            for(int i = 0; i <= 25; i++)
            {
                delay(25);
                SmartWatch->bl->adjust(i * Brightness);
            }

            Api_Console::Log(Api_Console::LogType::Info, "Display enabled at level " + String(Brightness) + '.');
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Info, "Display disabled at level " + String(Brightness) + '.');

            for(int i = 25; i >= 0; i--)
            {
                SmartWatch->bl->adjust(i * Brightness);
                delay(25);
            }
          
            SmartWatch->displaySleep();
            SmartWatch->bl->off();
        }
    }

    void Clear(uint16_t Color)
    {
        SmartWatch->tft->fillScreen(Color);
    }
    
    uint16_t ColorFromRgb(uint8_t R, uint8_t G, uint8_t B)
    {
        return SmartWatch->tft->color565(R, G, B);
    }

    void Pause()
    {
        SmartWatch->tft->readRect(0, 0, 240, 240, ScreenData);
    }

    void Resume()
    {
        SmartWatch->tft->pushRect(0, 0, 240, 240, ScreenData);
    }
    
    void DrawText(char Char, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor)
    {
        SmartWatch->tft->setTextSize(Size);
        SmartWatch->tft->setTextColor(TextColor, BackgroundColor);
        SmartWatch->tft->setCursor(X, Y);
        SmartWatch->tft->print(Char);
    }

    void DrawText(double Number, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor, int Decimals)
    {
        SmartWatch->tft->setTextSize(Size);
        SmartWatch->tft->setTextColor(TextColor, BackgroundColor);
        SmartWatch->tft->setCursor(X, Y);
        SmartWatch->tft->print(String(Number, Decimals));
    }

    void DrawText(int Number, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor)
    {
        SmartWatch->tft->setTextSize(Size);
        SmartWatch->tft->setTextColor(TextColor, BackgroundColor);
        SmartWatch->tft->setCursor(X, Y);
        SmartWatch->tft->print(String(Number));
    }

    void DrawText(String Text, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor, int LineLength)
    {
        SmartWatch->tft->setTextSize(Size);
        SmartWatch->tft->setTextColor(TextColor, BackgroundColor);

        if(LineLength < 1000)
        {
            int CurrentPosition = 0;
            int CharLimit = LineLength / (6 * Size);
            int SpaceBreak = 0;

            for (int i = 0; i < Text.length(); i++)
            {
                if((i % CharLimit) == SpaceBreak)
                {
                    if(Text[i] == ' ')
                    {
                        SpaceBreak++;

                        continue;
                    }

                    SmartWatch->tft->setCursor(X, Y + (CurrentPosition * 8 * Size));

                    CurrentPosition++;
                }

                SmartWatch->tft->print(Text[i]);
            }
        }
        else
        {
            SmartWatch->tft->setCursor(X, Y);
            SmartWatch->tft->print(Text);
        }
    }

    void DrawRectangle(int X, int Y, int W, int H, uint16_t Color, bool Fill)
    {
        if(Fill)
        {
            SmartWatch->tft->fillRect(X, Y, W, H, Color);
        }
        else
        {
            SmartWatch->tft->drawRect(X, Y, W, H, Color);
        }
    }

    void DrawBmp(String Image, int X, int Y)
    {
        if(SPIFFS.exists(Image))
        {
            fs::File BmpImage = SPIFFS.open(Image);

            BmpImage.seek(0x12);
            int ImageWidth = BmpImage.read();
            BmpImage.seek(0x16);
            int ImageHeight = BmpImage.read();
            BmpImage.seek(0x36);

            uint8_t SdBuffer[750];
            uint16_t LcdBuffer[250];

            for(int i = 0; i < ImageHeight; i++)
            {
                BmpImage.read(SdBuffer, (ImageWidth*3)+(ImageWidth%4));
                
                for(int j = 0; j < ImageWidth; j++)
                {
                    LcdBuffer[j] = ColorFromRgb(SdBuffer[(j*3)+2], SdBuffer[(j*3)+1], SdBuffer[(j*3)]);

                    if(LcdBuffer[j] == 64511) // 250, 125, 250
                    {
                        LcdBuffer[j] = SmartWatch->tft->readPixel(X+j, (ImageHeight-i)+(Y-1));
                    }
                }

                SmartWatch->tft->setAddrWindow(X, (ImageHeight-i)+(Y-1), ImageWidth, 1);
                SmartWatch->tft->pushColors(LcdBuffer, ImageWidth);
            }

            // Api_Console::Log(Api_Console::LogType::Ok, "Image displayed: " + Image);

            BmpImage.close();
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Image not found: " + Image);
        }
    }

    void SetBrightness(int Level)
    {
        Brightness = Level;
        SmartWatch->bl->adjust(Brightness * 25);
    }

    int GetBrightness()
    {
        return Brightness;
    }

    void PrintScreen()
    {
        uint16_t LcdBuffer[120];

        for (int i = 0; i < 120; i++)
        {
            for (int j = 0; j < 120; j++)
            {
                LcdBuffer[j] = SmartWatch->tft->readPixel(j, i);
            }

            SmartWatch->tft->setAddrWindow(120, 120+i, 120, 1);
            SmartWatch->tft->pushColors(LcdBuffer, 120);
        }
    }
}