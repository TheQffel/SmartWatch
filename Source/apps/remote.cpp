#include "remote.h"

#include "apis/display.h"
#include "apis/ir.h"
#include "apis/settings.h"
#include "apis/touch.h"
#include "guis/keyboard.h"
#include "guis/select.h"
#include "guis/alert.h"

namespace App_Remote
{
	String Protocol = "";
	uint8_t Length = 16;

	uint16_t Colors[] =
	{
		Color_Red_Light, Color_White_Dark, Color_Grey_Medium, Color_White_Dark, Color_Black_Medium, Color_Red_Medium,
		Color_Green_Light, Color_Grey_Medium, Color_Black_Light, Color_Grey_Medium, Color_Black_Medium, Color_Green_Medium,
		Color_Pink_Medium, Color_White_Dark, Color_Grey_Medium, Color_White_Dark, Color_Black_Medium, Color_Yellow_Light,
		Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_Blue_Light,
		Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_White_Medium, Color_Yellow_Dark,
		Color_Grey_Medium, Color_Grey_Medium, Color_Grey_Medium, Color_Grey_Medium, Color_Grey_Medium, Color_Blue_Dark,
	};

	char Symbols[] =
	{
		'Q', '+', '^', '+', 'i', 'A',
		'!', '<', 'X', '>', 's', 'B', 
		'?', '-', 'v', '-', 'x', 'C', 
		'0', '1', '2', '3', '4', 'D', 
		'5', '6', '7', '8', '9', 'E', 
		'<', '#', '"', '*', '>', 'F', 
	};

	char Buttons[] =
	{
		'U', 'Q', 'M', 'S', 'X', 'A',
		'V', 'O', 'L', 'P', 'Y', 'B',
		'W', 'R', 'N', 'Y', 'Z', 'C',
		'0', '1', '2', '3', '4', 'D',
		'5', '6', '7', '8', '9', 'E',
		'K', 'J', 'I', 'H', 'G', 'F',
	};

	String NumberToText(uint64_t Number)
	{
		char Buffer[24];
		snprintf(Buffer, sizeof(Buffer), "%" PRIu64, Number);
		return String(Buffer);
	}

	void Display()
	{
		Api_Display::Clear(Color_Black_Dark);

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				Api_Display::DrawRectangle(2 + (40 * j), 2 + (40 * i), 36, 36, Color_Brown_Medium);
				Api_Display::DrawRectangle(4 + (40 * j), 4 + (40 * i), 32, 32, Colors[(6 * i) + j]);
				Api_Display::DrawText(Symbols[(6 * i) + j], 12 + (40 * j), 12 + (40 * i), 2, Color_Black_Dark, Colors[(6 * i) + j]);
			}
		}
	}

	bool Menu()
	{
		bool Exit = false;
		
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

		Api_Display::DrawText(Protocol, 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText(Length, 35, 110, 3, Color_Grey_Dark, Color_Grey_Light);

		Api_Display::DrawText('V', 185, 35, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText('+', 140, 110, 3, Color_Grey_Dark, Color_Grey_Light);
		Api_Display::DrawText('-', 185, 110, 3, Color_Grey_Dark, Color_Grey_Light);
		
		Api_Display::DrawText("OK", 100, 185, 3, Color_Grey_Dark, Color_Grey_Light);

		String SelectedProtocol = Protocol;
		uint8_t SelectedLength = Length;

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

							Gui_Select::Item("BOSE");
							Gui_Select::Item("DELONGHI");
							Gui_Select::Item("EPSON");
							Gui_Select::Item("FUJITSU");
							Gui_Select::Item("GORENJE");
							Gui_Select::Item("HITACHI");
							Gui_Select::Item("JVC");
							Gui_Select::Item("LG");
							Gui_Select::Item("MITSUBISHI");
							Gui_Select::Item("NEC");
							Gui_Select::Item("PANASONIC");
							Gui_Select::Item("PIONEER");
							Gui_Select::Item("SAMSUNG");
							Gui_Select::Item("SANYO");
							Gui_Select::Item("SHARP");
							Gui_Select::Item("SONY");
							Gui_Select::Item("TOSHIBA");
							Gui_Select::Item("TOTO");
							Gui_Select::Item("WHIRLPOOL");
							Gui_Select::Item("YORK");

							SelectedProtocol = Gui_Select::Show("");
						}
					}

					if(Api_Touch::TouchY > 95 && Api_Touch::TouchY < 145)
					{
						if(Api_Touch::TouchX > 125 && Api_Touch::TouchX < 175)
						{
							if(SelectedLength < 64) { SelectedLength++; }
						}

						if(Api_Touch::TouchX > 170 && Api_Touch::TouchX < 220)
						{
							if(SelectedLength > 1) { SelectedLength--; }
						}
					}

					if(Api_Touch::TouchY > 170 && Api_Touch::TouchY < 220)
					{
						if(Api_Touch::TouchX > 80 && Api_Touch::TouchX < 160)
						{
							if(SelectedProtocol == "")
							{
								Gui_Alert::ShowOk("Error", "You must select protocol to continue.");
							}
							else
							{
								if(SelectedProtocol != Protocol || SelectedLength != Length)
								{
									Protocol = SelectedProtocol;
									Length = SelectedLength;

									Api_Settings::Remote_Protocol(Protocol);
									Api_Settings::Remote_Length(Length);

									Api_Settings::Update();
								}
							}
						}
					}

					Api_Display::DrawText("       ", 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
					Api_Display::DrawText("    ", 35, 110, 3, Color_Grey_Dark, Color_Grey_Light);

					Api_Display::DrawText(SelectedProtocol, 35, 35, 3, Color_Grey_Dark, Color_Grey_Light);
					Api_Display::DrawText(SelectedLength, 35, 110, 3, Color_Grey_Dark, Color_Grey_Light);
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

	void Main()
	{
		bool Exit = false;

		Protocol = Api_Settings::Remote_Protocol();
		Length = Api_Settings::Remote_Length();

		Api_Touch::ReadButton();

		if(Menu())
		{
			int LastIndex = -1;
			uint64_t Code = 0;

			Display();

			while(!Exit)
			{
				if(Api_Touch::ReadTouch())
				{
					if(Api_Touch::Click)
					{
						int Index = (Api_Touch::TouchX / 40) + ((Api_Touch::TouchY / 40) * 6);
						
						if(LastIndex != Index)
						{
							Code = 0;

							LastIndex = Index;

							if(isDigit(Buttons[Index]))
							{
								Code = Api_Settings::Remote_Number(Buttons[Index]);
							}

							if(isAlpha(Buttons[Index]))
							{
								Code = Api_Settings::Remote_Letter(Buttons[Index]);
							}
						}

						Api_Ir::Send(Protocol, Length, Code);
					}

					if(Api_Touch::Hold)
					{
						int Index = (Api_Touch::TouchX / 40) + ((Api_Touch::TouchY / 40) * 6);
						uint64_t Number = atoll(Gui_Keyboard::NumberInput(false, false).c_str());

						String Text = "Do you want to replace button " + String(Symbols[Index]) + " with value " + NumberToText(Number);
						if(Gui_Alert::ShowYesNo("Question", Text))
						{
							if(isDigit(Buttons[Index]))
							{
								Api_Settings::Remote_Number(Buttons[Index], Number);
							}

							if(isAlpha(Buttons[Index]))
							{
								Api_Settings::Remote_Letter(Buttons[Index], Number);
							}

							Api_Settings::Update();

							LastIndex = -1;
						}

						Display();
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
}