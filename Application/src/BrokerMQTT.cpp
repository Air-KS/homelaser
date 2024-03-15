#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "BrokerMQTT.h"
#include <NTPClient.h>

const char* mqtt_server = "cf3ed55ea6f44d9b99ce451a954dbd68.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_topic = "Bienvenue !";

WiFiClientSecure espClient;
PubSubClient client(espClient);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600; // Décalage horaire en secondes (par exemple, pour GMT+1)
const int   daylightOffset_sec = 3600; // Décalage horaire pour l'heure d'été en secondes (0 si non applicable)

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

void reconnect () {
    while(!client.connected()) {
        Serial.print("\nConnected to");
    }
}
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void BrokerMQTT_setup() {
    Serial.begin(115200);
    Init_WiFi(); // Initialise le WiFi

    // Charger le certificat SSL à partir du fichier hivemq.jks
    espClient.setCACert("hivemq.jks");

    // Initialise l'horloge NTP
    timeClient.begin();
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    if (!client.connect("ESP32Client")) {
        Serial.println("Erreur de connexion au serveur MQTT");
        return;
    }

    client.subscribe(mqtt_topic);
}

void BrokerMQTT_loop() {
    client.loop();
}
