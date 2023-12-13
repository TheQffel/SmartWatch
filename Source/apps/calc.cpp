#include "calc.h"

#include "apis/display.h"
#include "apis/touch.h"

namespace App_Calc
{
	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear(Color_Black_Medium);
		Api_Display::DrawBmp("/Apps/Calc/Calc.bmp", 0, 60);

		bool Calculate = false;
		double Result = 0;
		String Text = "";
        char Input[24];
        int Index = 0;

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				if(!Api_Touch::Swipe && !Api_Touch::Hold)
				{
					if(Api_Touch::TouchX > 0 && Api_Touch::TouchX < 48)
					{
						if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 108)
						{
							if(Index < 24)
							{
								Input[Index] = '7';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 152)
						{
							if(Index < 24)
							{
								Input[Index] = '4';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 152 && Api_Touch::TouchY < 196)
						{
							if(Index < 24)
							{
								Input[Index] = '1';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 196 && Api_Touch::TouchY < 240)
						{
							if(Index < 24)
							{
								Input[Index] = '0';
								Index++;
							}
						}
					}
					if(Api_Touch::TouchX > 48 && Api_Touch::TouchX < 96)
					{
						if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 108)
						{
							if(Index < 24)
							{
								Input[Index] = '8';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 152)
						{
							if(Index < 24)
							{
								Input[Index] = '5';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 152 && Api_Touch::TouchY < 196)
						{
							if(Index < 24)
							{
								Input[Index] = '2';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 196 && Api_Touch::TouchY < 240)
						{
							if(Index < 24)
							{
								Input[Index] = '.';
								Index++;
							}
						}
					}
					if(Api_Touch::TouchX > 96 && Api_Touch::TouchX < 144)
					{
						if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 108)
						{
							if(Index < 24)
							{
								Input[Index] = '9';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 152)
						{
							if(Index < 24)
							{
								Input[Index] = '6';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 152 && Api_Touch::TouchY < 196)
						{
							if(Index < 24)
							{
								Input[Index] = '3';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 196 && Api_Touch::TouchY < 240)
						{
							if(Index < 24)
							{
								Input[Index] = '=';
								Index++;
								
								Calculate = true;
							}
						}
					}
					if(Api_Touch::TouchX > 144 && Api_Touch::TouchX < 192)
					{
						if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 108)
						{
							if(Index < 24)
							{
								Input[Index] = '+';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 152)
						{
							if(Index < 24)
							{
								Input[Index] = '-';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 152 && Api_Touch::TouchY < 196)
						{
							if(Index < 24)
							{
								Input[Index] = '*';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 196 && Api_Touch::TouchY < 240)
						{
							if(Index < 24)
							{
								Input[Index] = '/';
								Index++;
							}
						}
					}
					if(Api_Touch::TouchX > 192 && Api_Touch::TouchX < 240)
					{
						if(Api_Touch::TouchY > 64 && Api_Touch::TouchY < 108)
						{
							Index = 0;
						}
						if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 152)
						{
							if(Index > 0)
							{
								Index--;
							}
						}
						if(Api_Touch::TouchY > 152 && Api_Touch::TouchY < 196)
						{
							if(Index < 24)
							{
								Input[Index] = '^';
								Index++;
							}
						}
						if(Api_Touch::TouchY > 196 && Api_Touch::TouchY < 240)
						{
							if(Index < 24)
							{
								Input[Index] = '&';
								Index++;
							}
						}
					}
				}
				
				Text = "";

				Api_Display::DrawRectangle(0, 0, 240, 60, Color_Black_Medium, true);

				if(Calculate)
				{
					Result = 0;

					char Operation = '+';
					String Number = "";

					for (int i = 0; i < Index; i++)
					{
						if((Input[i] > 47 && Input[i] < 58) || Input[i] == 44 || Input[i] == 46)
						{
							Number += Input[i];
						}
						else
						{
							if(Number.length() > 0)
							{
								if(Operation == '+')
								{
									Result += Number.toDouble();
								}
								if(Operation == '-')
								{
									Result -= Number.toDouble();
								}
								if(Operation == '*')
								{
									Result *= Number.toDouble();
								}
								if(Operation == '/')
								{
									Result /= Number.toDouble();
								}
							}

							Operation = Input[i];

							Number = "";
						}
					}

					for (int i = 8; i > -1; i--)
					{
						Text = String(Result, i);

						if(Text[Text.length() - 1] != '0')
						{
							break;
						}
					}
					
					Text.trim();
					Index = Text.length();

					for (int i = 0; i < Index; i++)
					{
						Input[i] = Text[i];
					}

					Text = '=' + Text;
					
					Calculate = false;
				}
				else
				{
					for (int i = 0; i < Index; i++)
					{
						Text += Input[i];
					}
				}

				Api_Display::DrawText(Text, 5, 5, 3, Color_White_Medium, Color_Black_Medium, 230);
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}