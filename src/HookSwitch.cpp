#include "HookSwitch.h"

constexpr int HOOK_LOW_THRESHOLD  = 300;
constexpr int HOOK_HIGH_THRESHOLD = 550;

bool HookSwitch::begin(uint8_t pin)
{
    m_pin = pin;

    pinMode(pin, INPUT);

    m_lastValue = analogRead(pin);

    return true;
}

void HookSwitch::update()
{
    int value = analogRead(m_pin);

    // leesett az analóg érték
    if (!m_waitRise && value < HOOK_LOW_THRESHOLD  && m_lastValue > HOOK_HIGH_THRESHOLD)
    {
        m_lifted = true;
        m_waitRise = true;
    }

    // visszaemelkedett
    if (m_waitRise && value > HOOK_HIGH_THRESHOLD)
    {
        m_replaced = true;
        m_waitRise = false;
    }

    m_lastValue = value;
}

bool HookSwitch::lifted()
{
    bool r = m_lifted;
    m_lifted = false;
    return r;
}

bool HookSwitch::replaced()
{
    bool r = m_replaced;
    m_replaced = false;
    return r;
}