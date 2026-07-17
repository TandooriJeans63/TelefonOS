#pragma once

#include "Config.h"
#include "FileSystem.h"
#include "AudioPlayer.h"
#include "HookSwitch.h"
class Phone
{
public:
    void begin();
    void update();
    void handleKey(char key);
private:
    bool m_initialized{false};
    bool m_offHook = false;
    String dialBuffer = "";
    Config m_config;
    FileSystem m_fileSystem;
    
    AudioPlayer m_audioPlayer;
    HookSwitch m_hookSwitch;
};