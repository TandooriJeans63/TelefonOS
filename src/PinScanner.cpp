#include "PinScanner.h"

#include "Logger.h"

bool PinScanner::begin()
{
    Logger::info("PinScanner starting...");

    for (std::uint8_t pin = FIRST_PIN; pin <= LAST_PIN; ++pin)
    {
        pinMode(pin, INPUT_PULLUP);

        m_lastState[pin] = digitalRead(pin);
    }

    Logger::info("PinScanner ready.");

    return true;
}

void PinScanner::update()
{
    for (std::uint8_t pin = FIRST_PIN; pin <= LAST_PIN; ++pin)
    {
        bool state = digitalRead(pin);

        if (state != m_lastState[pin])
        {
            m_lastState[pin] = state;

            Serial.print("PIN ");
            Serial.print(pin);
            Serial.print(" -> ");
            Serial.println(state ? "HIGH" : "LOW");
        }
    }
}