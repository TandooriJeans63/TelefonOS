#include "HookSwitch.h"

constexpr int HOOK_LOW_THRESHOLD  = 300;
constexpr int HOOK_HIGH_THRESHOLD = 550;
constexpr int HOOK_DEBOUNCE       = 50;

bool HookSwitch::begin(uint8_t pin)
{
    m_pin = pin;

    pinMode(pin, INPUT);

    // Stabil induló érték
    delay(300);

    int sum = 0;

    for (int i = 0; i < 20; i++)
    {
        sum += analogRead(pin);
        delay(5);
    }

    int value = sum / 20;

    Serial.print("INITIAL HOOK = ");
    Serial.println(value);

    if (value < HOOK_LOW_THRESHOLD)
        m_state = OFF_HOOK;
    else
        m_state = ON_HOOK;

    m_lifted = false;
    m_replaced = false;
    m_lastChange = millis();

    return true;
}

void HookSwitch::update()
{
    int value = analogRead(m_pin);
    if (m_firstRead)
    {
        if (value > HOOK_HIGH_THRESHOLD)
        {
            m_state = ON_HOOK;
            m_firstRead = false;
        }
        else if (value < HOOK_LOW_THRESHOLD)
        {
            m_state = OFF_HOOK;
            m_firstRead = false;
        }

        return;
    }

    switch (m_state)
    {
        case ON_HOOK:

            if (value < HOOK_LOW_THRESHOLD)
            {
                if (millis() - m_lastChange > HOOK_DEBOUNCE)
                {
                    m_state = OFF_HOOK;
                    m_lifted = true;

                    Serial.println("HOOK LIFTED");
                }
            }
            else
            {
                m_lastChange = millis();
            }

            break;

        case OFF_HOOK:

            if (value > HOOK_HIGH_THRESHOLD)
            {
                if (millis() - m_lastChange > HOOK_DEBOUNCE)
                {
                    m_state = ON_HOOK;
                    m_replaced = true;

                    Serial.println("HOOK REPLACED");
                }
            }
            else
            {
                m_lastChange = millis();
            }

            break;
    }
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