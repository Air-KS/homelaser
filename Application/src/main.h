// src/main.h

#ifndef MAIN_H
#define MAIN_H

//
#include <Arduino.h>
#include <FastLED.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "wifi.h"

//
#include "broches.h"

//
extern CRGB color_leds[NUM_LEDS];
extern decode_results results;
extern const uint16_t kRecvPin;
extern IRrecv irrecv;


#endif
