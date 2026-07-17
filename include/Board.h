#pragma once

#include <Arduino.h>
#include <cstdint>

/**
 * @brief Hardver configuration.
 *
 * every GPIO pin, hardver version and constans that related to the hardver 
 * exclusively it appear in this file only.
 */
namespace Board
{
    //====================================================
    // Board information
    //====================================================

    constexpr char NAME[] = "BenVrieLink Audio Guestbook";
    constexpr char MCU[]  = "Teensy 4.1";

    //====================================================
    // Built-in hardware
    //====================================================

    constexpr std::uint8_t LED = LED_BUILTIN;

    //====================================================
    // Hook switch
    //====================================================

    constexpr std::uint8_t HOOK_SWITCH = 40;   // TODO

    //====================================================
    // Rotary dial
    //====================================================

    constexpr std::uint8_t ROTARY_PULSE = 255;  // TODO
    constexpr std::uint8_t ROTARY_READY = 255;  // TODO

    //====================================================
    // Audio
    //====================================================

    constexpr std::uint8_t SPEAKER_ENABLE = 255; // TODO

}