#include "main.h"

namespace Api_Console
{
    void Setup();

    enum LogType { Error, Warning, Ok, Info, Other };

    int Color(int Index);
    String Message(int Index, bool DateTime);

    void Log(LogType Type, String Message);
}