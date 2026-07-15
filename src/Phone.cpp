#include <Arduino.h>
#include "Phone.h"

void Phone::begin()
{
    Serial.begin(115200);

    while (!Serial && millis() < 3000)
    {
    }

    Serial.println();
    Serial.println("==========================");
    Serial.println("TelefonOS");
    Serial.println("Version 0.0.1");
    Serial.println("==========================");

    initialized = true;
}

void Phone::update()
{
    if (!initialized)
        return;

    static unsigned long last = 0;

    if (millis() - last > 5000)
    {
        last = millis();

        Serial.println("TelefonOS running...");
    }
}