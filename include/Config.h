#pragma once

struct ConfigData
{
    char language[8] = "hu";

    int volume = 85;

    int timeout = 30;

    bool dialTone = true;

    char application[32] = "guestbook";
};

class Config
{
public:
    bool begin();

    ConfigData& data();

private:
    ConfigData m_config;
};