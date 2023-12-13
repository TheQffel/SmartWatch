#include "main.h"

namespace Api_Settings
{
    void Setup();
    void FactoryReset();
    void Update();

    uint32_t Lockscreen();
    bool Lockscreen(uint32_t Value);

    int16_t Latitude();
    bool Latitude(int16_t Value);
    int16_t Longitude();
    bool Longitude(int16_t Value);

    String Remote_Protocol();
    bool Remote_Protocol(String Value);
    uint8_t Remote_Length();
    bool Remote_Length(uint8_t Value);

    int8_t Timezone();
    bool Timezone(int8_t Value);
    uint8_t Style();
    bool Style(uint8_t Value);

    String Network_Name(int Index);
    bool Network_Name(int Index, String Value);
    String Network_Pass(int Index);
    bool Network_Pass(int Index, String Value);
    uint32_t Network_Addr(int Index);
    bool Network_Addr(int Index, uint32_t Value);
    uint32_t Network_Gate(int Index);
    bool Network_Gate(int Index, uint32_t Value);
    uint8_t Network_Mask(int Index);
    bool Network_Mask(int Index, uint8_t Value);
    uint32_t Network_Dns(int Index);
    bool Network_Dns(int Index, uint32_t Value);

    String Radio_Name(int Index);
    bool Radio_Name(int Index, String Value);
    String Radio_Url(int Index);
    bool Radio_Url(int Index, String Value);

    uint8_t Alarm_Hour(int Index);
    bool Alarm_Hour(int Index, uint8_t Value);
    uint8_t Alarm_Minute(int Index);
    bool Alarm_Minute(int Index, uint8_t Value);
    uint8_t Alarm_Day(int Index);
    bool Alarm_Day(int Index, uint8_t Value);

    String Holiday_Name(int Index);
    bool Holiday_Name(int Index, String Value);
    uint8_t Holiday_Day(int Index);
    bool Holiday_Day(int Index, uint8_t Value);
    uint8_t Holiday_Month(int Index);
    bool Holiday_Month(int Index, uint8_t Value);

    uint64_t Remote_Letter(char Index);
    bool Remote_Letter(char Index, uint64_t Value);
    uint64_t Remote_Number(char Index);
    bool Remote_Number(char Index, uint64_t Value);

    String Note(int Index);
    bool Note(int Index, String Value);

    String Remote_Address();
    bool Remote_Address(String Value);
    String Remote_Username();
    bool Remote_Username(String Value);
    String Remote_Password();
    bool Remote_Password(String Value);
    uint16_t Remote_Port_Vnc();
    bool Remote_Port_Vnc(uint16_t Value);
    uint16_t Remote_Port_Ftp();
    bool Remote_Port_Ftp(uint16_t Value);
    uint16_t Remote_Port_Ssh();
    bool Remote_Port_Ssh(uint16_t Value);

    String App_Name(int Index);
    bool App_Name(int Index, String Value);
    String App_Token(int Index);
    bool App_Token(int Index, String Value);
    String App_Username(int Index);
    bool App_Username(int Index, String Value);
    String App_Password(int Index);
    bool App_Password(int Index, String Value);

    String Device();
    bool Device(String Value);
}