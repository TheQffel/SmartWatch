#include "terminal.h"

#include "apis/console.h"
#include "apis/display.h"
#include "apis/touch.h"

namespace App_Terminal
{
	void Display(bool Mode)
	{
		Api_Display::Clear();

		for (int i = 2; i < 25; i++)
		{
			Api_Display::DrawText(Api_Console::Message(i, Mode).substring(0, 38), 6, (10 * i) - 14, 1, Api_Console::Color(i), Color_Black_Dark);
		}
	}

	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		bool Mode = false;

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