#pragma once

#include <Arduino.h>

class AudioPlayer;

class Beeper
{
public:
    bool begin(AudioPlayer* player);

    void beep3();

    void update();

    bool isPlaying() const;

private:
    AudioPlayer* m_player = nullptr;

    bool m_active = false;
    int m_step = 0;

    elapsedMillis m_timer;
};