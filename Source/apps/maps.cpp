#include "maps.h"

#include "apis/display.h"
#include "apis/gps.h"
#include "apis/touch.h"
#include "apis/wifi.h"

#include "guis/alert.h"

namespace App_Maps
{
	double Longitude = 0;
	double Latitude = 0;

	void Display()
	{
		// https://api.mapbox.com/styles/v1/mapbox/streets-v12/static/
	}

	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear();

		Api_Display::DrawText("Loading...", 15, 210, 3, Color_Grey_Light, Color_Black_Dark);

		if(Api_Wifi::Connected())
		{
			if(Api_Gps::Locate())
			{
				Longitude = (((int)(Api_Gps::Longitude * 100)) * 0.01);
				Latitude = (((int)(Api_Gps::Latitude * 100)) * 0.01);
			}
			else
			{
				Gui_Alert::ShowOk("Error", "Something went    wrong when trying    to get your    location, please    try again.");
			}
		}
		else
		{
			Gui_Alert::ShowOk("Error", "You must connect    to a WiFi network    to use this app.");
		}

		Display();

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				if(Api_Touch::Hold)
				{

				}

				if(Api_Touch::Swipe)
				{
					if(Api_Touch::SwipeHorizontal)
					{
						if(Api_Touch::TouchX > Api_Touch::SwipeX) { Longitude += 0.01; }
						if(Api_Touch::TouchX < Api_Touch::SwipeX) { Longitude -= 0.01; }
					}

					if(Api_Touch::SwipeVertical)
					{
						if(Api_Touch::TouchY > Api_Touch::SwipeY) { Latitude += 0.005; }
						if(Api_Touch::TouchY < Api_Touch::SwipeY) { Latitude -= 0.005; }
					}
				}

				Display();
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}