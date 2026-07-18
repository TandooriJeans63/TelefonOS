#pragma once

#include <Audio.h>

class AudioPlayer
{
public:
    bool begin();

    void update();

    bool play(const char* filename);

    bool isPlaying();
    bool stop();
      AudioMixer4& mixer()
    {
        return m_mixer;
    }

    AudioSynthWaveform& beeper()
    {
        return m_beeper;
    }
private:
    AudioPlaySdWav      m_playWav;
    AudioSynthWaveform  m_beeper;
    AudioMixer4         m_mixer;
    AudioOutputI2S      m_i2s;

    
    AudioConnection p1{m_playWav,0,m_mixer,0};
    AudioConnection p2{m_playWav,1,m_mixer,1};

    AudioConnection p3{m_beeper,0,m_mixer,2};

    AudioConnection p4{m_mixer,0,m_i2s,0};
    AudioConnection p5{m_mixer,0,m_i2s,1};

    AudioControlSGTL5000 m_codec;
};