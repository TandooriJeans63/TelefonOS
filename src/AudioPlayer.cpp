#include "AudioPlayer.h"

#include <Arduino.h>

#include "Logger.h"

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

bool AudioPlayer::begin()
{
    Logger::info("Initializing Audio...");

    AudioMemory(16);

    m_codec.enable();

    m_codec.volume(0.8f);

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

    return m_playWav.play(filename);
}

bool AudioPlayer::isPlaying()
{
    return m_playWav.isPlaying();
}
bool AudioPlayer::stop()
{
    Logger::info("STOP.");
    m_playWav.stop();

    return true;
}