#include "FileSystem.h"

#include <SD.h>

bool FileSystem::begin()
{
    // TODO:
    // Itt fogjuk inicializálni a Teensy Audio Shield SD kártyáját.

    m_initialized = false;

    return m_initialized;
}

bool FileSystem::exists(const char* path)
{
    return SD.exists(path);
}

File FileSystem::openRead(const char* path)
{
    return SD.open(path, FILE_READ);
}

File FileSystem::openWrite(const char* path)
{
    return SD.open(path, FILE_WRITE);
}