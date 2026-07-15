#pragma once

#include <Arduino.h>
#include <SD.h>

class FileSystem
{
public:
    bool begin();

    bool exists(const char* path);

    File openRead(const char* path);

    File openWrite(const char* path);

    void listRoot();
    void listDirectory(const char* path);

private:
    bool m_initialized{false};
};