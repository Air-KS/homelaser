// srcBrokerMQTT.cpp

#include <WiFi.h>
#include <PubSubClient.h>
#include  "BrokerMQTT.h"

const char* mqtt_server = "adresse_ip_du_broker_mqtt"; // Adresse IP du serveur MQTT
const char* mqtt_topic = "topic/vers/esclave";

WiFiClient espClient;
PubSubClient client(espClient);

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
    Init_WiFi(); // Utiliser la fonction Init_WiFi() pour initialiser la connexion Wi-Fi
    client.setServer(mqtt_server, 1883); // Utilise l'adresse IP du serveur MQTT
    client.setCallback(callback);
}

void BrokerMQTT_loop() {
    if (!client.connected()) {
        if (client.connect("ESP32Client")) {
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
            return;
        }
    }
    client.loop();
}
