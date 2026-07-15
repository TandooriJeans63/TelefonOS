#pragma once

#include <Audio.h>

class AudioPlayer
{
public:
    bool begin();

    void update();

    bool play(const char* filename);

    bool isPlaying() const;

private:
    AudioPlaySdWav m_playWav;

    AudioOutputI2S m_i2s;

    AudioConnection m_patchCord{m_playWav, 0, m_i2s, 0};
    AudioConnection m_patchCord2{m_playWav, 1, m_i2s, 1};

    AudioControlSGTL5000 m_codec;
};