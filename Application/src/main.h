// src/main.h

#ifndef MAIN_H
#define MAIN_H

//
#include <Arduino.h>
#include <FastLED.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <ESPAsyncWebServer.h>
#include <painlessMesh.h>
// #include "setup/setup.h"
#include "games/games.h"
#include "music/music.h"
#include "pitches.h"
#include "prototypes.h"

//
#include "broches.h"

// Déclaration des variables externes
extern CRGB color_leds[NUM_LEDS];
extern decode_results results;
extern const uint16_t kRecvPin;
extern IRrecv irrecv;
extern Scheduler userScheduler;

#endif
