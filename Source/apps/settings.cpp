#include "settings.h"

#include "apis/display.h"
#include "apis/touch.h"
#include "apis/wifi.h"

#include "guis/keyboard.h"

namespace App_Settings
{
	void Main()
	{
		bool Exit = false;
		
		Api_Display::Clear();

		Api_Touch::ReadButton();

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				// to do
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}