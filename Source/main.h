#define LILYGO_WATCH_2020_V1
//#define LILYGO_WATCH_2020_V2
//#define LILYGO_WATCH_2020_V3
//#define LILYGO_WATCH_2020_V4
//#define LILYGO_WATCH_2020_V5
#include <LilyGoWatch.h>

// Libraries:

#include <ArduinoJson.h>
#include <ESP32httpUpdate.h>
#include <WiFiClientSecure.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <EEPROM.h>
#include "WiFi.h"
#include "SPIFFS.h"

// Variables:

extern TTGOClass* SmartWatch;
extern String OsVersion;

extern String Apps[];

extern int AppsNumber;
extern int PagesNumber;
extern int Page;

// Colors:

#define Color_Black_Dark 0x0000
#define Color_Black_Medium 0x0861
#define Color_Black_Light 0x2124
#define Color_Grey_Dark 0x4208
#define Color_Grey_Medium 0x632C
#define Color_Grey_Light 0x8C71
#define Color_White_Dark 0xB596
#define Color_White_Medium 0xDEDB
#define Color_White_Light 0xFFFF
#define Color_Red_Dark 0xC000
#define Color_Red_Medium 0xF800
#define Color_Red_Light 0xFA08
#define Color_Green_Dark 0x0400
#define Color_Green_Medium 0x0600
#define Color_Green_Light 0x07E0
#define Color_Blue_Dark 0x0010
#define Color_Blue_Medium 0x001F
#define Color_Blue_Light 0x041F
#define Color_Yellow_Dark 0xFC00
#define Color_Yellow_Medium 0xFE00
#define Color_Yellow_Light 0xFFE0
#define Color_Pink_Dark 0xC018
#define Color_Pink_Medium 0xF81F
#define Color_Pink_Light 0xFC1F
#define Color_Cyan_Dark 0x07FF
#define Color_Cyan_Medium 0x07FC
#define Color_Cyan_Light 0x07F8
#define Color_Brown_Dark 0xA308
#define Color_Brown_Medium 0xC408
#define Color_Brown_Light 0xE610