#include "AudioPlayer.h"

#include <Arduino.h>

#include "Logger.h"

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

bool AudioPlayer::begin()
{
    Logger::info("Initializing Audio...");

    AudioMemory(32);

    m_codec.enable();
    m_codec.volume(0.8);
    m_codec.inputSelect(AUDIO_INPUT_MIC);
     m_codec.micGain(40);

    m_mixer.gain(0, 1.0f);   // WAV
    m_mixer.gain(1, 1.0f);   // (szabad)
    m_mixer.gain(2, 1.0f);   // Beeper
    m_mixer.gain(3, 0.0f);

    m_beeper.begin(WAVEFORM_SINE);
    m_beeper.frequency(1000);
    m_beeper.amplitude(0);

    Logger::info("Audio ready.");

    return true;
}

void AudioPlayer::update()
{
}

bool AudioPlayer::play(const char* filename)
{
    Logger::info("Playing audio...");

    Logger::info(filename);

    if (m_playWav.isPlaying())
    {
        Logger::info("Already an audio so stop and play again");
        m_playWav.stop();
    }

    bool ok = m_playWav.play(filename);
    delay(20);  
    Serial.print("PLAY RESULT After20ms= ");
    Serial.println(ok);

    return ok;
}

bool AudioPlayer::isPlaying()
{
    bool playing = m_playWav.isPlaying();

    /*Serial.print("isPlaying = ");
    Serial.println(playing);*/

    return playing;
}
bool AudioPlayer::stop()
{
    Logger::info("STOP.");
    m_playWav.stop();

    return true;
}