#include "Config.h"

bool Config::begin()
{
    return true;
}

ConfigData& Config::data()
{
    return m_config;
}