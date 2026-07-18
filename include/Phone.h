#pragma once

#include "FileSystem.h"

#include "AudioPlayer.h"
#include "Recorder.h"
#include "Beeper.h"
#include "HookSwitch.h"
class Phone
{
public:
    void begin();
    void update();
    void playSound(const char* file);
private:
    String nextRecordingName();
    bool m_initialized{false};
    bool m_offHook = false;
    FileSystem m_fileSystem;
    Recorder m_recorder;
    AudioPlayer m_audioPlayer;
    Beeper m_beeper;
    HookSwitch m_hookSwitch;
    enum PhoneState
    {
        PHONE_IDLE,
        PHONE_GREETING,
        PHONE_BEEP,
        PHONE_RECORDING
    };

    PhoneState m_state = PHONE_IDLE;
    String m_recordFolder = "/Recordings/Default";
    uint32_t m_recordIndex = 1;
    elapsedMillis m_greetingDelay;
};