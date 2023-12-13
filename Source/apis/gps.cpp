#include "gps.h"

#include "apis/console.h"
#include "apis/settings.h"
#include "apis/wifi.h"

namespace Api_Gps
{
    String Country = "";
    String Code = "";
    String City = "";
    double Latitude = 0;
    double Longitude = 0;
    
    void Setup()
    {
        bool Result = true;

        Api_Settings::Latitude();
        Api_Settings::Longitude();

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Gps initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize gps.");
        }
    }

    bool Locate()
    {
        if (Api_Wifi::Connected())
        {
            if (Api_Wifi::Fetch("http://ip-api.com/json", true))
            {
                if(Api_Wifi::ResultJson["status"].as<String>().equalsIgnoreCase("success"))
                {
                    Country = Api_Wifi::ResultJson["country"].as<String>();
                    Code = Api_Wifi::ResultJson["countryCode"].as<String>();
                    City = Api_Wifi::ResultJson["city"].as<String>();
                    Latitude = Api_Wifi::ResultJson["lat"].as<double>();
                    Longitude = Api_Wifi::ResultJson["lon"].as<double>();

                    Api_Console::Log(Api_Console::LogType::Ok, "Location obtained successfully.");

                    return true;
                }

                Api_Console::Log(Api_Console::LogType::Error, "Cannot locate: Api error.");

                return false;
            }

            Api_Console::Log(Api_Console::LogType::Error, "Cannot locate: Fetch error.");

            return false;
        }

        Api_Console::Log(Api_Console::LogType::Warning, "Connot locate without internet.");

        return false;
    }
}