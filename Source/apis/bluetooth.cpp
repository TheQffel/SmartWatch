#include "bluetooth.h"

namespace Api_Bluetooth
{
    void Toggle(bool State)
    {
        if(State)
        {
            btStart();
        }
        else
        {
            btStop();
        }
    }
}