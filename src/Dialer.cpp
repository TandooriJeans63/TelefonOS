#include <Arduino.h>
#include "Dialer.h"
#include "Admin.h"
#include "Globals.h"

String dialBuffer = "";


void dialBegin()
{
    dialBuffer = "";
}


void dialKey(char key)
{

    Serial.print("KEY: ");
    Serial.println(key);


    // számok és *
    if(
        (key >= '0' && key <= '9') ||
        key == '*'
      )
    {
        dialBuffer += key;

        Serial.print("BUFFER: ");
        Serial.println(dialBuffer);

        return;
    }



    // lezárás
    if(key == '#')
    {

        Serial.print("DIAL COMPLETE: ");
        Serial.println(dialBuffer);



        // parancs mód
        if(dialBuffer == config.data().admin.code)
        {
            adminEnter();
            //Serial.println("ADMIN MENU");
            //m_audioPlayer.play("/DO_NOT_REMOVE/menu.wav");
        }
        else if(dialBuffer == "*001")
        {
            Serial.println("VOLUME MENU");
        }


        else if(dialBuffer == "*002")
        {
            Serial.println("FILE LIST");
        
            // később ide:
            // fileSystem.listRoot();
        }
        else
        {
            Serial.print("CALL NUMBER: ");
            Serial.println(dialBuffer);
        }


        dialBuffer = "";
    }
}
String getDialBuffer()
{
    return dialBuffer;
}
void clearDialBuffer()
{
    dialBuffer = "";
}