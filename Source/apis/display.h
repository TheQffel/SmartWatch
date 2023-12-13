#include "main.h"

namespace Api_Display
{
    void Setup();
    void Toggle(bool State);
    void Pause();
    void Resume();
    void Clear(uint16_t Color = 0);
    uint16_t ColorFromRgb(uint8_t R, uint8_t G, uint8_t B);
    void DrawText(char Char, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor);
    void DrawText(int Number, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor);
    void DrawText(double Number, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor, int Decimals = 0);
    void DrawText(String Text, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor, int LineLength = 1000);
    void DrawRectangle(int X, int Y, int W, int H, uint16_t Color, bool Fill = true);
    void DrawBmp(String Image, int X, int Y);
    void SetBrightness(int Brightness);
    int GetBrightness();
    void PrintScreen();
}
