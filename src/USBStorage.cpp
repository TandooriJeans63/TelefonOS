#include "USBStorage.h"

#include <Arduino.h>
#include <SD.h>
#include <MTP_Teensy.h>
#include <Globals.h>

void usbStorageBegin()
{
    Serial.println("Initializing MTP...");

    // NE SD.begin() !!!

    MTP.begin();

    MTP.addFilesystem(SD, "TelefonOS");

    Serial.println("MTP READY");
}

void usbStorageUpdate()
{
    if (!usbMode)
        return;
    MTP.loop();
}