#include "main.h"

namespace Api_Display
{
    void Toggle(bool State);
    uint16_t ColorFromRgb(uint8_t R, uint8_t G, uint8_t B);
    void DrawText(String Text, int X, int Y, int Size, uint16_t TextColor, uint16_t BackgroundColor);
    void DrawRectangle(int X, int Y, int W, int H, uint16_t Color, bool Fill);
    void DrawBmp(String Image, int X, int Y);
    void PrintScreen();
}
