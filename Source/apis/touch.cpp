#include "touch.h"

namespace Api_Touch
{
    int16_t TouchX;
    int16_t TouchY;
    int16_t SwipeX;
    int16_t SwipeY;

    bool Hold;
    bool Swipe;

    bool ReadTouch()
    {
        Hold = false;
        Swipe = false;

        int HoldCounter = 0;

        if(SmartWatch->getTouch(TouchX, TouchY))
        {
            while(SmartWatch->getTouch(SwipeX, SwipeY))
            {
                HoldCounter++;
                delay(10);
            }
            if(HoldCounter > 99)
            {
                Hold = true;
            }
            if(abs(TouchX - SwipeX) > 25 || abs(TouchY - SwipeY) > 25)
            {
                Swipe = true;
            }
            return true;
        }
        return false;
    }
}