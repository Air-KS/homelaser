#include <Arduino.h>
#include "BrokerMQTT.h"

void setup()
{
    Serial.begin(115200);
    BrokerMQTT_setup();
}

void loop()
{
    BrokerMQTT_loop();
}
