#include "Rotary.h"

const uint8_t rows[4] = {29, 30, 31, 32};
const uint8_t cols[4] = {25, 26, 27, 28};


char keys[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

KeyCallback keyCallback = nullptr;

bool keyDown = false;
char stableKey = 0;
char lastDetected = 0;

unsigned long changeTime = 0;

const unsigned long debounceTime = 50;


void rotaryBegin(KeyCallback callback)
{
    keyCallback = callback;
    for(int i = 0; i < 4; i++)
    {
        pinMode(rows[i], INPUT_PULLUP);
        pinMode(cols[i], INPUT_PULLUP);
    }
}

void rotaryUpdate()
{
    char detectedKey = 0;


    for(int c = 0; c < 4; c++)
    {
        pinMode(cols[c], OUTPUT);
        digitalWrite(cols[c], LOW);

        delayMicroseconds(10);


        for(int r = 0; r < 4; r++)
        {
            if(digitalRead(rows[r]) == LOW)
            {
                
                detectedKey = keys[r][c];
                break;
            }
        }


        pinMode(cols[c], INPUT_PULLUP);


        if(detectedKey != 0)
            break;
    }



    // változott amit látunk?
    if(detectedKey != lastDetected)
    {
        lastDetected = detectedKey;
        changeTime = millis();
    }



    // csak akkor fogadjuk el, ha stabil 150ms-ig ugyanaz
    if(millis() - changeTime > debounceTime)
    {

        // új gomb
        if(detectedKey != 0 && !keyDown)
        {
            if(keyCallback)
            {
                keyCallback(detectedKey);
            }
           //Serial.println(detectedKey);

            keyDown = true;
        }


        // felengedés
        if(detectedKey == 0)
        {
            keyDown = false;
        }

    }
}