#include "wifi.h"
#include <WiFi.h>

const char* ssid = "Zana";
const char* password = "Zana.Sohan";

void Init_WiFi()
{
    WiFi.begin(ssid, password);
    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connexion au Wi-Fi en cours...");

        if (millis() - startTime >= 10000)
        {
            Serial.println("Tentative de reconnexion au Wi-Fi...");
            WiFi.begin(ssid, password);
            startTime = millis();
        }
    }

    Serial.println("Wi-Fi Connecté");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());
}
