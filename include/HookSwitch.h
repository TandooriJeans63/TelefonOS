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
    uint8_t m_pin = 255;

    int m_lastValue = 0;

    bool m_lifted = false;

    bool m_replaced = false;

    bool m_waitRise = false;
    
};