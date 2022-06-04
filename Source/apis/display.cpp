#include "display.h"

namespace Api_Display
{
    void Toggle(bool State)
    {
        if(State)
        {
            for(int i = 0; i <= 25; i++)
            {
                delay(25);
                SmartWatch->bl->adjust(i*10);
            }
        }
        else
        {
            for(int i = 25; i >= 0; i--)
            {
                SmartWatch->bl->adjust(i*10);
                delay(25);
            }
        }
    }

    uint16_t ColorFromRgb(uint8_t R, uint8_t G, uint8_t B)
    {
        return SmartWatch->tft->color565(B, G, R);
    }

    void DrawText(String Text, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor)
    {
        SmartWatch->tft->setCursor(X, Y);
        SmartWatch->tft->setTextSize(Size);
        SmartWatch->tft->setTextColor(TextColor, BackgroundColor);
        SmartWatch->tft->print(Text);
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
        fs::File BmpImage = SPIFFS.open(Image);

        BmpImage.seek(0x12);
        int ImageWidth = BmpImage.read();
        BmpImage.seek(0x16);
        int ImageHeight = BmpImage.read();
        BmpImage.seek(0x36);

        uint8_t SdBuffer[720];
        uint16_t LcdBuffer[240];

        for(int i = 0; i < ImageHeight; i++)
        {
            BmpImage.read(SdBuffer, (ImageWidth*3)+(ImageWidth%4));
            
            for(int j = 0; j < ImageWidth; j++)
            {
                LcdBuffer[j] = ColorFromRgb(SdBuffer[j*3], SdBuffer[(j*3)+1], SdBuffer[(j*3)+2]);

                if(LcdBuffer[j] == 64511) // 250, 125, 250
                {
                    LcdBuffer[j] = SmartWatch->tft->readPixel(X+j, (ImageHeight-i)+(Y-1));
                }
            }

            SmartWatch->tft->setAddrWindow(X, (ImageHeight-i)+(Y-1), ImageWidth, 1);
            SmartWatch->tft->pushColors(LcdBuffer, ImageWidth);
        }

        BmpImage.close();
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