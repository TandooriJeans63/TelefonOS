#include <Arduino.h>
#include "Phone.h"

Phone phone;

void setup()
{
    phone.begin();
}

void loop()
{
    phone.update();
}