#pragma once

#include "Config.h"
#include "FileSystem.h"
#include "PinScanner.h"

class Phone
{
public:
    void begin();
    void update();

private:
    bool m_initialized{false};

    Config m_config;
    FileSystem m_fileSystem;
    PinScanner m_pinScanner;
};