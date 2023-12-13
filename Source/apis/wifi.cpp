#include "wifi.h"

#include "apis/console.h"
#include "apis/display.h"
#include "apis/settings.h"
#include "apis/touch.h"

#include "guis/alert.h"
#include "guis/keyboard.h"

namespace Api_Wifi
{
    String Name;
    String Pass;
    uint32_t Addr;
    uint32_t Mask;
    uint32_t Gate;
    uint32_t Dns;
    uint8_t Temp;

    int Count = 0;
    String* Networks;
    bool* Passwords;
    int* Strengths;

    String ResultText;
    StaticJsonDocument<4096> ResultJson;

    bool ScanAutoConnect = false;

    uint8_t LongToShort(uint32_t IpMask)
    {
        int IpLength = 0;
        while (IpLength < 32 && (IpMask & 0x80000000))
        { IpLength++; IpMask <<= 1; }
        return IpLength;
    }

    uint32_t ShortToLong(uint8_t IpMask)
    {
        return (0xFFFFFFFF << (32 - IpMask)) & 0xFFFFFFFF;
    }

    void ScanResults();

    void Setup()
    {
        bool Result = WiFi.setHostname(Api_Settings::Device().c_str());

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Wifi initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize wifi.");
        }
    }

    void Loop()
    {
        if(ScanAutoConnect)
        {
            Count = WiFi.scanComplete();

            if(Count < 0)
            {
                if(Count == -2)
                {
                    WiFi.scanNetworks(true);
                }
            }
            else
            {
                ScanResults();

                Autoconnect(false);

                WiFi.scanDelete();
            }
        }
    }

    bool Connected()
    {
        return (WiFi.status() == WL_CONNECTED);
    }

    void Toggle(bool State)
    {
        if(State)
        {
            if(WiFi.mode(WIFI_MODE_STA))
            {
                Api_Console::Log(Api_Console::LogType::Ok, "Wifi enabled successfully.");
            }
            else
            {
                Api_Console::Log(Api_Console::LogType::Error, "Failed to enable wifi.");
            }

            delay(100);
            Autoconnect();

            delay(100);
        }
        else
        {
            Disconnect();
            delay(100);

            if(WiFi.mode(WIFI_MODE_NULL))
            {
                Api_Console::Log(Api_Console::LogType::Ok, "Wifi disabled successfully.");
            }
            else
            {
                Api_Console::Log(Api_Console::LogType::Error, "Failed to disable wifi.");
            }

            delay(100);
        }
    }

    void Scan()
    {
        wifi_mode_t Mode = WiFi.getMode();

        Count = WiFi.scanNetworks();

        ScanResults();

        WiFi.scanDelete();

        WiFi.mode(Mode);
    }

    void ScanResults()
    {
        Networks = new String[Count];
        Passwords = new bool[Count];
        Strengths = new int[Count];

        for (int i = 0; i < Count; i++)
        {
            Networks[i] = WiFi.SSID(i);
            Strengths[i] = WiFi.RSSI(i);

            if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
            {
                Passwords[i] = false;
            }
            else
            {
                Passwords[i] = true;
            }
        }
    }

    uint32_t Convert(uint8_t A, uint8_t B, uint8_t C, uint8_t D)
    {
        uint32_t Result = 0;
        
        Result |= static_cast<uint32_t>(A) << 24;
        Result |= static_cast<uint32_t>(B) << 16;
        Result |= static_cast<uint32_t>(C) << 8;
        Result |= static_cast<uint32_t>(D);

        return Result;
    }

    uint32_t Convert(String Address)
    {
        Address += ".....";

        int Index0 = 0;
        int IndexA = Address.indexOf('.', Index0) + 1;
        int IndexB = Address.indexOf('.', IndexA) + 1;
        int IndexC = Address.indexOf('.', IndexB) + 1;
        int IndexD = Address.indexOf('.', IndexC) + 1;
        
        String A = Address.substring(Index0, IndexA - 1);
        String B = Address.substring(IndexA, IndexB - 1);
        String C = Address.substring(IndexB, IndexC - 1);
        String D = Address.substring(IndexC, IndexD - 1);

        return Convert(A.toInt(), B.toInt(), C.toInt(), D.toInt());
    }

    void Config()
    {
        IPAddress IpAddr(Addr >> 24, Addr >> 16, Addr >> 8, Addr);
        IPAddress IpGate(Gate >> 24, Gate >> 16, Gate >> 8, Gate);
        IPAddress IpMask(Mask >> 24, Mask >> 16, Mask >> 8, Mask);
        IPAddress IpDns(Dns >> 24, Dns >> 16, Dns >> 8, Dns);

        WiFi.config(IpAddr, IpGate, IpMask, IpDns);
    }

    void Config(String WifiName, String WifiPassword, uint32_t NetAddress, uint32_t NetMask, uint32_t NetGateway, uint32_t DnsAddress)
    {
        Name = WifiName;
        Pass = WifiPassword;
        
        Addr = NetAddress;
        Mask = NetMask;
        Gate = NetGateway;
        Dns = DnsAddress;

        Config();
    }

    void Connect()
    {
        if(Pass == "")
        {
            WiFi.begin(Name.c_str());
        }
        else
        {
            WiFi.begin(Name.c_str(), Pass.c_str());
        }
    }

    void Disconnect()
    {
        WiFi.disconnect();

        Config("", "", 0, 0, 0, 0);
    }

    void Autoconnect(bool Scan)
    {
        ScanAutoConnect = Scan;

        if(!Scan)
        {
            String Names[5];

            for(int i = 0; i < 5; i++)
            {
                Names[i] = Api_Settings::Network_Name(i);
            }

            for (int i = 0; i < Count; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if(Names[j] == Networks[i])
                    {
                        Load(j);
                        Connect();

                        Api_Console::Log(Api_Console::LogType::Info, "Connecting to wifi: " + Name);

                        return;
                    }
                }
            }

            Api_Console::Log(Api_Console::LogType::Warning, "No known network to connect.");
        }
    }

    void Save(int Index)
    {
        Temp = LongToShort(Mask);

        Api_Settings::Network_Name(Index, Name);
        Api_Settings::Network_Pass(Index, Pass);
        Api_Settings::Network_Addr(Index, Addr);
        Api_Settings::Network_Mask(Index, Temp);
        Api_Settings::Network_Gate(Index, Gate);
        Api_Settings::Network_Dns(Index, Dns);

        Api_Settings::Update();
    }

    void Load(int Index)
    {
        Name = Api_Settings::Network_Name(Index);
        Pass = Api_Settings::Network_Pass(Index);
        Addr = Api_Settings::Network_Addr(Index);
        Temp = Api_Settings::Network_Mask(Index);
        Gate = Api_Settings::Network_Gate(Index);
        Dns = Api_Settings::Network_Dns(Index);

        Mask = ShortToLong(Temp);

        Config();
    }

    void Main()
    {
        if(Connected())
        { Disconnect(); }

        Api_Display::Clear(Color_Black_Light);

        Api_Display::DrawText("Loading...", 8, 8, 3, Color_White_Dark, Color_Black_Light);

        Api_Display::DrawRectangle(0, 40, 240, 200, Color_Grey_Medium);
        Api_Display::DrawRectangle(0, 0, 240, 40, Color_Black_Dark, false);

        Scan();

        Api_Touch::ReadButton();

        Api_Display::DrawText("Select WiFi:", 8, 8, 3, Color_White_Dark, Color_Black_Light);

        for (int i = 0; i < 5; i++)
        {
            if(i < Count)
            {
                Api_Display::DrawText(Networks[i], 10, (i * 40) + 52, 2, Color_White_Medium, Color_Grey_Medium);
            }

            Api_Display::DrawRectangle(0, (i * 40) + 40, 240, 40, Color_Black_Dark, false);
        }

        int Index = -1;

        while (!Api_Touch::ReadButton())
        {
            if(Api_Touch::ReadTouch())
            {
                if(Api_Touch::Click)
                {
                    if(Api_Touch::TouchY > 40 && Api_Touch::TouchY < 80 && Count > 0) { Index = 0; }
                    if(Api_Touch::TouchY > 80 && Api_Touch::TouchY < 120 && Count > 1) { Index = 1; }
                    if(Api_Touch::TouchY > 120 && Api_Touch::TouchY < 160 && Count > 2) { Index = 2; }
                    if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 200 && Count > 3) { Index = 3; }
                    if(Api_Touch::TouchY > 200 && Api_Touch::TouchY < 240 && Count > 4) { Index = 4; }

                    break;
                }
            }

            delay(10);
        }

        if(Index > -1)
        {
            String Space = "                ";
            String Empty[] = { "< ENTER SSID >", "< ENTER PASS >", " < ADDR AUTO > ", " < MASK AUTO > ", " < GATE AUTO > ", " < DNS AUTO > " };
            String Texts[] = { "", "", "", "", "", "" };
            bool Secured = Passwords[Index];
            Texts[0] = Networks[Index];

            if(Secured)
            {
                Texts[1] = Gui_Keyboard::TextInput();
            }

            Gui_Alert::ShowOk("Information", "Setup adv. config (optionally) and press network name to continue.");

            Api_Touch::ReadTouch();

            Api_Display::Clear(Color_Black_Medium);

            for (int i = 0; i < 6; i++)
            {
                String Text = (Texts[i].length() > 0 ? Texts[i] : Empty[i]);
                int Color = (Texts[i].length() > 0 ? Color_White_Medium : Color_Grey_Medium);
                
                Api_Display::DrawText(Text, 10, (i * 40) + 12, 2, Color, Color_Black_Medium);
                Api_Display::DrawRectangle(0, (i * 40), 240, 40, Color_Black_Dark, false);
            }

            bool Ok = false;

            while(!Api_Touch::ReadButton())
            {
                if(Api_Touch::ReadTouch())
                {
                    int TextIndex = -1;

                    if(Api_Touch::Click)
                    {
                        if(Api_Touch::TouchY > 0 && Api_Touch::TouchY < 40) { Ok = true; break; }
                        if(Api_Touch::TouchY > 40 && Api_Touch::TouchY < 80) { TextIndex = 1; }
                        if(Api_Touch::TouchY > 80 && Api_Touch::TouchY < 120) { TextIndex = 2; }
                        if(Api_Touch::TouchY > 120 && Api_Touch::TouchY < 160) { TextIndex = 3; }
                        if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 200) { TextIndex = 4; }
                        if(Api_Touch::TouchY > 200 && Api_Touch::TouchY < 240) { TextIndex = 5; }
                    }

                    if(TextIndex > 0)
                    {
                        if(TextIndex == 1)
                        {
                            Texts[TextIndex] = Gui_Keyboard::TextInput();
                        }
                        else
                        {
                            Texts[TextIndex] = Gui_Keyboard::NumberInput(false, true, true);
                        }

                        Api_Display::Clear(Color_Black_Medium);
                    }

                    for (int i = 0; i < 6; i++)
                    {
                        String Text = (Texts[i].length() > 0 ? Texts[i] : Empty[i]);
                        int Color = (Texts[i].length() > 0 ? Color_White_Medium : Color_Grey_Medium);
                        
                        Api_Display::DrawText(Space, 10, (i * 40) + 12, 2, Color, Color_Black_Medium);
                        Api_Display::DrawText(Text, 10, (i * 40) + 12, 2, Color, Color_Black_Medium);
                    }
                }

                delay(10);
            }

            if(Ok)
            {
                Config(Texts[0], Texts[1], Convert(Texts[2]), Convert(Texts[3]), Convert(Texts[4]), Convert(Texts[5]));

                if(WiFi.getMode() > 0)
                {
                    Connect();
                }

                Api_Display::Clear(Color_Black_Light);

                Api_Display::DrawRectangle(0, 40, 240, 200, Color_Grey_Medium);
                Api_Display::DrawRectangle(0, 0, 240, 40, Color_Black_Dark, false);

                Gui_Alert::ShowOk("Information", "You can have up to 5 saved networks - select one to overwrite.");

                Api_Touch::ReadButton();

                Api_Display::DrawText("Replace:", 8, 8, 3, Color_White_Dark, Color_Black_Light);

                for (int i = 0; i < 5; i++)
                {
                    Api_Display::DrawText(Api_Settings::Network_Name(i), 10, (i * 40) + 52, 2, Color_White_Medium, Color_Grey_Medium);

                    Api_Display::DrawRectangle(0, (i * 40) + 40, 240, 40, Color_Black_Dark, false);
                }

                Index = -1;

                while (!Api_Touch::ReadButton())
                {
                    if(Api_Touch::ReadTouch())
                    {
                        if(Api_Touch::Click)
                        {
                            if(Api_Touch::TouchY > 40 && Api_Touch::TouchY < 80) { Index = 0; }
                            if(Api_Touch::TouchY > 80 && Api_Touch::TouchY < 120) { Index = 1; }
                            if(Api_Touch::TouchY > 120 && Api_Touch::TouchY < 160) { Index = 2; }
                            if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 200) { Index = 3; }
                            if(Api_Touch::TouchY > 200 && Api_Touch::TouchY < 240) { Index = 4; }

                            break;
                        }
                    }

                    delay(10);
                }

                if(Index > -1)
                {
                    Save(Index);
                }
            }
        }
    }

    bool Fetch(String Address, bool ConvertToJson, int RedirectLimit)
    {
        bool Result = false;

        Address.replace('\\', '/');

        if(Address.length() > 9 && Address.indexOf(':') > 0 && Address.indexOf('/') > 0 && RedirectLimit > 0)
        {
            WiFiClient ClientHttp;
            WiFiClientSecure ClientHttps;
            HTTPClient Server;

            Server.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);

            String Protocol = Address.substring(0, Address.indexOf(':'));

            int Port = 0;
            bool Valid = false;
            bool Secured = false;

            if(Protocol.equalsIgnoreCase("HTTP"))
            {
                Port = 80;
                Valid = true;
                Secured = false;
            }

            if(Protocol.equalsIgnoreCase("HTTPS"))
            {
                Port = 443;
                Valid = true;
                Secured = true;

                ClientHttps.setInsecure();
            }

            String Host = Address.substring(Address.indexOf(':') + 3, Address.indexOf('/', 8));
            String Url = Address.substring(Address.indexOf('/', 8));

            if(Valid)
            {
                if (Server.begin(Secured ? ClientHttps : ClientHttp, Host, Port, Url, Secured))
                {
                    const char* Headers[] = { "Location" };
                    const size_t Size = sizeof(Headers) / sizeof(Headers[0]);
                    Server.collectHeaders(Headers, Size);

                    int Code = Server.GET();

                    if(Code >= 200 && Code <= 299)
                    {
                        Result = true;

                        ResultText = Server.getString();

                        Api_Console::Log(Api_Console::LogType::Ok, "Fetch (" + String(Code) + ") ok: " + Address);

                        if(ConvertToJson)
                        {
                            Result = (deserializeJson(ResultJson, ResultText) ? false : true);
                        }
                    }

                    if(Code >= 300 && Code <= 399)
                    {
                        Api_Console::Log(Api_Console::LogType::Warning, "Redirect (" + String(Code) + ") at: " + Address);

                        Result = Fetch(Server.header("Location"), ConvertToJson, RedirectLimit - 1);
                    }

                    if(Code >= 400 && Code <= 499)
                    {
                        Api_Console::Log(Api_Console::LogType::Error, "Error (" + String(Code) + ") client: " + Address);

                        Result = false;
                    }
                    
                    if(Code >= 500 && Code <= 599)
                    {
                        Api_Console::Log(Api_Console::LogType::Error, "Error (" + String(Code) + ") server: " + Address);

                        Result = false;
                    }
                    
                    Server.end();
                }
                else
                {
                    Api_Console::Log(Api_Console::LogType::Error, "Cannot connect: " + Address);
                }
            }
            else
            {
                Api_Console::Log(Api_Console::LogType::Error, "Invalid protocol: " + Address);
            }
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Invalid url: " + Address);
        }

        return Result;
    }
}