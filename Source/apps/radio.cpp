#include "radio.h"

#include "apis/display.h"
#include "apis/touch.h"

namespace App_Radio
{
	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear();

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