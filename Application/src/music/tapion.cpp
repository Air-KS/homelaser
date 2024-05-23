// src/music/tapion.cpp

#include "pitches.h"
#include "broches.h"

/**
********************************
* ----- Musique -----
* Au clair de la Lune
*******************************
*/
void Music_Tapion()
{
	tone(tonePin, NOTE_5DO, 450);
	delay(470);
	tone(tonePin, NOTE_5DO, 450);
	delay(470);
	tone(tonePin, NOTE_5FA, 950);
	delay(1250);

	tone(tonePin, NOTE_6DO, 450);
	delay(470);
	tone(tonePin, NOTE_5LA_D, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL_D, 450);
	delay(470);
	tone(tonePin, NOTE_5LA_D, 950);
	delay(1250);

	tone(tonePin, NOTE_5FA, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL_D, 1050);
	delay(1150);

	tone(tonePin, NOTE_5SOL_D, 450);
	delay(470);
	tone(tonePin, NOTE_5LA_D, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL_D, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL, 950);
	delay(1250);

	//////////////////
	tone(tonePin, NOTE_5DO, 450);
	delay(470);
	tone(tonePin, NOTE_5DO, 450);
	delay(470);
	tone(tonePin, NOTE_5FA, 950);
	delay(1150);

	tone(tonePin, NOTE_6DO, 450);
	delay(470);
	tone(tonePin, NOTE_5LA_D, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL_D, 450);
	delay(470);
	tone(tonePin, NOTE_5LA_D, 950);
	delay(1250);

	tone(tonePin, NOTE_5FA, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL_D, 1050);
	delay(1250);

	tone(tonePin, NOTE_5SOL_D, 450);
	delay(470);
	tone(tonePin, NOTE_5SOL, 800);
	delay(850);
	tone(tonePin, NOTE_5FA, 450);
	delay(470);
	tone(tonePin, NOTE_5RE_D, 450);
	delay(470);
	tone(tonePin, NOTE_5FA, 1200);
	delay(1450);

	delay(4500);
	return;
}
