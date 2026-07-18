#include <Arduino.h>
#include "Phone.h"
#include "Rotary.h"
#include "Dialer.h"
#include "Admin.h"
#include "USBStorage.h"
Phone phone;

void rotaryKey(char key)
{
    Serial.print("PHONE KEY: ");
    Serial.println(key);
    if(adminActive())
    {
        adminKey(key);
    }
    else
    {
        dialKey(key);
    }
    //phone.handleKey(key);
}

void setup()
{
    Serial.begin(115200);
    phone.begin();
    
    dialBegin();
    adminBegin();
    rotaryBegin(rotaryKey);
    usbStorageBegin();
}
void loop()
{
    phone.update();
    
    rotaryUpdate();
    usbStorageUpdate();
}