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
    else
    {
        m_fileSystem.listRoot();
        m_fileSystem.listDirectory("/DO_NOT_REMOVE");
        m_fileSystem.listDirectory("/Recordings");
    }

    //=========================================================
    // Configuration
    //=========================================================

    if (!m_config.begin(m_fileSystem))
    {
        Logger::warning("Configuration not loaded.");
    }


    m_audioPlayer.begin();
    m_hookSwitch.begin(Board::HOOK_SWITCH);

    //=========================================================
    // Debug modules
    //=========================================================

   
    //=========================================================
    // Finished
    //=========================================================

    m_initialized = true;

    Logger::info("System initialized.");
    dialBuffer = "";
    Serial.println("PHONE READY");
    //delay(500);
    //m_audioPlayer.play("/greeting.wav");
}

void Phone::update()
{
    if (!m_initialized)
    {
        return;
    }

    m_hookSwitch.update();
    
    if (m_hookSwitch.lifted())
    {
        Logger::info("HANDSET LIFTED");
        Serial.print("Calling: ");
        Serial.println(dialBuffer);
        
        m_audioPlayer.play("/greeting.wav");
    }
    
    if (m_hookSwitch.replaced())
    {
        Logger::info("HANDSET REPLACED");
        dialBuffer = "";
        m_audioPlayer.stop();
    }
    m_audioPlayer.update();    
}

void Phone::handleKey(char key)
{

    if(
        (key >= '0' && key <= '9') ||
        key == '*' ||
        key == '#'
      )
    {

        dialBuffer += key;


        Serial.print("DIAL BUFFER: ");
        Serial.println(dialBuffer);

    }

}