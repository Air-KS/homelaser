/* src/games/games.h */

#ifndef REFLEX_TIME_H
#define REFLEX_TIME_H

#include "main.h"

// Réfléx Time
void Reflex_Time();
void playPositiveSound();
void playNegativeSound();

// Switch_Color
void Switch_Color();
void changeColor(String color);

// Variable global
extern bool reflex_time_running;
extern bool switch_colorLed;

#endif
