#include <Arduino.h>
#include "Logger.h"

void Logger::begin()
{
    Serial.begin(115200);

    while (!Serial && millis() < 3000)
    {
    }
}

void Logger::info(const char* text)
{
    Serial.print("[INFO] ");
    Serial.println(text);
}

void Logger::warning(const char* text)
{
    Serial.print("[WARN] ");
    Serial.println(text);
}

void Logger::error(const char* text)
{
    Serial.print("[ERROR] ");
    Serial.println(text);
}