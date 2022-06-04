#define LILYGO_WATCH_2020_V1
#include <LilyGoWatch.h>

// Libraries:
#include <ESP32HttpUpdate.h>
#include "WiFi.h"
#include "SPIFFS.h"

extern TTGOClass* SmartWatch;
extern String OsVersion;

extern String Apps[];

extern int AppsNumber;
extern int PagesNumber;
extern int Page;
