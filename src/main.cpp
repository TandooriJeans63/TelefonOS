#include <Arduino.h>
#include "Phone.h"
#include "Rotary.h"
Phone phone;

void rotaryKey(char key)
{
    Serial.print("PHONE KEY: ");
    Serial.println(key);

    phone.handleKey(key);
}

void setup()
{
    Serial.begin(115200);

    phone.begin();

    rotaryBegin(rotaryKey);
}
void loop()
{
    phone.update();

    rotaryUpdate();
}