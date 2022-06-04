#include "settings.h"

#include "apis\updater.h"
#include "apis\display.h"
#include "apis\touch.h"
#include "apis\wifi.h"

#include "guis\keyboard.h"

namespace App_Settings
{
	void Wifi()
	{
		Api_Display::DrawRectangle(0, 35, 240, 235, Api_Display::ColorFromRgb(200, 200, 200), true);
		Api_Wifi::Scan();
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 43);
		Api_Display::DrawText(Api_Wifi::Name[0], 45, 49, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 35, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 84);
		Api_Display::DrawText(Api_Wifi::Name[1], 45, 90, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 76, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 125);
		Api_Display::DrawText(Api_Wifi::Name[2], 45, 131, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 117, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 166);
		Api_Display::DrawText(Api_Wifi::Name[3], 45, 172, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 158, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 207);
		Api_Display::DrawText(Api_Wifi::Name[4], 45, 213, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 199, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);

		int Timeout = 0;
		while(Timeout < 1000)
		{
			if(Api_Touch::ReadTouch())
			{
				Timeout = 1000;

				int Network = -1;

				if(Api_Touch::TouchY > 35 && Api_Touch::TouchY < 76) { Network = 0; }
				if(Api_Touch::TouchY > 76 && Api_Touch::TouchY < 117) { Network = 1; }
				if(Api_Touch::TouchY > 117 && Api_Touch::TouchY < 158) { Network = 2; }
				if(Api_Touch::TouchY > 158 && Api_Touch::TouchY < 199) { Network = 3; }
				if(Api_Touch::TouchY > 199 && Api_Touch::TouchY < 240) { Network = 4; }

				if(Network > -1)
				{
					if(Api_Wifi::Password[Network])
					{
						Api_Wifi::Connect(Api_Wifi::Name[Network], Gui_Keyboard::GetInput(""));
					}
					else
					{
						Api_Wifi::Connect(Api_Wifi::Name[Network]);
					}
				}
			}

			Timeout++;
			delay(10);
		}
	}

	void Main()
	{
		/*Serial.print("Your Version: ");
		Serial.println(OsVersion);

		if(Api_Updater::CheckForUpdates())
		{
			Serial.println("Update Available!");
			//Api_Updater::Update();
		}
		else
		{
			Serial.println("Latest Version!");
		}*/

		//Serial.println(Gui_Keyboard::GetInput(""));

		Api_Display::DrawRectangle(0, 35, 240, 235, Api_Display::ColorFromRgb(200, 200, 200), true);
		Api_Display::DrawBmp("/Apps/Settings/Wifi.bmp", 8, 43);
		Api_Display::DrawText("Wifi", 45, 49, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 35, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Bluetooth.bmp", 8, 84);
		Api_Display::DrawText("Bluetooth", 45, 90, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 76, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Sounds.bmp", 8, 125);
		Api_Display::DrawText("Sounds", 45, 131, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 117, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/Display.bmp", 8, 166);
		Api_Display::DrawText(/*"Display"*/"Sync Time", 45, 172, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 158, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);
		Api_Display::DrawBmp("/Apps/Settings/System.bmp", 8, 207);
		Api_Display::DrawText("System", 45, 213, 2, Api_Display::ColorFromRgb(50, 50, 50), Api_Display::ColorFromRgb(200, 200, 200));
		Api_Display::DrawRectangle(0, 199, 240, 41, Api_Display::ColorFromRgb(125, 125, 125), false);

		int Timeout = 0;
		while(Timeout < 1000)
		{
			if(Api_Touch::ReadTouch())
			{
				Timeout = 1000;

				if(Api_Touch::TouchY > 35 && Api_Touch::TouchY < 76) { Wifi(); }
				if(Api_Touch::TouchY > 76 && Api_Touch::TouchY < 117) { /* Bluetooth(); */ }
				if(Api_Touch::TouchY > 117 && Api_Touch::TouchY < 158) { /* Sounds(); */ }
				if(Api_Touch::TouchY > 158 && Api_Touch::TouchY < 199) { /* Display(); */ if(WiFi.status() == WL_CONNECTED) { configTime(3600, 0, "pool.ntp.org"); } }
				if(Api_Touch::TouchY > 199 && Api_Touch::TouchY < 240) { /* System(); */ }
			}

			Timeout++;
			delay(10);
		}
	}
}