/* src/bluetooth.ino */

/**************
* Carte esclave
***************/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

BluetoothSerial SerialBT;

const char* targetDeviceName = "esp32"; // Remplacez "NomDeVotreAppareil" par le nom de votre appareil cible
bool isConnected = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Nom du périphérique Bluetooth

  Serial.println("Le périphérique a démarré, vous pouvez maintenant le connecter via Bluetooth !");
  SerialBT.register_callback(btCallback);
}

void loop() {
  if (!isConnected) {
    SerialBT.connect(targetDeviceName); // Tente automatiquement de se connecter au périphérique cible
    delay(5000); // Attend 5 secondes avant de vérifier à nouveau la connexion
  }
}

void btCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Connexion Bluetooth établie !");
    isConnected = true;
    // Envoyer un message lorsque la connexion est établie
    SerialBT.println("Appareil 1 se joint à la connexion");
  } else if (event == ESP_SPP_CLOSE_EVT) {
    Serial.println("Connexion Bluetooth fermée !");
    isConnected = false;
  }
}
