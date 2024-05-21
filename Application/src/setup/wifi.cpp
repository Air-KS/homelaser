/*****
	./src/setup/wifi.cpp
 *****/

#include "prototypes.h"
#include <WiFi.h>
#include "setup.h"

const char* ssid = "Zana";
const char* password = "Zana.Sohan";

void Init_WiFi() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	unsigned long startTime = millis(); // Enregistre le temps actuel

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) { // Attendre jusqu'à 30 secondes
    delay(1000);
    Serial.print("Statut Wi-Fi: ");
    Serial.println(WiFi.status()); // Affiche le statut Wi-Fi
    Serial.println("Connexion au Wi-Fi en cours...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi Connecté");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Échec de la connexion au Wi-Fi. Vérifiez les identifiants.");
  }
}

void Init_Mesh() {
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
}

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}
