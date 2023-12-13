#include "touch.h"

#include "apis/console.h"
#include "apis/vibration.h"

namespace Api_Touch
{
    int16_t TouchX;
    int16_t TouchY;
    int16_t SwipeX;
    int16_t SwipeY;

    bool Hold;
    bool Swipe;
    bool Click;

    bool SwipeHorizontal;
    bool SwipeVertical;

    void Setup()
    {
        bool Result = true;

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Touch initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize touch.");
        }
    }

    bool ReadTouch(bool WaitForRelease)
    {
        Hold = false;
        Swipe = false;
        Click = false;

        SwipeHorizontal = false;
        SwipeVertical = false;

        int HoldCounter = 0;

        if(SmartWatch->getTouch(TouchX, TouchY))
        {
            if(WaitForRelease)
            {
                while(SmartWatch->getTouch(SwipeX, SwipeY))
                {
                    if(HoldCounter++ == 50)
                    {
                        Api_Vibration::Vibrate();
                    }

                    delay(10);
                }

                int SwipeHorizontalLength = abs(TouchX - SwipeX);
                int SwipeVerticalLength = abs(TouchY - SwipeY);

                if(SwipeHorizontalLength > 50)
                {
                    SwipeHorizontal = true;
                    Swipe = true;
                }

                if(SwipeVerticalLength > 50)
                {
                    SwipeVertical = true;
                    Swipe = true;
                }

                if(HoldCounter > 50)
                {
                    Hold = !Swipe;
                }

                if(Swipe)
                {
                    if(SwipeHorizontalLength > SwipeVerticalLength)
                    {
                        SwipeVertical = false;
                    }

                    if(SwipeHorizontalLength < SwipeVerticalLength)
                    {
                        SwipeHorizontal = false;
                    }
                }
            }

            Click = (!Swipe && !Hold);

            if(Click)
            {
                Api_Vibration::Vibrate();
            }

            return true;
        }
        
        return false;
    }

    bool ReadButton()
    {
        SmartWatch->power->readIRQ();
        bool Short = SmartWatch->power->isPEKShortPressIRQ();
        bool Long = SmartWatch->power->isPEKLongtPressIRQ();
        SmartWatch->power->clearIRQ();
        return (Short || Long);
    }
}