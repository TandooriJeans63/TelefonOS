#include "Phone.h"
#include "Version.h"
#include "Logger.h"
#include "Config.h"
#include <cstdint>
#include <Arduino.h>

Config config;

void Phone::begin()
{
    Logger::begin();

    Logger::info("==============================");
    Logger::info(FW_NAME);
    Logger::info(FW_VERSION);
    Logger::info(FW_BUILD_DATE);
    Logger::info(FW_BUILD_TIME);
    Logger::info("==============================");

    config.begin();

    initialized = true;
}

void Phone::update()
{
    if (!initialized)
        return;

    static uint32_t timer = 0;

    if (millis() - timer > 5000)
    {
        timer = millis();

        Logger::info("Firmware running...");
    }
}