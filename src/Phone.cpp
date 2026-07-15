#include "Phone.h"
#include "Version.h"
#include "Logger.h"
#include "Config.h"
#include "Board.h"
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

    pinMode(Board::LED, OUTPUT);

    digitalWrite(Board::LED, LOW);

    Logger::info(Board::NAME);
    Logger::info(Board::MCU);
    pinScanner.begin();
}

void Phone::update()
{
    if (!initialized)
        return;

    static std::uint32_t lastBlink = 0;
    static bool ledState = false;

    if (millis() - lastBlink >= 500)
    {
        lastBlink = millis();

        ledState = !ledState;

        digitalWrite(Board::LED, ledState);
    }

    pinScanner.update();
}