#include <Arduino.h>
#include "BluetoothSerial.h"
#include <FastLED.h>
#include "games.h"
#include <main.h>

BluetoothSerial SerialBT;

CRGB color_leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_SLAVE"); // Nom Bluetooth de l'esclave
  Serial.println("Slave: Bluetooth initialisé");

  // Initialisation des broches des LED comme sorties
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(color_leds, NUM_LEDS);

	FastLED.setBrightness(30);
  // Initialisation de la réception IR
  irrecv.enableIRIn();
}

void loop() {
  // Si la connexion Bluetooth n'est pas établie, essaie de se connecter au maître
  if (!SerialBT.connected()) {
    SerialBT.connect("ESP32_MASTER"); // Nom Bluetooth du maître
  }

  // Attend un message du maître via Bluetooth
  if (SerialBT.available()) {
    String message = SerialBT.readStringUntil('\n');
    Serial.println("Message from master: " + message);

    // Vérifie si le message reçu est pour lancer le jeu Switch Color
    if (message.equals("START_SWITCH_COLOR")) {
      // Lance le jeu Switch Color
      Switch_Color();
    } else {
      // Si le message reçu n'est pas pour lancer le jeu, envoie-le à la carte maître
      Serial.println("Sending message to master: " + message);
      SerialBT.println(message); // Envoie le message à la carte maître
    }
  }

  delay(1000);
}
