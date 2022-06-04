#include "keyboard.h"

#include "apis\display.h"
#include "apis\touch.h"

namespace Gui_Keyboard
{
    void SwitchKeyboardLayout(bool Size, bool Type)
    {
        if(Size)
        {
            if(Type)
            {
		        Api_Display::DrawBmp("/System/KeyboardNumbersUp.bmp", 0, 130);
            }
            else
            {
		        Api_Display::DrawBmp("/System/KeyboardLettersUp.bmp", 0, 130);
            }
        }
        else
        {
            if(Type)
            {
		        Api_Display::DrawBmp("/System/KeyboardNumbersDown.bmp", 0, 130);
            }
            else
            {
		        Api_Display::DrawBmp("/System/KeyboardLettersDown.bmp", 0, 130);
            }
        }
    }

    String GetInput(String Text)
    {
        String Result = "";
        char Input[128];
        int Index = 0;
        bool Done = false;

        bool CharactersSize = false;
        bool CharactersType = false;

        char Characters[] =
        {
            113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 97, 115, 100, 102, 103, 104, 106, 107, 108, 122, 120, 99, 118, 98, 110, 109, 46, 44, 32,
            81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 65, 83, 68, 70, 71, 72, 74, 75, 76, 90, 88, 67, 86, 66, 78, 77, 46, 44, 32,
            49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 64, 35, 36, 95, 38, 45, 43, 40, 41, 42, 34, 39, 58, 59, 33, 63, 92, 47, 32,
            126, 96, 124, 32, 32, 32, 247, 215, 182, 32, 163, 162, 32, 165, 94, 176, 61, 123, 125, 37, 169, 174, 32, 32, 91, 93, 60, 62, 32
        };
                
        SmartWatch->tft->fillScreen(0);
        SmartWatch->tft->setTextSize(2);
        SmartWatch->tft->textcolor = SmartWatch->tft->color565(255, 255, 255);
        SmartWatch->tft->textbgcolor = 0;

        SwitchKeyboardLayout(CharactersSize, CharactersType);

        while(!Done)
        {
            if(Api_Touch::ReadTouch())
            {
                if(!Api_Touch::Swipe && !Api_Touch::Hold)
                {
                    int Character = -1;

                    if(Api_Touch::TouchY > 132 && Api_Touch::TouchY < 159)
                    {
                        if(Api_Touch::TouchX > 0 && Api_Touch::TouchX < 24) { Character = 0; }
                        if(Api_Touch::TouchX > 24 && Api_Touch::TouchX < 48) { Character = 1; }
                        if(Api_Touch::TouchX > 48 && Api_Touch::TouchX < 72) { Character = 2; }
                        if(Api_Touch::TouchX > 72 && Api_Touch::TouchX < 96) { Character = 3; }
                        if(Api_Touch::TouchX > 96 && Api_Touch::TouchX < 120) { Character = 4; }
                        if(Api_Touch::TouchX > 120 && Api_Touch::TouchX < 144) { Character = 5; }
                        if(Api_Touch::TouchX > 144 && Api_Touch::TouchX < 168) { Character = 6; }
                        if(Api_Touch::TouchX > 168 && Api_Touch::TouchX < 192) { Character = 7; }
                        if(Api_Touch::TouchX > 192 && Api_Touch::TouchX < 216) { Character = 8; }
                        if(Api_Touch::TouchX > 216 && Api_Touch::TouchX < 240) { Character = 9; }
                    }
                    if(Api_Touch::TouchY > 159 && Api_Touch::TouchY < 186)
                    {
                        if(Api_Touch::TouchX > 12 && Api_Touch::TouchX < 36) { Character = 10; }
                        if(Api_Touch::TouchX > 36 && Api_Touch::TouchX < 60) { Character = 11; }
                        if(Api_Touch::TouchX > 60 && Api_Touch::TouchX < 84) { Character = 12; }
                        if(Api_Touch::TouchX > 84 && Api_Touch::TouchX < 108) { Character = 13; }
                        if(Api_Touch::TouchX > 108 && Api_Touch::TouchX < 132) { Character = 14; }
                        if(Api_Touch::TouchX > 132 && Api_Touch::TouchX < 156) { Character = 15; }
                        if(Api_Touch::TouchX > 156 && Api_Touch::TouchX < 180) { Character = 16; }
                        if(Api_Touch::TouchX > 180 && Api_Touch::TouchX < 204) { Character = 17; }
                        if(Api_Touch::TouchX > 204 && Api_Touch::TouchX < 228) { Character = 18; }
                    }
                    if(Api_Touch::TouchY > 186 && Api_Touch::TouchY < 213)
                    {
                        if(Api_Touch::TouchX > 36 && Api_Touch::TouchX < 60) { Character = 19; }
                        if(Api_Touch::TouchX > 60 && Api_Touch::TouchX < 84) { Character = 20; }
                        if(Api_Touch::TouchX > 84 && Api_Touch::TouchX < 108) { Character = 21; }
                        if(Api_Touch::TouchX > 108 && Api_Touch::TouchX < 132) { Character = 22; }
                        if(Api_Touch::TouchX > 132 && Api_Touch::TouchX < 156) { Character = 23; }
                        if(Api_Touch::TouchX > 156 && Api_Touch::TouchX < 180) { Character = 24; }
                        if(Api_Touch::TouchX > 180 && Api_Touch::TouchX < 204) { Character = 25; }

                        if(Api_Touch::TouchX > 0 && Api_Touch::TouchX < 36)
                        {
                            CharactersSize = !CharactersSize;
                            SwitchKeyboardLayout(CharactersSize, CharactersType);
                        }
                        if(Api_Touch::TouchX > 204 && Api_Touch::TouchX < 240)
                        {
                            Input[Index] = 32;
                            Index--;
                        }
                    }
                    if(Api_Touch::TouchY > 213 && Api_Touch::TouchY < 240)
                    {
                        if(Api_Touch::TouchX > 36 && Api_Touch::TouchX < 60) { Character = 26; }
                        if(Api_Touch::TouchX > 180 && Api_Touch::TouchX < 204) { Character = 27; }
                        if(Api_Touch::TouchX > 60 && Api_Touch::TouchX < 180) { Character = 28; }

                        if(Api_Touch::TouchX > 0 && Api_Touch::TouchX < 36)
                        {
                            CharactersType = !CharactersType;
                            SwitchKeyboardLayout(CharactersSize, CharactersType);
                        }
                        if(Api_Touch::TouchX > 204 && Api_Touch::TouchX < 240)
                        {
                            Done = true;
                        }
                    }

                    if(Character > -1 && Index < 127)
                    {
                        if(CharactersSize) { Character += 29; }
                        if(CharactersType) { Character += 58; }

                        Input[Index] = Characters[Character];
                        Index++;
                    }

                    SmartWatch->tft->fillRect(0, 0, 240, 130, 0);

                    for (int i = 0; i < Index; i++)
                    {
                        if(i % 19 == 0)
                        {
                            SmartWatch->tft->setCursor(5, 5 + i);
                        }
                        SmartWatch->tft->print(Input[i]);
                    }
                }
            }
            delay(10);
        }

        for (int i = 0; i < Index; i++)
        {
            Result += Input[i];
        }
        return Result;
    }
}