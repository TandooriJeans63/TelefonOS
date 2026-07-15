#pragma once

class Logger
{
public:
    static void begin();
    static void info(const char* text);
    static void warning(const char* text);
    static void error(const char* text);
};