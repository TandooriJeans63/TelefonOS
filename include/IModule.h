#pragma once

class IModule
{
public:
    virtual ~IModule() = default;

    virtual bool begin() = 0;

    virtual void update() = 0;
};