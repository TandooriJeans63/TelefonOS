#include <Arduino.h>
#include "Admin.h"
#include "Phone.h"

extern Phone phone;

bool adminMode = false;


void adminBegin()
{
    adminMode = false;
}


bool adminActive()
{
    return adminMode;
}


void adminEnter()
{
    adminMode = true;

    Serial.println("ADMIN MODE");
}


void adminKey(char key)
{

    if(!adminMode)
        return;


    Serial.print("ADMIN KEY: ");
    Serial.println(key);



    switch(key)
    {

        case '1':

            Serial.println("DELETE LAST RECORDING");

            // TODO:
            // Recorder::deleteLast();

            break;



        case '2':

            Serial.println("START NEW RECORDING");

            // TODO:
            // Recorder::start();

            break;



        case '3':

            Serial.println("PLAY ALL RECORDINGS");

            // TODO:
            // Recorder::playAll();

            break;
        case '#':

            Serial.println("EXIT ADMIN");

            adminMode=false;

            break;

        default:

            break;
    }
}