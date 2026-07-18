#include <Arduino.h>
#include <cstdint>

#include "Board.h"
#include "Logger.h"
#include "Phone.h"
#include "Version.h"
#include "Dialer.h"
#include "Admin.h"
#include "Globals.h"


void Phone::begin()
{
   Serial.begin(115200);

    delay(5000);

    Serial.println();
    Serial.println("================================");
    Serial.println("TelefonOS BOOT");
    Serial.println("================================");

    Logger::begin();

    Logger::info("========================================");
    Logger::info(FW_NAME);
    Logger::info(FW_VERSION);
    Logger::info(FW_BUILD_DATE);
    Logger::info(FW_BUILD_TIME);
    Logger::info("========================================");

    pinMode(Board::LED, OUTPUT);
    digitalWrite(Board::LED, LOW);
    Logger::info(Board::NAME);
    Logger::info(Board::MCU);

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

    if (!config.begin(m_fileSystem))
    {
        Logger::warning("Configuration not loaded.");
    }

    m_audioPlayer.begin();
    m_beeper.begin(&m_audioPlayer);
    m_recorder.begin();
    m_hookSwitch.begin(Board::HOOK_SWITCH);

    m_initialized = true;

    Logger::info("System initialized.");
    //delay(500);
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
        usbMode = false;
        Logger::info("HANDSET LIFTED");
        String number = getDialBuffer();


        Serial.print("CALLING: ");
        Serial.println(number);
        if(adminActive())
        {
            Serial.println("ADMIN MENU START");
           // m_audioPlayer.play("/DO_NOT_REMOVE/menu.wav");
            m_audioPlayer.play(config.data().defaultMenu);
        }
        else
        {
            LanguageConfig* lang = config.findLanguageByKey(number.c_str());
            if(lang)
            {
                m_recordFolder = "/Recordings/";
                m_recordFolder += lang->folder;
                if(m_audioPlayer.play(lang->greeting)){
                    m_state = PHONE_GREETING;
                    m_greetingDelay = 0;
                }
            }
            else
            {
                m_recordFolder = "/Recordings/Default";
                if(m_audioPlayer.play(config.data().defaultGreeting)){
                    m_state = PHONE_GREETING;
                    m_greetingDelay = 0;
                }
            }
            
        }

       
    }
    
    if (m_hookSwitch.replaced())
    {
        Logger::info("HANDSET REPLACED");
        clearDialBuffer();
        m_audioPlayer.stop();
        m_recorder.stop();
        adminBegin();
        usbMode = true;
        m_state = PHONE_IDLE;
    }
    m_audioPlayer.update(); 
    m_beeper.update();
    m_recorder.update();
    switch(m_state)
        {
        case PHONE_GREETING:
        usbMode = false;
        if(m_greetingDelay < 100)
            break;
        if(!m_audioPlayer.isPlaying())
        {
            Logger::info("BEEEEEEEEEO");
            m_beeper.beep3();

            m_state = PHONE_BEEP;
        }

        break;


        case PHONE_BEEP:

            if(!m_beeper.isPlaying())
            {
                String file = nextRecordingName();

                Logger::info(file.c_str());

                m_recorder.start(file.c_str());

                m_state = PHONE_RECORDING;
            }

            break;


        case PHONE_RECORDING:

            break;

        default:
            break;
    }
}

void Phone::playSound(const char* file)
{
    m_audioPlayer.play(file);
}

String Phone::nextRecordingName()
{
    uint16_t index = 1;

    while(true)
    {
        char filename[128];

        sprintf(filename,
                "%s/rec%04d.wav",
                m_recordFolder.c_str(),
                index);

        if(!m_fileSystem.exists(filename))
            return String(filename);

        index++;
    }
}