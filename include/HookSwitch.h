#pragma once

#include <Arduino.h>

class HookSwitch
{
public:
    bool begin(uint8_t pin);

    void update();

    bool lifted();

    bool replaced();

private:
      enum State
    {
        ON_HOOK,
        OFF_HOOK
    };

    State m_state = ON_HOOK;

    uint8_t m_pin = 0;

    bool m_lifted = false;
    bool m_replaced = false;

    unsigned long m_lastChange = 0;
    bool m_firstRead = true;
};