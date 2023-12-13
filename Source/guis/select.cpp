#include "select.h"

#include "apis/console.h"
#include "apis/display.h"
#include "apis/touch.h"

namespace Gui_Select
{
    String Items[] = 
    {
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", 
    };

    int Index = 0;
    int Total = 0;
    int Selected = 0;

    void Clear()
    {
        Index = 0;
        Total = 0;
        Selected = -1;
    }

    void Item(String Value)
    {
        if(Total < 100)
        {
            Items[Total] = Value;
            Total++;
        }
    }

    void Display()
    {
        if(Index > Total - 6) { Index = Total - 5; }
        if(Index < 0) { Index = 0; }

        if(Total > 0)
        {
            Api_Display::DrawRectangle(5, 5, 190, 42, Color_Grey_Medium);
            Api_Display::DrawText(Items[Index + 0], 10, 10, 3, Color_White_Medium, Color_Grey_Medium);
        }
        
        if(Total > 1)
        {
            Api_Display::DrawRectangle(5, 52, 190, 42, Color_Grey_Medium);
            Api_Display::DrawText(Items[Index + 1], 10, 57, 3, Color_White_Medium, Color_Grey_Medium);
        }
        
        if(Total > 2)
        {
            Api_Display::DrawRectangle(5, 99, 190, 42, Color_Grey_Medium);
            Api_Display::DrawText(Items[Index + 2], 10, 104, 3, Color_White_Medium, Color_Grey_Medium);
        }
        
        if(Total > 3)
        {
            Api_Display::DrawRectangle(5, 146, 190, 42, Color_Grey_Medium);
            Api_Display::DrawText(Items[Index + 3], 10, 151, 3, Color_White_Medium, Color_Grey_Medium);
        }
        
        if(Total > 4)
        {
            Api_Display::DrawRectangle(5, 193, 190, 42, Color_Grey_Medium);
            Api_Display::DrawText(Items[Index + 4], 10, 198, 3, Color_White_Medium, Color_Grey_Medium);
        }
    }
    
    String Show(String DefaultValue)
    {
        int Search = -1;

        if(DefaultValue != "")
        {
            for (int i = 0; i < Total; i++)
            {
                if(Items[i] == DefaultValue)
                {
                    Search = i;
                }
            }

            if(Search < 0)
            {
                Search = 0;

                for (int i = 0; i < Total; i++)
                {
                    String Value = Items[i];

                    while(Value.length() < DefaultValue.length()) { Value += ""; }

                    Value = Value.substring(0, DefaultValue.length());

                    Value.toUpperCase();

                    DefaultValue.toUpperCase();

                    if(Value == DefaultValue)
                    {
                        Search = i;
                    }
                }
            }
        }
        
        int Result = Show(Search);

        if(Selected < 0) { return ""; }

        return Items[Result];
    }

    int Show(int DefaultIndex)
    {
        Index = 0;
        Selected = -1;

        if(DefaultIndex >= 0 && DefaultIndex <= Total - 6)
        {
            Index = DefaultIndex;
        }

        bool Done = false;

        Api_Display::Pause();

        Api_Display::Clear(Color_Black_Medium);

        Api_Display::DrawRectangle(200, 5, 35, 54, Color_White_Medium);
        Api_Display::DrawRectangle(200, 64, 35, 53, Color_White_Medium);
        Api_Display::DrawRectangle(200, 123, 35, 53, Color_White_Medium);
        Api_Display::DrawRectangle(200, 181, 35, 54, Color_White_Medium);

        Display();

        while(!Done)
        {
            if(Api_Touch::ReadTouch())
            {
                if(Api_Touch::Click)
                {
                    if(Api_Touch::TouchX > 5 && Api_Touch::TouchX < 195)
                    {
                        if(Api_Touch::TouchY > 5 && Api_Touch::TouchY < 47)
                        {
                            if(Total > 0) { Selected = Index + 0; Done = true; }
                        }

                        if(Api_Touch::TouchY > 52 && Api_Touch::TouchY < 94)
                        {
                            if(Total > 1) { Selected = Index + 1; Done = true; }
                        }

                        if(Api_Touch::TouchY > 99 && Api_Touch::TouchY < 141)
                        {
                            if(Total > 2) { Selected = Index + 2; Done = true; }
                        }

                        if(Api_Touch::TouchY > 146 && Api_Touch::TouchY < 188)
                        {
                            if(Total > 3) { Selected = Index + 3; Done = true; }
                        }

                        if(Api_Touch::TouchY > 193 && Api_Touch::TouchY < 235)
                        {
                            if(Total > 4) { Selected = Index + 4; Done = true; }
                        }
                    }

                    if(Api_Touch::TouchX > 200 && Api_Touch::TouchX < 235)
                    {
                        if(Api_Touch::TouchY > 5 && Api_Touch::TouchY < 59)
                        {
                            Index -= 5;
                        }
                        
                        if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 117)
                        {
                            Index--;
                        }
                        
                        if(Api_Touch::TouchY > 123 && Api_Touch::TouchY < 176)
                        {
                            Index++;
                        }
                        
                        if(Api_Touch::TouchY > 181 && Api_Touch::TouchY < 235)
                        {
                            Index += 5;
                        }

                        Display();
                    }
                }
            }

            if(Api_Touch::ReadButton())
            {
                Done = true;
            }

            delay(10);
        }

        Api_Display::Resume();

        Api_Console::Log(Api_Console::LogType::Info, "Box displayed. Selected: " + String(Selected));

        return Selected;
    }
}