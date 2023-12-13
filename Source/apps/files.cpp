#include "files.h"

#include "apis/display.h"
#include "apis/touch.h"

namespace App_Files
{
	String Paths[] = { "", "", "", "", "", "", "", "" };

	int PrintDirectory(String Path, int Offset)
	{
		Api_Display::DrawRectangle(0, 0, 240, 26, Color_Black_Light, true);
		Api_Display::DrawRectangle(0, 26, 240, 214, Color_Black_Dark, true);

		Api_Display::DrawText(Path, 6, 6, 2, Color_White_Light, Color_Black_Light);

		fs::File Root = SPIFFS.open("/");

		int Total = 0;

		String Entries[] =
		{
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "",
		};

		for (int i = 0; i < 8; i++)
		{
			Paths[i] = "";
		}

		while(true)
		{
			String Name = Root.getNextFileName();

			if(Name.equalsIgnoreCase("")) { break; }

			if(Name.length() > Path.length())
			{
				if(Name.startsWith(Path))
				{
					Name = Name.substring(Path.length());
					int Index = Name.indexOf('/');

					bool AlreadyHave = false;

					if(Index > 0)
					{
						Name = Name.substring(0, Index);

						for (int i = 0; i < Total; i++)
						{
							if(Entries[i].equalsIgnoreCase(Name))
							{
								AlreadyHave = true;
								break;
							}
						}
					}

					if(!AlreadyHave)
					{
						Entries[Total] = Name;
						Total++;
					}
				}
			}
		}

		if(Offset < 0) { Offset = 0; }
		if(Offset > 56) { Offset = 56; }

		for (int i = 0; i < Total; i++)
		{
			for (int j = 1; j < Total; j++)
			{
				bool HaveDotA = (Entries[j].indexOf('.') > 0);
				bool HaveDotB = (Entries[j-1].indexOf('.') > 0);

				if (!HaveDotA && HaveDotB)
				{
					String Item = Entries[j-1];
					Entries[j-1] = Entries[j];
					Entries[j] = Item;
				}
				
				if(HaveDotA == HaveDotB)
				{
					if(Entries[j] < Entries[j-1])
					{
						String Item = Entries[j-1];
						Entries[j-1] = Entries[j];
						Entries[j] = Item;
					}
				}
			}
		}

		while((Offset > 0) && (Offset + 8) > Total) { Offset--; }

		for (int i = 0; i < 8; i++)
		{
			int Pos = (26 * i) + 32;

			if(!Entries[Offset + i].equalsIgnoreCase(""))
			{
				if(Entries[i].indexOf('.') > 0)
				{
					Api_Display::DrawBmp("/Apps/Files/File.bmp", 6, Pos);

					// Paths[i] = ("/" + Entries[Offset + i]);
				}
				else
				{
					Api_Display::DrawBmp("/Apps/Files/Folder.bmp", 6, Pos);

					Paths[i] = ("/" + Entries[Offset + i]);
				}

				Api_Display::DrawText(Entries[Offset + i], 32, Pos + 8, 1, Color_White_Dark, Color_Black_Dark);
			}
		}
		
		return Offset;
	}

	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear();

		String Path = "";
		int Offset = 0;

		PrintDirectory("/", Offset);

		while(!Exit)
		{
			if(Api_Touch::ReadTouch())
			{
				if(!Api_Touch::Hold && !Api_Touch::Swipe)
				{
					if(Api_Touch::TouchY > 30 && Api_Touch::TouchY < 56) { Path += Paths[0]; Offset = 0; }
					if(Api_Touch::TouchY > 56 && Api_Touch::TouchY < 82) { Path += Paths[1]; Offset = 0; }
					if(Api_Touch::TouchY > 82 && Api_Touch::TouchY < 108) { Path += Paths[2]; Offset = 0; }
					if(Api_Touch::TouchY > 108 && Api_Touch::TouchY < 134) { Path += Paths[3]; Offset = 0; }
					if(Api_Touch::TouchY > 134 && Api_Touch::TouchY < 160) { Path += Paths[4]; Offset = 0; }
					if(Api_Touch::TouchY > 160 && Api_Touch::TouchY < 186) { Path += Paths[5]; Offset = 0; }
					if(Api_Touch::TouchY > 186 && Api_Touch::TouchY < 212) { Path += Paths[6]; Offset = 0; }
					if(Api_Touch::TouchY > 212 && Api_Touch::TouchY < 238) { Path += Paths[7]; Offset = 0; }
				}

				if(Api_Touch::Swipe)
				{
					if(Api_Touch::SwipeVertical)
					{
						if(Api_Touch::TouchY > Api_Touch::SwipeY)
						{
							Offset++;
						}
						if(Api_Touch::TouchY < Api_Touch::SwipeY)
						{
							Offset--;
						}
					}
				}

				if(Api_Touch::Hold)
				{
					if(Path.length() > 1)
					{
						Path = Path.substring(0, Path.lastIndexOf('/'));
					}
				}

				Offset = PrintDirectory(Path + "/", Offset);
			}

			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}