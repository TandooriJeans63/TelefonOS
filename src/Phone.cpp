#include <Arduino.h>
#include <cstdint>

#include "Board.h"
#include "Config.h"
#include "Logger.h"
#include "Phone.h"
#include "Version.h"

void Phone::begin()
{
     Serial.begin(115200);

    delay(5000);

    Serial.println();
    Serial.println("================================");
    Serial.println("TelefonOS BOOT");
    Serial.println("================================");
    //=========================================================
    // Logger
    //=========================================================

    Logger::begin();

    Logger::info("========================================");
    Logger::info(FW_NAME);
    Logger::info(FW_VERSION);
    Logger::info(FW_BUILD_DATE);
    Logger::info(FW_BUILD_TIME);
    Logger::info("========================================");

    //=========================================================
    // Hardware
    //=========================================================

    pinMode(Board::LED, OUTPUT);
    digitalWrite(Board::LED, LOW);

    Logger::info(Board::NAME);
    Logger::info(Board::MCU);

    //=========================================================
    // File system
    //=========================================================

    Logger::info("Initializing filesystem...");

    if (!m_fileSystem.begin())
    {
        Logger::warning("Filesystem not initialized.");
    }

    //=========================================================
    // Configuration
    //=========================================================

    if (!m_config.begin(m_fileSystem))
    {
        Logger::warning("Configuration not loaded.");
    }

    //=========================================================
    // Debug modules
    //=========================================================

    //if (!m_pinScanner.begin())
    //{
    //    Logger::warning("PinScanner initialization failed.");
    //}

    //=========================================================
    // Finished
    //=========================================================

    m_initialized = true;

    Logger::info("System initialized.");
}

void Phone::update()
{
    if (!m_initialized)
    {
        return;
    }

    static std::uint32_t lastBlink{0};
    static bool ledState{false};

    if (millis() - lastBlink >= 500)
    {
        lastBlink = millis();

        ledState = !ledState;

        digitalWrite(Board::LED, ledState);
    }

    //m_pinScanner.update();
}