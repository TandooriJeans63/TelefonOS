#include "FileSystem.h"

#include <SD.h>

#include "Logger.h"

static constexpr uint8_t SD_CS_PIN = 10;

bool FileSystem::begin()
{
    Logger::info("Initializing SD card...");

    if (!SD.begin(BUILTIN_SDCARD))
    {
        Logger::error("SD initialization failed.");

        m_initialized = false;
        return false;
    }

    Logger::info("SD initialized.");

    m_initialized = true;

    return true;
}

bool FileSystem::exists(const char* path)
{
    if (!m_initialized)
        return false;

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

void FileSystem::listRoot()
{
    if (!m_initialized)
    {
        Logger::warning("Filesystem not initialized.");
        return;
    }

    Logger::info("Root directory:");

    File root = SD.open("/");

    File file = root.openNextFile();

    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("[DIR ] ");
        }
        else
        {
            Serial.print("[FILE] ");
        }

        Serial.print(file.name());

        if (!file.isDirectory())
        {
            Serial.print(" (");
            Serial.print(file.size());
            Serial.print(" bytes)");
        }

        Serial.println();

        file.close();

        file = root.openNextFile();
    }

    root.close();
}

void FileSystem::listDirectory(const char* path)
{
    if (!m_initialized)
    {
        Logger::warning("Filesystem not initialized.");
        return;
    }

    Serial.print("\n=== ");
    Serial.print(path);
    Serial.println(" ===");

    File dir = SD.open(path);

    if (!dir || !dir.isDirectory())
    {
        Logger::error("Directory not found.");
        return;
    }

    File file = dir.openNextFile();

    while (file)
    {
        if (file.isDirectory())
            Serial.print("[DIR ] ");
        else
            Serial.print("[FILE] ");

        Serial.print(file.name());

        if (!file.isDirectory())
        {
            Serial.print(" (");
            Serial.print(file.size());
            Serial.print(" bytes)");
        }

        Serial.println();

        file.close();
        file = dir.openNextFile();
    }

    dir.close();
}