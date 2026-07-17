#ifndef ROTARY_H
#define ROTARY_H

#include <Arduino.h>

typedef void (*KeyCallback)(char);

void rotaryBegin(KeyCallback callback);
void rotaryUpdate();

#endif