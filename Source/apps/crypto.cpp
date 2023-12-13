#include "crypto.h"

#include "apis/display.h"
#include "apis/touch.h"
#include "apis/wifi.h"

#include "guis/alert.h"

namespace App_Crypto
{
	String ApiUrl = F("http://192.168.1.9/crypto/?currency=");

	double Tether = 0;
	double Bitcoin = 0;
	double Ethereum = 0;
	double Chia = 0;
	double Monero = 0;
	double Litecoin = 0;

	void Main()
	{
		bool Exit = false;
		
		Api_Touch::ReadButton();

		Api_Display::Clear(Color_Black_Medium);

		if(Api_Wifi::Connected())
		{
			Api_Display::DrawText("Loading", 15, 15, 4, Color_White_Medium, Color_Black_Medium);

			if(Api_Wifi::Fetch(ApiUrl + "USDT")) { Tether = Api_Wifi::ResultText.toDouble(); }

			Api_Display::DrawText(".", 50, 50, 4, Color_White_Medium, Color_Black_Medium);

			if(Api_Wifi::Fetch(ApiUrl + "BTC")) { Bitcoin = Api_Wifi::ResultText.toDouble(); }

			Api_Display::DrawText(".", 75, 50, 4, Color_White_Medium, Color_Black_Medium);

			if(Api_Wifi::Fetch(ApiUrl + "ETH")) { Ethereum = Api_Wifi::ResultText.toDouble(); }

			Api_Display::DrawText(".", 100, 50, 4, Color_White_Medium, Color_Black_Medium);

			if(Api_Wifi::Fetch(ApiUrl + "XCH")) { Chia = Api_Wifi::ResultText.toDouble(); }

			Api_Display::DrawText(".", 125, 50, 4, Color_White_Medium, Color_Black_Medium);
			
			if(Api_Wifi::Fetch(ApiUrl + "XMR")) { Monero = Api_Wifi::ResultText.toDouble(); }

			Api_Display::DrawText(".", 150, 50, 4, Color_White_Medium, Color_Black_Medium);

			if(Api_Wifi::Fetch(ApiUrl + "LTC")) { Litecoin = Api_Wifi::ResultText.toDouble(); }

			Api_Display::Clear(Color_Black_Medium);
		}
		else
		{
			Gui_Alert::ShowOk("Error", "You must connect    to a WiFi network    to use this app.");

			Api_Display::Clear(Color_Black_Medium);
		}

		Api_Display::DrawBmp("/Apps/Crypto/Tether.bmp", 5, 5);
		Api_Display::DrawText(String(Tether, 2), 45, 10, 3, Color_White_Medium, Color_Black_Medium);

		Api_Display::DrawBmp("/Apps/Crypto/Bitcoin.bmp", 5, 45);
		Api_Display::DrawText(String(Bitcoin, 2), 45, 50, 3, Color_White_Medium, Color_Black_Medium);
		
		Api_Display::DrawBmp("/Apps/Crypto/Ethereum.bmp", 5, 85);
		Api_Display::DrawText(String(Ethereum, 2), 45, 90, 3, Color_White_Medium, Color_Black_Medium);

		Api_Display::DrawBmp("/Apps/Crypto/Chia.bmp", 5, 125);
		Api_Display::DrawText(String(Chia, 2), 45, 130, 3, Color_White_Medium, Color_Black_Medium);

		Api_Display::DrawBmp("/Apps/Crypto/Monero.bmp", 5, 165);
		Api_Display::DrawText(String(Monero, 2), 45, 170, 3, Color_White_Medium, Color_Black_Medium);

		Api_Display::DrawBmp("/Apps/Crypto/Litecoin.bmp", 5, 205);
		Api_Display::DrawText(String(Litecoin, 2), 45, 210, 3, Color_White_Medium, Color_Black_Medium);

		while(!Exit)
		{
			if(Api_Touch::ReadButton())
			{
				Exit = true;
			}

			delay(10);
		}
	}
}