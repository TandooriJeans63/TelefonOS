#include "Config.h"

#include "FileSystem.h"

bool Config::begin(FileSystem& fileSystem)
{
    (void)fileSystem;

    return true;
}

ConfigData& Config::data()
{
    return m_config;
}