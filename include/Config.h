#pragma once

class FileSystem;
#define MAX_LANGUAGES 10

struct LanguageConfig
{
    char id[8];
    char key[8];
    char name[32];
    char folder[16];
    char greeting[64];
    char menu[64];
};

struct ConfigData
{
    uint8_t version;

    char defaultLanguage[8];
    char defaultFolder[16];
    char defaultGreeting[64];
    char defaultMenu[64];

    char recordingsFolder[64];

    LanguageConfig languages[MAX_LANGUAGES];
    uint8_t languageCount;

    struct
    {
        char code[16];
    } admin;

    int volume;
    int timeout;
    bool dialTone;

    char application[32];
};

class Config
{
public:

    bool begin(FileSystem& fileSystem);

    ConfigData& data();

    LanguageConfig* findLanguageByKey(const char* key);

private:

    ConfigData m_config;
};