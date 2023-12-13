#include "main.h"

namespace Api_Touch
{
    extern int16_t TouchX;
    extern int16_t TouchY;
    extern int16_t SwipeX;
    extern int16_t SwipeY;

    extern bool Hold;
    extern bool Swipe;
    extern bool Click;

    extern bool SwipeHorizontal;
    extern bool SwipeVertical;

    void Setup();
    
    bool ReadTouch(bool WaitForRelease = true);
    bool ReadButton();
}
