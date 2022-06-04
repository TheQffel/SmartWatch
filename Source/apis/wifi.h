#include "main.h"

namespace Api_Wifi
{
    extern int Count;
    extern String Name[10];
    extern bool Password[10];
    extern int Strength[10];

    void Toggle(bool State);
    void Scan();
    void Connect(String Name, String Password = "");
    String ReadString(String Address);
}
