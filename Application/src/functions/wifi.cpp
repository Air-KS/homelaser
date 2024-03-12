// src/functions/wifi.cpp

#include "prototypes.h"
#include "wifi.h"

const char* ssid = "Zana";
const char* password = "Zana.Sohan";

void Init_WiFi()
{
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Connexion au Wi-Fi en cours...");
	}
	Serial.println("Wi-Fi Connecter");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}
