#include "Config.h"
#include "FileSystem.h"

#include <ArduinoJson.h>
#include <SD.h>
#include <string.h>

bool Config::begin(FileSystem& fileSystem)
{
    (void)fileSystem;

    File file = SD.open("/config.json");

    if(!file)
    {
        Serial.println("CONFIG NOT FOUND");
        return false;
    }

    JsonDocument doc;

    if(deserializeJson(doc,file))
    {
        Serial.println("CONFIG PARSE ERROR");
        file.close();
        return false;
    }

    file.close();

    memset(&m_config,0,sizeof(m_config));

    m_config.version = doc["version"] | 1;

    strcpy(m_config.defaultLanguage,
           doc["default_language"] | "hu");

    strcpy(m_config.defaultGreeting,
           doc["default_greeting"] | "/greeting.wav");

    strcpy(m_config.defaultMenu,
           doc["default_menu"] | "/DO_NOT_REMOVE/menu.wav");

    strcpy(m_config.recordingsFolder,
           doc["recordings_folder"] | "/Recordings");
    strcpy(m_config.defaultFolder,
       doc["default_folder"] | "Default");

    strcpy(m_config.admin.code,
           doc["admin"]["code"] | "*746");

    JsonObject langs = doc["languages"];

    m_config.languageCount = 0;

    for(JsonPair kv : langs)
    {
        if(m_config.languageCount >= MAX_LANGUAGES)
            break;

        LanguageConfig &lang =
            m_config.languages[m_config.languageCount++];

        strcpy(lang.id,kv.key().c_str());

        JsonObject obj = kv.value();

        strcpy(lang.key,
               obj["key"] | "");

        strcpy(lang.name,
               obj["name"] | "");

        strcpy(lang.greeting,
               obj["greeting"] | "");

        strcpy(lang.menu,
               obj["menu"] | "");
        strcpy(lang.folder,
       obj["folder"] | "Default");
    }

    Serial.println("CONFIG LOADED");

    return true;
}

ConfigData& Config::data()
{
    return m_config;
}

LanguageConfig* Config::findLanguageByKey(const char* key)
{
    for(int i=0;i<m_config.languageCount;i++)
    {
        if(strcmp(key,m_config.languages[i].key)==0)
            return &m_config.languages[i];
    }

    return nullptr;
}