#pragma once

#include <Arduino.h>
#include <cstdint>

#include "IModule.h"

class PinScanner final : public IModule
{
public:

    bool begin() override;

    void update() override;

private:

    static constexpr std::uint8_t FIRST_PIN = 0;
    static constexpr std::uint8_t LAST_PIN  = 39;

    bool m_lastState[40]{};

    std::uint32_t m_lastPrint = 0;
};