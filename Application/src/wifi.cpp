// src/wifi.cpp

#include "BrokerMQTT.h"
#include "wifi.h"

const char* ssid = "Zana";
const char* password = "Zana.Sohan";

void Init_WiFi()
{
    WiFi.begin(ssid, password);
    unsigned long startTime = millis(); // Enregistre le temps actuel

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connexion au Wi-Fi en cours...");

        // Attendre au moins 10 secondes avant de tenter de se reconnecter
        if (millis() - startTime >= 10000)
        {
            Serial.println("Tentative de reconnexion au Wi-Fi...");
            WiFi.begin(ssid, password);
            startTime = millis(); // Réinitialise le temps actuel
        }
    }
    Serial.println("Wi-Fi Connecter");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
