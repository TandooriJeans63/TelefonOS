#include "Beeper.h"
#include "AudioPlayer.h"

bool Beeper::begin(AudioPlayer* player)
{
    m_player = player;
    return true;
}

void Beeper::beep3()
{
    m_step = 0;
    m_timer = 0;
    m_active = true;
}

bool Beeper::isPlaying() const
{
    return m_active;
}

void Beeper::update()
{
    if(!m_active)
        return;

    switch(m_step)
    {
        case 0:
            m_player->beeper().amplitude(0.5);
            m_timer = 0;
            m_step++;
            break;

        case 1:
            if(m_timer > 120)
            {
                m_player->beeper().amplitude(0);
                m_timer = 0;
                m_step++;
            }
            break;

        case 2:
            if(m_timer > 120)
            {
                m_player->beeper().amplitude(0.5);
                m_timer = 0;
                m_step++;
            }
            break;

        case 3:
            if(m_timer > 120)
            {
                m_player->beeper().amplitude(0);
                m_timer = 0;
                m_step++;
            }
            break;

        case 4:
            if(m_timer > 120)
            {
                m_player->beeper().amplitude(0.5);
                m_timer = 0;
                m_step++;
            }
            break;

        case 5:
            if(m_timer > 120)
            {
                m_player->beeper().amplitude(0);
                m_active = false;
            }
            break;
    }
}