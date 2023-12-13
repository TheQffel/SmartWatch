#include "calendar.h"

#include "apis/display.h"
#include "apis/time.h"
#include "apis/touch.h"

namespace App_Calendar
{
	void Refresh(int Year, int Month, int Day = -1)
	{
		Api_Display::DrawRectangle(0, 0, 240, 34, Color_Blue_Medium);
		Api_Display::DrawRectangle(0, 34, 240, 26, Color_Green_Medium);

		Api_Display::DrawRectangle(0, 60, 240, 30, Color_Cyan_Dark);
		Api_Display::DrawRectangle(0, 90, 240, 30, Color_Cyan_Light);
		Api_Display::DrawRectangle(0, 120, 240, 30, Color_Cyan_Dark);
		Api_Display::DrawRectangle(0, 150, 240, 30, Color_Cyan_Light);
		Api_Display::DrawRectangle(0, 180, 240, 30, Color_Cyan_Dark);
		Api_Display::DrawRectangle(0, 210, 240, 30, Color_Cyan_Light);

		int DayOfWeek = Api_Time::WeekDay(1, Month, Year) - 1;

		Api_Display::DrawText(Api_Time::MonthName(Month), 10, 10, 2, Color_Black_Dark, Color_Blue_Medium);
		Api_Display::DrawText(String(Year), 180, 10, 2, Color_Black_Dark, Color_Blue_Medium);

		Api_Display::DrawText(Api_Time::DayName(1)[0], 20, 40, 2, Color_Black_Dark, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(2)[0], 52, 40, 2, Color_Black_Dark, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(3)[0], 84, 40, 2, Color_Black_Dark, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(4)[0], 116, 40, 2, Color_Black_Dark, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(5)[0], 148, 40, 2, Color_Black_Dark, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(6)[0], 180, 40, 2, Color_Black_Light, Color_Green_Medium);
		Api_Display::DrawText(Api_Time::DayName(7)[0], 212, 40, 2, Color_Red_Medium, Color_Green_Medium);

		for(int i = 0; i < Api_Time::DaysInMonth(Month, Year); i++)
		{
			int Row = ((DayOfWeek + i) / 7);
			int Col = ((DayOfWeek + i) % 7);

			int RowPx = Row * 30 + 68;
			int ColPx = Col * 32 + 14;

			if(i < 9) { ColPx += 6; }

			int16_t Color = Color_Black_Medium;
			if(Col == 5) { Color = Color_Grey_Medium; }
			if(Col == 6) { Color = Color_Red_Medium; }

			if(Day - 1 == i) { Color = Color_Blue_Medium; }

			if(Row % 2 == 0)
			{
				Api_Display::DrawText((i + 1), ColPx, RowPx, 2, Color, Color_Cyan_Dark);
			}
			else
			{
				Api_Display::DrawText((i + 1), ColPx, RowPx, 2, Color, Color_Cyan_Light);
			}
		}
	}

	void Main()
	{
		bool Exit = false;

		Api_Touch::ReadButton();

		int Year = Api_Time::Year;
		int Month = Api_Time::Month;
		int Day = Api_Time::Day;

		Refresh(Year, Month, Day);

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				if(Api_Touch::Swipe)
				{
					if(Api_Touch::SwipeHorizontal)
					{
						if(Api_Touch::TouchX > Api_Touch::SwipeX)
						{
							Month++;
						}
						if(Api_Touch::TouchX < Api_Touch::SwipeX)
						{
							Month--;
						}
					}
					if(Api_Touch::SwipeVertical)
					{
						if(Api_Touch::TouchY > Api_Touch::SwipeY)
						{
							Year++;
						}
						if(Api_Touch::TouchY < Api_Touch::SwipeY)
						{
							Year--;
						}
					}

					if(Month > 12)
					{
						Month = 1;
						Year++;
					}
					if(Month < 1)
					{
						Month = 12;
						Year--;
					}

					if(Year == Api_Time::Year && Month == Api_Time::Month)
					{
						Refresh(Year, Month, Day);
					}
					else
					{
						Refresh(Year, Month);
					}
				}

				if(Api_Touch::Hold)
				{
					
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