#include "updater.h"

#include "apis\wifi.h"

namespace Api_Updater
{
    bool CheckForUpdates()
    {
        return OsVersion == Api_Wifi::ReadString("http://192.168.1.9/os/version.txt");
    }

    void Update()
    {
        ESPhttpUpdate.rebootOnUpdate(false);
        
        switch(ESPhttpUpdate.updateSpiffs("http://192.168.1.9/os/spiffs.bin"))
        {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                break;
        }
        switch(ESPhttpUpdate.update("http://192.168.1.9/os/firmware.bin"))
        {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                break;
        }
    }
}