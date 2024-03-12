// src/music/clair_lune.cpp

#include "pitches.h"
#include "broches.h"

/**
********************************
* ----- Musique -----
* Au clair de la Lune
*******************************
*/
void Music_Clair_Lune()
{
	tone(tonePin, NOTE_4DO, 500);
	delay(520);
	tone(tonePin, NOTE_4DO, 500);
	delay(520);
	tone(tonePin, NOTE_4DO, 500);
	delay(520);
	tone(tonePin, NOTE_4RE, 500);
	delay(520);
	tone(tonePin, NOTE_4MI, 1000);
	delay(1020);
	tone(tonePin, NOTE_4RE, 500);
	delay(1000);
	tone(tonePin, NOTE_4DO, 500);
	delay(520);
	tone(tonePin, NOTE_4MI, 500);
	delay(520);
	tone(tonePin, NOTE_4RE, 500);
	delay(520);
	tone(tonePin, NOTE_4RE, 500);
	delay(520);
	tone(tonePin, NOTE_4DO, 1000);
	delay(5000);
	return;
}
