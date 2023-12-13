#include "weather.h"

#include "apis/display.h"
#include "apis/gps.h"
#include "apis/time.h"
#include "apis/touch.h"
#include "apis/wifi.h"

#include "guis/alert.h"

namespace App_Weather
{
	int Temp = 0;
	int Humu = 50;
	int Wind = 0;
	int Pres = 975;

	int Weather = 0;
	bool IsDay = true;

	int Temps[] = { 0, 0, 0, 0, 0, 0, 0 };
	int Weathers[] = { 0, 0, 0, 0, 0, 0, 0 };
	int Mornings[] = { 0, 0, 0, 0, 0, 0, 0 };
	int Evenings[] = { 0, 0, 0, 0, 0, 0, 0 };

	int Day = 1;
	int Month = 1;
	int Year = 2000;

	String WeatherToIconName(int Weather, bool Wind = false, bool Daytime = true)
	{
		String Result = "";

		if(Weather == 0) { if(Daytime) { Result = "Sun"; } else { Result = "Moon"; } }
		if(Weather == 1) { if(Daytime) { Result = "SunCloud"; } else { Result = "MoonCloud"; } }
		if(Weather == 2) { Result = "Cloud"; } if(Weather == 3) { Result = "Clouds"; }
		if(Weather < 5 && Wind) { if(Weather > 0) { Result = "Wind"; } else { Result = "CloudWind"; } }
		if(Weather >= 40 && Weather <= 49) { if(Daytime) { Result = "SunFog"; } else { Result = "MoonFog"; } }
		if(Weather >= 50 && Weather <= 59) { Result = "Dizzle"; }
		if(Weather >= 60 && Weather <= 69) { Result = "Rain"; }
		if(Weather >= 70 && Weather <= 79) { Result = "Snow"; }
		if(Weather >= 80 && Weather <= 84) { Result = "Rain"; }
		if(Weather >= 85 && Weather <= 89) { Result = "Snow"; }
		if(Weather >= 90 && Weather <= 99) { Result = "Thunder"; }

		return Result;
	}

	void Display(bool Mode)
	{
		int WeekDay = Api_Time::WeekDay(Day, Month, Year);
		String Name = Api_Time::DayName(WeekDay);

		Api_Display::Clear(Color_Black_Dark);

		if(Mode)
		{
			String Windspeed = String(Wind) + " Kmh";
			String Temperature = String(Temp) + "`C";
			if(Temp > 0) { Temperature = "+" + Temperature; }
			String Pressure = String(Pres) + " Ha";
			String Humudity = String(Humu) + "%";

			String Morning = String(Mornings[0] / 1000) + (Mornings[0] % 1000 < 10 ? ":0" : ":") + String(Mornings[0] % 1000);
			String Evening = String(Evenings[0] / 1000) + (Evenings[0] % 1000 < 10 ? ":0" : ":") + String(Evenings[0] % 1000);

			Api_Display::DrawBmp("/Apps/Weather/L/" + WeatherToIconName(Weather, Wind > 9, IsDay) + ".bmp", 5, 5);

			String CityFirst = " ";
			String CityLast = Api_Gps::City;;
			int Index = CityLast.indexOf(' ');
			if (Index < 0) { Index = CityLast.indexOf('-'); }
			if(Index > -1)
			{
				CityFirst = CityLast.substring(0, Index); CityFirst.trim();
				CityLast = CityLast.substring(Index + 1); CityLast.trim();
			}

			if(CityFirst.length() > 10) { CityFirst = CityFirst.substring(0, 9) + '.'; }
			if(CityLast.length() > 10) { CityLast = CityLast.substring(0, 9) + '.'; }
			
			String Code = ' ' + Api_Gps::Code;
			String Country = Api_Gps::Country;
			if(Country.length() > 10) { Country = Country.substring(0, 9) + '.'; }

			Api_Display::DrawText(CityFirst, 175-(6*CityFirst.length()), 10, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(CityLast, 175-(6*CityLast.length()), 35, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Country, 175-(6*Country.length()), 70, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Code, 175-(6*Code.length()), 105, 2, Color_White_Dark, Color_Black_Dark);

			Api_Display::DrawBmp("/Apps/Weather/S/" + Name + ".bmp", 5, 104);
			Api_Display::DrawBmp("/Apps/Weather/S/Temperature.bmp", 205, 140);
			Api_Display::DrawBmp("/Apps/Weather/S/Windspeed.bmp", 5, 140);
			Api_Display::DrawBmp("/Apps/Weather/S/Humudity.bmp", 205, 176);
			Api_Display::DrawBmp("/Apps/Weather/S/Pressure.bmp", 5, 176);
			Api_Display::DrawBmp("/Apps/Weather/S/Evening.bmp", 205, 212);
			Api_Display::DrawBmp("/Apps/Weather/S/Morning.bmp", 5, 212);

			while(Name.length() < 7) { Name = Name + " "; }
			while(Temperature.length() < 7) { Temperature = " " + Temperature; }
			while(Windspeed.length() < 7) { Windspeed = Windspeed + " "; }
			while(Humudity.length() < 7) { Humudity = " " + Humudity; }
			while(Pressure.length() < 7) { Pressure = Pressure + " "; }
			while(Evening.length() < 7) { Evening = " " + Evening; }
			while(Morning.length() < 7) { Morning = Morning + " "; }
			
			Api_Display::DrawText(Name, 40, 114, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Temperature, 116, 150, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Windspeed, 40, 150, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Humudity, 116, 186, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Pressure, 40, 186, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Evening, 116, 222, 2, Color_White_Dark, Color_Black_Dark);
			Api_Display::DrawText(Morning, 40, 222, 2, Color_White_Dark, Color_Black_Dark);
		}
		else
		{
			int CenterX[] = { 40, 120, 200, 40, 120, 200 };
			int CenterY[] = { 40, 40, 40, 155, 155, 155 };

			for (int i = 0; i < 6; i++)
			{
				Name = Api_Time::DayName(WeekDay + i);
				String Temperature = String(Temps[i]);
				if(Temps[i] > 0) { Temperature = "+" + Temperature; }

				Api_Display::DrawBmp("/Apps/Weather/M/" + WeatherToIconName(Weathers[i]) + ".bmp", CenterX[i] - 25, CenterY[i] - 25);
				Api_Display::DrawText(Temperature, CenterX[i] - (Temperature.length() * 6), CenterY[i] + 35, 2, Color_White_Dark, Color_Black_Dark);
				Api_Display::DrawText(Name, CenterX[i] - (Name.length() * 3), CenterY[i] + 60, 1, Color_White_Dark, Color_Black_Dark);
			}
		}
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
				String Current = "&current=temperature_2m,relativehumidity_2m,surface_pressure,is_day,weathercode,windspeed_10m";
				String Daily = "&daily=weathercode,temperature_2m_max,temperature_2m_min,sunrise,sunset";

				String Latitude = "&latitude=" + String(Api_Gps::Latitude, 4);
				String Longitude = "&longitude=" + String(Api_Gps::Longitude, 4);

				String Url = "https://api.open-meteo.com/v1/forecast?timezone=auto" + Latitude + Longitude + Current + Daily;

				if(Api_Wifi::Fetch(Url, true))
				{
                    Temp = (int)(Api_Wifi::ResultJson["current"]["temperature_2m"].as<float>());
                    Humu = (int)(Api_Wifi::ResultJson["current"]["relativehumidity_2m"].as<float>());
                    Wind = (int)(Api_Wifi::ResultJson["current"]["windspeed_10m"].as<float>());
                    Pres = (int)(Api_Wifi::ResultJson["current"]["surface_pressure"].as<float>());

					if(Temp > 99) { Temp = 99; } if(Temp < -99) { Temp = -99; }
					if(Humu > 99) { Humu = 99; } if(Humu < 0) { Humu = 0; }
					if(Wind > 99) { Wind = 99; } if(Wind < 0) { Wind = 0; }
					if(Pres > 1050) { Pres = 1050; } if(Pres < 900) { Pres = 900; }

                    if(Api_Wifi::ResultJson["current"]["is_day"].as<int>() == 0) { IsDay = false; }
                    if(Api_Wifi::ResultJson["current"]["is_day"].as<int>() == 1) { IsDay = true; }
					
                    Weather = (Api_Wifi::ResultJson["current"]["weathercode"].as<int>());

					for (int i = 0; i < 7; i++)
					{
						Weathers[i] = (Api_Wifi::ResultJson["daily"]["weathercode"][i].as<int>());
						Temps[i] = (int)(Api_Wifi::ResultJson["daily"]["temperature_2m_max"][i].as<float>());
						
						if(Temps[i] > 99) { Temps[i] = 99; } if(Temps[i] < -99) { Temps[i] = -99; }

						String Morning = (Api_Wifi::ResultJson["daily"]["sunrise"][i].as<String>()).substring(11);
						String Evening = (Api_Wifi::ResultJson["daily"]["sunset"][i].as<String>()).substring(11);

						Morning.replace(':', '0'); Mornings[i] = atoi(Morning.c_str());
						Evening.replace(':', '0'); Evenings[i] = atoi(Evening.c_str());
					}

					Api_Time::Update();

					Day = Api_Time::Day;
					Month = Api_Time::Month;
					Year = Api_Time::Year;
				}
				else
				{
					Gui_Alert::ShowOk("Error", "Something went    wrong when trying    to fetch your    forecast, please    try again.");
				}
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

		bool Mode = true;

		Display(Mode);

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				Mode = !Mode;

				Display(Mode);
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}