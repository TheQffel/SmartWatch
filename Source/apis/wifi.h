#include "main.h"

namespace Api_Wifi
{
	extern String Name;
    extern String Pass;
    extern uint32_t Addr;
    extern uint32_t Mask;
    extern uint32_t Gate;
    extern uint32_t Dns;
 
    extern int Count;
    extern String* Networks;
    extern bool* Passwords;
    extern int* Strengths;

    extern String ResultText;
    extern StaticJsonDocument<4096> ResultJson;

    void Setup();
    void Loop();
    bool Connected();
    void Toggle(bool State);
    uint32_t Convert(uint8_t A, uint8_t B, uint8_t C, uint8_t D);
    void Config(String WifiName, String WifiPassword = "", uint32_t NetAddress = 0, uint32_t NetMask = 0, uint32_t NetGateway = 0, uint32_t DnsAddress = 0);
    void Load(int Index);
    void Save(int Index);
    void Scan();
    void Connect();
    void Autoconnect(bool Scan = true);
    void Disconnect();
    void Main();

    bool Fetch(String Address, bool ConvertToJson = false, int RedirectLimit = 10);
}
