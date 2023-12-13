#include "settings.h"

#include "apis/console.h"

namespace Api_Settings
{
    void Setup()
    {
        bool Result = EEPROM.begin(4096);

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Eeprom initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize eeprom.");
        }
    }

    String ReadString(int Address, int Length)
    {
        char Text[Length];

        for (int i = 0; i < Length; i++)
        {
            Text[i] = EEPROM.read(Address + i);

            if(Text[i] == 0)
            {
                Length = i;
            }
        }
        
        String Result = String(Text);

        Result = Result.substring(0, Length);
        
        Result.trim();

        return Result;
    }

    bool WriteString(int Address, int Length, String Value)
    {
        if(Value.length() > Length)
        {
            Value = Value.substring(0, Length);
        }

        int Number = Value.length();

        for (int i = 0; i < Length; i++)
        {
            if(i < Number)
            {
                EEPROM.write(Address + i, Value[i]);
            }
            else
            {
                EEPROM.write(Address + i, 0);

                Length = i;
            }
        }

        return true;
    }

    uint8_t ReadByte(int Address) { return EEPROM.readByte(Address); }
    bool WriteByte(int Address, uint8_t Value) { EEPROM.writeByte(Address, Value); return true; }
    
    uint16_t ReadShort(int Address) { return EEPROM.readUShort(Address); }
    bool WriteShort(int Address, uint16_t Value) { EEPROM.writeUShort(Address, Value); return true; }
    
    uint32_t ReadInt(int Address) { return EEPROM.readUInt(Address); }
    bool WriteInt(int Address, uint32_t Value) { EEPROM.writeUInt(Address, Value); return true; }
    
    uint64_t ReadLong(int Address) { return EEPROM.readULong64(Address); }
    bool WriteLong(int Address, uint64_t Value) { EEPROM.writeULong64(Address, Value); return true; }

    void Update()
    {
        bool Result = EEPROM.commit();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Error, "Settings updated.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to update settings.");
        }
    }

    void FactoryReset()
    {
        Lockscreen(111111111);

        Latitude(0);
        Longitude(0);

        Remote_Protocol("");
        Remote_Length(16);

        Timezone(0);
        Style(0);

        for (int i = 0; i < 5; i++)
        {
            Network_Name(i, "");
            Network_Pass(i, "");
            Network_Addr(i, 0);
            Network_Gate(i, 0);
            Network_Mask(i, 0);
            Network_Dns(i, 0);
        }
        
        for (int i = 0; i < 5; i++)
        {
            Radio_Name(i, "");
            Radio_Url(i, "");
        }
        
        for (int i = 0; i < 10; i++)
        {
            Alarm_Hour(i, 0);
            Alarm_Minute(i, 0);
            Alarm_Day(i, 0);
        }
        
        for (int i = 0; i < 10; i++)
        {
            Holiday_Name(i, "");
            Holiday_Day(i, 0);
            Holiday_Month(i, 0);
        }

        for (char i = 'A'; i <= 'Z'; i++)
        {
            Remote_Letter(i, 0);
        }

        for (char i = '0'; i <= '9'; i++)
        {
            Remote_Number(i, 0);
        }

        for (int i = 0; i < 5; i++)
        {
            Note(i, "");
        }
        
        Remote_Address("");
        Remote_Username("");
        Remote_Password("");

        Remote_Port_Vnc(5900);
        Remote_Port_Ftp(21);
        Remote_Port_Ssh(22);

        for (int i = 0; i < 5; i++)
        {
            App_Name(i, "");
            App_Token(i, "");
            App_Username(i, "");
            App_Password(i, "");
        }

        Device("ArduSmartWatch");

        Update();

        Api_Console::Log(Api_Console::LogType::Info, "Factory reset");
    }

    //    0 -    3  =  Lockscreen Code

    uint32_t Lockscreen() { return ReadInt(0); }
    bool Lockscreen(uint32_t Value) { return WriteInt(0, Value); }

    //    4 -    5  =  Latitude   //    6 -    7  =  Longitude

    int16_t Latitude() { return ReadShort(4) - 90; }
    bool Latitude(int16_t Value) { return WriteShort(4, Value + 90); }
    
    int16_t Longitude() { return ReadShort(6) - 180; }
    bool Longitude(int16_t Value) { return WriteShort(6, Value + 180); }

    //    8 -   11  =  Remote Protocol      //   12 -   12  =  Remote Length
    
    String Remote_Protocol() { return ReadString(8, 4); }
    bool Remote_Protocol(String Value) { return WriteString(8, 4, Value); }

    uint8_t Remote_Length() { return ReadByte(12); }
    bool Remote_Length(uint8_t Value) { return WriteByte(12, Value); }

    //   13 -   13  =  Clock Gmt    //   14 -   14  =  Clock Style

    int8_t Timezone() { return ReadByte(13) - 64; }
    bool Timezone(int8_t Value) { return WriteByte(13, Value + 64); }
    
    uint8_t Style() { return ReadByte(14); }
    bool Style(uint8_t Value) { return WriteByte(14, Value); }

    //  15 -  46  =  Network 5 Name     //   92 -  123  =  Network 5 Name       //  169 -  200  =  Network 5 Name       //  246 -  277  =  Network 5 Name       //  323 -  354  =  Network 5 Name   
    //  47 -  78  =  Network 5 Pass     //  124 -  155  =  Network 5 Pass       //  201 -  232  =  Network 5 Pass       //  278 -  309  =  Network 5 Pass       //  355 -  386  =  Network 5 Pass   
    //  79 -  82  =  Network 5 Address  //  156 -  159  =  Network 5 Address    //  233 -  236  =  Network 5 Address    //  310 -  313  =  Network 5 Address    //  387 -  390  =  Network 5 Address
    //  83 -  86  =  Network 5 Gateway  //  160 -  163  =  Network 5 Gateway    //  237 -  240  =  Network 5 Gateway    //  314 -  317  =  Network 5 Gateway    //  391 -  394  =  Network 5 Gateway
    //  87 -  87  =  Network 5 Mask     //  164 -  164  =  Network 5 Mask       //  241 -  241  =  Network 5 Mask       //  318 -  318  =  Network 5 Mask       //  395 -  395  =  Network 5 Mask   
    //  88 -  91  =  Network 5 Dns      //  165 -  168  =  Network 5 Dns        //  242 -  245  =  Network 5 Dns        //  319 -  322  =  Network 5 Dns        //  396 -  399  =  Network 5 Dns    

    String Network_Name(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(15 + (Index * 77), 32); } return ""; }
    bool Network_Name(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(15 + (Index * 77), 32, Value); } return false; }

    String Network_Pass(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(47 + (Index * 77), 32); } return ""; }
    bool Network_Pass(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(47 + (Index * 77), 32, Value); } return false; }

    uint32_t Network_Addr(int Index) { if(Index >= 0 && Index <= 4) { return ReadInt(79 + (Index * 77)); } return 0; }
    bool Network_Addr(int Index, uint32_t Value) { if(Index >= 0 && Index <= 4) { return WriteInt(79 + (Index * 77), Value); } return false; }

    uint32_t Network_Gate(int Index) { if(Index >= 0 && Index <= 4) { return ReadInt(83 + (Index * 77)); } return 0; }
    bool Network_Gate(int Index, uint32_t Value) { if(Index >= 0 && Index <= 4) { return WriteInt(83 + (Index * 77), Value); } return false; }

    uint8_t Network_Mask(int Index) { if(Index >= 0 && Index <= 4) { return ReadByte(87 + (Index * 77)); } return 0; }
    bool Network_Mask(int Index, uint8_t Value) { if(Index >= 0 && Index <= 4) { return WriteByte(87 + (Index * 77), Value); } return false; }

    uint32_t Network_Dns(int Index) { if(Index >= 0 && Index <= 4) { return ReadInt(88 + (Index * 77)); } return 0; }
    bool Network_Dns(int Index, uint32_t Value) { if(Index >= 0 && Index <= 4) { return WriteInt(88 + (Index * 77), Value); } return false; }

    //  400 -  415  =  Radio 1 Name     //  480 -  495  =  Radio 2 Name     //  560 -  575  =  Radio 3 Name     //  640 -  655  =  Radio 4 Name     //  720 -  735  =  Radio 5 Name 
    //  416 -  479  =  Radio 1 Url      //  486 -  559  =  Radio 2 Url      //  576 -  639  =  Radio 3 Url      //  656 -  719  =  Radio 4 Url      //  736 -  799  =  Radio 5 Url  

    String Radio_Name(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(400 + (Index * 80), 16); } return ""; }
    bool Radio_Name(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(400 + (Index * 80), 16, Value); } return false; }

    String Radio_Url(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(416 + (Index * 80), 64); } return ""; }
    bool Radio_Url(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(416 + (Index * 80), 64, Value); } return false; }

    //  800 -  800  =  Alarm 1 Hour     //  803 -  803  =  Alarm 2 Hour     //  806 -  806  =  Alarm 3 Hour     //  809 -  809  =  Alarm 4 Hour     //  812 -  812  =  Alarm 5 Hour     
    //  801 -  801  =  Alarm 1 Minute   //  804 -  804  =  Alarm 2 Minute   //  807 -  807  =  Alarm 3 Minute   //  810 -  810  =  Alarm 4 Minute   //  813 -  813  =  Alarm 5 Minute   
    //  802 -  802  =  Alarm 1 Day      //  805 -  805  =  Alarm 2 Day      //  808 -  808  =  Alarm 3 Day      //  811 -  811  =  Alarm 4 Day      //  814 -  814  =  Alarm 5 Day      
   
    //  815 -  815  =  Alarm 6 Hour     //  818 -  818  =  Alarm 7 Hour     //  821 -  821  =  Alarm 8 Hour     //  824 -  824  =  Alarm 9 Hour     //  827 -  827  =  Alarm 0 Hour     
    //  816 -  816  =  Alarm 6 Minute   //  819 -  819  =  Alarm 7 Minute   //  822 -  822  =  Alarm 8 Minute   //  825 -  825  =  Alarm 9 Minute   //  828 -  828  =  Alarm 0 Minute   
    //  817 -  817  =  Alarm 6 Day      //  820 -  820  =  Alarm 7 Day      //  823 -  823  =  Alarm 8 Day      //  826 -  826  =  Alarm 9 Day      //  829 -  829  =  Alarm 0 Day      

    uint8_t Alarm_Hour(int Index) { if(Index >= 0 && Index <= 9) { return ReadByte(800 + (Index * 3)); } return 0; }
    bool Alarm_Hour(int Index, uint8_t Value) { if(Index >= 0 && Index <= 9) { return WriteByte(800 + (Index * 3), Value); } return false; }

    uint8_t Alarm_Minute(int Index) { if(Index >= 0 && Index <= 9) { return ReadByte(801 + (Index * 3)); } return 0; }
    bool Alarm_Minute(int Index, uint8_t Value) { if(Index >= 0 && Index <= 9) { return WriteByte(801 + (Index * 3), Value); } return false; }

    uint8_t Alarm_Day(int Index) { if(Index >= 0 && Index <= 9) { return ReadByte(802 + (Index * 3)); } return 0; }
    bool Alarm_Day(int Index, uint8_t Value) { if(Index >= 0 && Index <= 9) { return WriteByte(802 + (Index * 3), Value); } return false; }

    //  830 -  853  =  Holiday 1 Name   //  856 -  879  =  Holiday 2 Name   //  882 -  905  =  Holiday 3 Name   //  908 -  931  =  Holiday 4 Name   //  934 -  957  =  Holiday 5 Name   
    //  854 -  854  =  Holiday 1 Day    //  880 -  880  =  Holiday 2 Day    //  906 -  906  =  Holiday 3 Day    //  932 -  932  =  Holiday 4 Day    //  958 -  958  =  Holiday 5 Day    
    //  855 -  855  =  Holiday 1 Month  //  881 -  881  =  Holiday 2 Month  //  907 -  907  =  Holiday 3 Month  //  933 -  933  =  Holiday 4 Month  //  959 -  959  =  Holiday 5 Month 

    //  960 -  983  =  Holiday 6 Name   //  986 - 1009  =  Holiday 7 Name   // 1012 - 1035  =  Holiday 8 Name   // 1038 - 1061  =  Holiday 9 Name   // 1064 - 1087  =  Holiday 0 Name   
    //  984 -  984  =  Holiday 6 Day    // 1010 - 1010  =  Holiday 7 Day    // 1036 - 1036  =  Holiday 8 Day    // 1062 - 1062  =  Holiday 9 Day    // 1088 - 1088  =  Holiday 0 Day    
    //  985 -  985  =  Holiday 6 Month  // 1011 - 1011  =  Holiday 7 Month  // 1037 - 1037  =  Holiday 8 Month  // 1063 - 1063  =  Holiday 9 Month  // 1089 - 1089  =  Holiday 0 Month  

    String Holiday_Name(int Index) { if(Index >= 0 && Index <= 9) { return ReadString(830 + (Index * 26), 24); } return ""; }
    bool Holiday_Name(int Index, String Value) { if(Index >= 0 && Index <= 9) { return WriteString(830 + (Index * 26), 24, Value); } return false; }

    uint8_t Holiday_Day(int Index) { if(Index >= 0 && Index <= 9) { return ReadByte(854 + (Index * 26)); } return 0; }
    bool Holiday_Day(int Index, uint8_t Value) { if(Index >= 0 && Index <= 9) { return WriteByte(854 + (Index * 26), Value); } return false; }

    uint8_t Holiday_Month(int Index) { if(Index >= 0 && Index <= 9) { return ReadByte(855 + (Index * 26)); } return 0; }
    bool Holiday_Month(int Index, uint8_t Value) { if(Index >= 0 && Index <= 9) { return WriteByte(855 + (Index * 26), Value); } return false; }

    // 1090 - 1097  =  Remote A     // 1098 - 1105  =  Remote B     // 1106 - 1113  =  Remote C     // 1114 - 1121  =  Remote D     // 1122 - 1129  =  Remote E
    // 1130 - 1137  =  Remote F     // 1138 - 1145  =  Remote G     // 1146 - 1153  =  Remote H     // 1154 - 1161  =  Remote I     // 1162 - 1169  =  Remote J
    // 1170 - 1177  =  Remote K     // 1178 - 1185  =  Remote L     // 1186 - 1193  =  Remote M     // 1194 - 1201  =  Remote N     // 1202 - 1209  =  Remote O
    // 1210 - 1217  =  Remote P     // 1226 - 1233  =  Remote R     // 1234 - 1241  =  Remote S     // 1242 - 1249  =  Remote T     // 1250 - 1257  =  Remote U
    // 1258 - 1265  =  Remote V     // 1266 - 1273  =  Remote W     // 1274 - 1281  =  Remote X     // 1282 - 1289  =  Remote Y     // 1290 - 1297  =  Remote Z

    uint64_t Remote_Letter(char Index) { if(Index >= 'A' && Index <= 'Z') { return ReadLong(1090 + ((Index - 65) * 8)); } return 0; }
    bool Remote_Letter(char Index, uint64_t Value) { if(Index >= 'A' && Index <= 'Z') { return WriteLong(1090 + ((Index - 65) * 8), Value); } return false; }

    // 1298 - 1553  =  Note 1   // 1554 - 1809  =  Note 2   // 1810 - 2065  =  Note 3   // 2066 - 2321  =  Note 4   // 2322 - 2577  =  Note 5

    String Note(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(1298 + (Index * 256), 256); } return ""; }
    bool Note(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(1298 + (Index * 256), 256, Value); } return false; }

    // 2578 - 2609  =  Remote Address   // 2610 - 2641  =  Remote Username  // 2642 - 2673  =  Remote Password
    // 2674 - 2675  =  Remote Vnc Port  // 2676 - 2677  =  Remote Ftp Port  // 2678 - 2679  =  Remote Ssh Port

    String Remote_Address() { return ReadString(2578, 32); }
    bool Remote_Address(String Value) { return WriteString(2578, 32, Value); }
    
    String Remote_Username() { return ReadString(2610, 32); }
    bool Remote_Username(String Value) { return WriteString(2610, 32, Value); }
    
    String Remote_Password() { return ReadString(2642, 32); }
    bool Remote_Password(String Value) { return WriteString(2642, 32, Value); }

    uint16_t Remote_Port_Vnc() { return ReadShort(2674); }
    bool Remote_Port_Vnc(uint16_t Value) { return WriteShort(2674, Value); }

    uint16_t Remote_Port_Ftp() { return ReadShort(2676); }
    bool Remote_Port_Ftp(uint16_t Value) { return WriteShort(2676, Value); }

    uint16_t Remote_Port_Ssh() { return ReadShort(2678); }
    bool Remote_Port_Ssh(uint16_t Value) { return WriteShort(2678, Value); }

    // 2680 - 2687  =  App 1 Name       // 2944 - 2951  =  App 2 Name       // 3208 - 3215  =  App 3 Name       // 3472 - 3479  =  App 4 Name       // 3736 - 3743  =  App 5 Name  
    // 2688 - 2879  =  App 1 Token      // 2952 - 3143  =  App 2 Token      // 3216 - 3407  =  App 3 Token      // 3480 - 3671  =  App 4 Token      // 3744 - 3935  =  App 5 Token
    // 2880 - 2911  =  App 1 Username   // 3144 - 3175  =  App 2 Username   // 3408 - 3439  =  App 3 Username   // 3672 - 3703  =  App 4 Username   // 3936 - 3977  =  App 5 Username
    // 2912 - 2943  =  App 1 Password   // 3176 - 3207  =  App 2 Password   // 3440 - 3471  =  App 3 Password   // 3724 - 3735  =  App 4 Password   // 3968 - 3999  =  App 5 Password

    String App_Name(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(2680 + (Index * 264), 8); } return ""; }
    bool App_Name(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(2680 + (Index * 264), 8, Value); } return false; }
    
    String App_Token(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(2688 + (Index * 264), 192); } return ""; }
    bool App_Token(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(2688 + (Index * 264), 192, Value); } return false; }
    
    String App_Username(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(2880 + (Index * 264), 32); } return ""; }
    bool App_Username(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(2880 + (Index * 264), 32, Value); } return false; }
    
    String App_Password(int Index) { if(Index >= 0 && Index <= 4) { return ReadString(2912 + (Index * 264), 32); } return ""; }
    bool App_Password(int Index, String Value) { if(Index >= 0 && Index <= 4) { return WriteString(2912 + (Index * 264), 32, Value); } return false; }

    // 4000 - 4007  =  Remote 1     // 4008 - 4015  =  Remote 2     // 4016 - 4023  =  Remote 3     // 4024 - 4031  =  Remote 4     // 4032 - 4039  =  Remote 5
    // 4040 - 4047  =  Remote 6     // 4048 - 4055  =  Remote 7     // 4056 - 4063  =  Remote 8     // 4064 - 4071  =  Remote 9     // 4072 - 4079  =  Remote 0

    uint64_t Remote_Number(char Index) { if(Index >= '0' && Index <= '9') { return ReadLong(4000 + ((Index - 48) * 8)); } return 0; }
    bool Remote_Number(char Index, uint64_t Value) { if(Index >= '0' && Index <= '9') { return WriteLong(4000 + ((Index - 48) * 8), Value); } return false; }

    // 4080 - 4095  =  Device Name
    
    String Device() { return ReadString(4080, 16); }
    bool Device(String Value) { return WriteString(4080, 16, Value); }
}