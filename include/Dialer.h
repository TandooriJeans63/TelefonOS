#pragma once

#include <Arduino.h>

void dialBegin();
void dialKey(char key);
String getDialBuffer();
void clearDialBuffer();