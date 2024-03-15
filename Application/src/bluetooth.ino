#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32BT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.connected(10)) { // Check if a device is connected for 10 ms
    Serial.println("Connexion réussie !");
    delay(1000); // Attends 1 seconde avant d'afficher un message à nouveau
  }
}
