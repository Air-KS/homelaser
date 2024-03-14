#include <WiFi.h>

const char *ssid = "esp32";
const char *password = "123";

void setup() {
  Serial.begin(115200);
  
  // Initialisation du mode point d'accès
  WiFi.mode(WIFI_AP);

  // Configuration du point d'accès avec un SSID et un mot de passe
  WiFi.softAP(ssid, password);

  Serial.println("Point d'accès WiFi démarré");
  Serial.print("Adresse IP du point d'accès: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Vérifier si un client est connecté
  if (WiFi.softAPgetStationNum() > 0) {
    Serial.println("Je suis connecté !");
    delay(1000); // Attente d'une seconde avant de répéter le message
  }
}
