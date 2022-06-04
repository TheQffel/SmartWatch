#include "wifi.h"

namespace Api_Wifi
{
    int Count = 0;
    String Name[10];
    bool Password[10];
    int Strength[10];

    void Toggle(bool State)
    {
        if(State)
        {
            WiFi.setSleep(false);
            WiFi.mode(WIFI_MODE_STA);
        }
        else
        {
            WiFi.mode(WIFI_MODE_NULL);
            WiFi.setSleep(true);
        }
    }

    void Scan()
    {
        Count = WiFi.scanNetworks();

        if(Count > 10)
        {
            Count = 10;
        }
        for (int i = 0; i < Count; i++)
        {
            Name[i] = WiFi.SSID(i);
            Strength[i] = WiFi.RSSI(i);

            if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
            {
                Password[i] = false;
            }
            else
            {
                Password[i] = true;
            }
        }
    }

    void Connect(String Name, String Password)
    {
        if(Password == "")
        {
            WiFi.begin(Name.c_str());
        }
        else
        {
            WiFi.begin(Name.c_str(), Password.c_str());
        }
    }

    String ReadString(String Address)
    {
        WiFiClient Client;
        HTTPClient Server;

        String Response;

        if (Server.begin(Client, Address))
        {
            if (Server.GET() > 0)
            {
                Response = Server.getString();
            }
            else
            {
                return "";
            }
            Server.end();
        }
        else
        {
            return "";
        }
        return Response;
    }
}