#pragma once

#include "PinScanner.h"

class Phone
{
public:

    void begin();

    void update();

private:

    bool initialized = false;

    PinScanner pinScanner;
};