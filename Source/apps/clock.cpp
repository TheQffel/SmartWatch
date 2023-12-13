#include "clock.h"

#include "apis/battery.h"
#include "apis/console.h"
#include "apis/display.h"
#include "apis/settings.h"
#include "apis/time.h"
#include "apis/touch.h"
#include "apis/wifi.h"

#include "guis/alert.h"
#include "guis/select.h"

namespace App_Clock
{
	uint8_t Style = 1;
	int8_t Gmt = 0;

	String GmtToText(int Number)
	{
		if (Number == 0) { return "GMT 0"; }

		String Hour = String(abs(Number / 4));
		String Minute = String(abs((Number % 4) * 15));

		if (Hour.length() < 2)
		{
			if (Number < 0) { Hour = "-" + Hour; }
			if (Number > 0) { Hour = "+" + Hour; }
		}

		if (Minute.length() < 2) { Minute += "0"; }
		
		return Hour + ":" + Minute;
	}

	String StyleToText(int Number)
	{
		String Result = "Style " + Number;

		if (Number == 0) { Result = "Random"; }
		if (Number == 1) { Result = "Analog"; }
		if (Number == 2) { Result = "Digital"; }

		return Result;
	}

	bool Menu()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear(Color_Black_Medium);

		Api_Display::DrawRectangle(20, 20, 200, 50, Color_Grey_Dark);
		Api_Display::DrawRectangle(20, 95, 200, 50, Color_Grey_Dark);
		Api_Display::DrawRectangle(80, 170, 80, 50, Color_Grey_Dark);

		Api_Display::DrawRectangle(25, 25, 145, 40, Color_Grey_Light);
		Api_Display::DrawRectangle(175, 25, 40, 40, Color_Grey_Light);

		Api_Display::DrawRectangle(25, 100, 100, 40, Color_Grey_Light);
		Api_Display::DrawRectangle(130, 100, 40, 40, Color_Grey_Light);
		Api_Display::DrawRectangle(175, 100, 40, 40, Color_Grey_Light);

		Api_Display::DrawRectangle(85, 175, 70, 40, Color_Grey_Light);

		Api_Display::DrawText(StyleToText(Style), 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText(GmtToText(Gmt), 30, 110, 3, Color_Grey_Dark, Color_Grey_Light);

		Api_Display::DrawText('V', 185, 35, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText('+', 140, 110, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText('-', 185, 110, 3, Color_Grey_Dark, Color_Grey_Light);
		
		Api_Display::DrawText("OK", 100, 185, 3, Color_Grey_Dark, Color_Grey_Light);

		uint8_t SelectedStyle = Style;
		int8_t SelectedGmt = Gmt;

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				if(Api_Touch::Click)
				{
					if(Api_Touch::TouchY > 20 && Api_Touch::TouchY < 70)
					{
						if(Api_Touch::TouchX > 20 && Api_Touch::TouchX < 220)
						{
							Gui_Select::Clear();

							for(int i = 0; i < 10; i++)
							{
								Gui_Select::Item(StyleToText(i));
							}

							SelectedStyle = Gui_Select::Show(SelectedStyle);
						}
					}

					if(Api_Touch::TouchY > 95 && Api_Touch::TouchY < 145)
					{
						if(Api_Touch::TouchX > 125 && Api_Touch::TouchX < 175)
						{
							if(SelectedGmt < 48) { SelectedGmt++; }
						}

						if(Api_Touch::TouchX > 170 && Api_Touch::TouchX < 220)
						{
							if(SelectedGmt > -48) { SelectedGmt--; }
						}
					}

					if(Api_Touch::TouchY > 170 && Api_Touch::TouchY < 220)
					{
						if(Api_Touch::TouchX > 80 && Api_Touch::TouchX < 160)
						{
							if(SelectedStyle != Style || SelectedGmt != Gmt)
							{
								Style = SelectedStyle;
								Gmt = SelectedGmt;

								Api_Settings::Style(Style);
								Api_Settings::Timezone(Gmt);

								Api_Settings::Update();
							}

							break;
						}
					}

					Api_Display::DrawText("       ", 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
					Api_Display::DrawText("    ", 35, 110, 3, Color_Grey_Dark, Color_Grey_Light);

					Api_Display::DrawText(StyleToText(SelectedStyle), 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
					Api_Display::DrawText(GmtToText(SelectedGmt), 30, 110, 3, Color_Grey_Dark, Color_Grey_Light);
				}
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}

		return !Exit;
	}

	void Main(bool Sleep)
	{
		bool Exit = false;

		Style = Api_Settings::Style();
		Gmt = Api_Settings::Timezone();

		Api_Touch::ReadButton();

		int Timeout = 10000;

		if(!Sleep)
		{
			Timeout = 0;
			
			Api_Display::DrawBmp("/System/Clock.bmp", 0, 0);
		}

		while(!Exit)
		{
			if(Timeout > 2500)
			{
				Api_Display::Toggle(false);

				SmartWatch->rtc->syncToRtc();
				SmartWatch->power->clearIRQ();
				SmartWatch->bma->readInterrupt();

				gpio_wakeup_enable((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL);
				gpio_wakeup_enable((gpio_num_t)BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
				gpio_wakeup_enable((gpio_num_t)RTC_INT, GPIO_INTR_LOW_LEVEL);
				gpio_wakeup_enable((gpio_num_t)TOUCH_INT, GPIO_INTR_LOW_LEVEL);

				SmartWatch->touch->setPowerMode(FOCALTECH_PMODE_MONITOR);

				Api_Console::Log(Api_Console::LogType::Other, "System goes to sleep at " + String(Api_Battery::Percentage()) + '%');

				delay(250);
				setCpuFrequencyMhz(80);
				esp_sleep_enable_gpio_wakeup();
				delay(500); Api_Battery::Reset();
				esp_light_sleep_start();
				setCpuFrequencyMhz(240);
				delay(250);

				Api_Console::Log(Api_Console::LogType::Other, "System wakes up at " + String(Api_Battery::Percentage()) + '%');

				SmartWatch->touch->setPowerMode(FOCALTECH_PMODE_ACTIVE);

				SmartWatch->power->clearIRQ();
				SmartWatch->bma->readInterrupt();
				SmartWatch->rtc->syncToSystem();
    
				SmartWatch->tft->fillScreen(0);
				Api_Display::DrawBmp("/System/Clock.bmp", 0, 0);
				Api_Time::SyncScheduled = true;
				
            	Api_Display::Toggle(true);

				Timeout = 0;
			}

			if((Timeout % 25) == 0)
			{
				Api_Time::Update(true);

				SmartWatch->tft->fillCircle(120, 120, 70, 0);

				float HourAngle = ((((Api_Time::Hour + 9) % 12) + (Api_Time::Minute / 60.0f)) * 30 * PI) / 180;
				int HourX = 120 + (40 * cos(HourAngle));
				int HourY = 120 + (40 * sin(HourAngle));

				float MinuteAngle = (((Api_Time::Minute + 45) % 60) * 6 * PI) / 180;
				int MinuteX = 120 + (60 * cos(MinuteAngle));
				int MinuteY = 120 + (60 * sin(MinuteAngle));

				float SecondAngle = (((Api_Time::Second + 45) % 60) * 6 * PI) / 180;
				int SecondX = 120 + (65 * cos(SecondAngle));
				int SecondY = 120 + (65 * sin(SecondAngle));

				SmartWatch->tft->drawLine(120, 120, HourX, HourY, SmartWatch->tft->color565(250, 250, 250));
				SmartWatch->tft->drawLine(120, 120, MinuteX, MinuteY, SmartWatch->tft->color565(250, 250, 250));
				SmartWatch->tft->drawLine(120, 120, SecondX, SecondY, SmartWatch->tft->color565(250, 0, 0));

				if(!Sleep) { Timeout = 0; }
			}

			Timeout++;

			if(Api_Touch::ReadTouch())
			{
				if(!Sleep)
				{
					if(Menu())
					{
						Api_Time::SyncScheduled = true;

						if(Api_Wifi::Connected())
						{
							Api_Time::Update();
						}
						else
						{
							Gui_Alert::ShowOk("Warning", "Time zone set, but you are not conne-cted to internet. Your time will be synchronised after you connect to the internet.");
						}

						Api_Display::DrawBmp("/System/Clock.bmp", 0, 0);
					}
					else
					{
						Exit = true;
					}
				}
				else
				{
					Exit = true;
				}
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}