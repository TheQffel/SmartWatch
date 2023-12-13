#include "alert.h"

#include "apis/console.h"
#include "apis/display.h"
#include "apis/touch.h"

namespace Gui_Alert
{
    bool ShowYesNo(String Title, String Message)
    {
        Api_Display::Pause();

        Api_Display::DrawRectangle(10, 40, 220, 30, Api_Display::ColorFromRgb(75, 50, 25));
        Api_Display::DrawRectangle(10, 70, 220, 130, Api_Display::ColorFromRgb(250, 200, 150));

        Api_Display::DrawText(Title, 14, 44, 3, Api_Display::ColorFromRgb(250, 250, 250), Api_Display::ColorFromRgb(75, 50, 25));
        Api_Display::DrawText(Message, 12, 72, 2, Api_Display::ColorFromRgb(25, 25, 25), Api_Display::ColorFromRgb(250, 200, 150), 218);

        Api_Display::DrawRectangle(70, 170, 40, 20, Api_Display::ColorFromRgb(75, 50, 25), false);
        Api_Display::DrawText("YES", 72, 173, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(250, 200, 150));

        Api_Display::DrawRectangle(130, 170, 40, 20, Api_Display::ColorFromRgb(75, 50, 25), false);
        Api_Display::DrawText("NO", 139, 173, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(250, 200, 150));

        Api_Console::Log(Api_Console::LogType::Info, "Alert displayed: " + Title);

        bool Done = false;
        bool Result = false;

        while(!Done)
        {
            if(Api_Touch::ReadTouch())
            {
                if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 200)
                {
                    if(Api_Touch::TouchX > 60 && Api_Touch::TouchX < 120)
                    {
                        Done = true;
                        Result = true;
                    }
                    
                    if(Api_Touch::TouchX > 120 && Api_Touch::TouchX < 180)
                    {
                        Done = true;
                        Result = false;
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

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Warning, "Alert result: YES");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Warning, "Alert result: NO");
        }

        return Result;
    }
    
    void ShowOk(String Title, String Message)
    {
        Api_Display::Pause();

        Api_Display::DrawRectangle(10, 40, 220, 30, Api_Display::ColorFromRgb(75, 50, 25));
        Api_Display::DrawRectangle(10, 70, 220, 130, Api_Display::ColorFromRgb(250, 200, 150));

        Api_Display::DrawText(Title, 14, 44, 3, Api_Display::ColorFromRgb(250, 250, 250), Api_Display::ColorFromRgb(75, 50, 25));
        Api_Display::DrawText(Message, 12, 72, 2, Api_Display::ColorFromRgb(25, 25, 25), Api_Display::ColorFromRgb(250, 200, 150), 218);

        Api_Display::DrawRectangle(100, 172, 40, 20, Api_Display::ColorFromRgb(75, 50, 25), false);
        Api_Display::DrawText("OK", 109, 175, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(250, 200, 150));

        Api_Console::Log(Api_Console::LogType::Info, "Alert displayed: " + Title);

        bool Done = false;

        while(!Done)
        {
            if(Api_Touch::ReadTouch())
            {
                if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 200)
                {
                    if(Api_Touch::TouchX > 90 && Api_Touch::TouchX < 150)
                    {
                        Done = true;
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
    }
}