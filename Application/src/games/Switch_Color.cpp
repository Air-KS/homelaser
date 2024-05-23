/* src/games/Switch_Color.cpp */

/* Library */
#include "games.h"

/**
********************************
* --- Switch Color
*******************************
*/
// Fonction pour changer de couleur en fonction de la télécommande IR
void Switch_Color()
{
	if (digitalRead(SWITCH_COLOR) == LOW)
	{
		if (irrecv.decode(&results))
		{
			Led_Intensity(30);

			Serial.print("Code IR reçu: 0x");
			Serial.println(results.value, HEX); // Affiche le code reçu en HEX.

			// Touche couleur Rouge de la télécommande
			if (results.value == 0x6D || results.value == 0x1006D)
			{
				// Change toutes les LEDs en rouge
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 0, 0));
				Serial.println("Switch color Rouge");
				switch_colorLed = true;
				FastLED.show();
			}
			// Touche couleur Vert de la télécommande
			if (results.value == 0x6E || results.value == 0x1006E)
			{
				// Change toutes les LEDs en vert
				fill_solid(color_leds, NUM_LEDS, CRGB(0, 255, 0));
				Serial.println("Switch color Vert");
				switch_colorLed = true;
				FastLED.show();
			}
			// Touche couleur Bleu de la télécommande
			if (results.value == 0x70 || results.value == 0x10070)
			{
				// Change toutes les LEDs en bleu
				fill_solid(color_leds, NUM_LEDS, CRGB(0, 0, 255));
				Serial.println("Switch color Bleu");
				switch_colorLed = true;
				FastLED.show();
			}
			// Touche couleur Jaune de la télécommande
			if (results.value == 0x6F || results.value == 0x1006F)
			{
				// Change toutes les LEDs en Jaune Gold
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 215, 0));
				Serial.println("Switch color Jaune");
				switch_colorLed = true;
				FastLED.show();
			}
			// Touche Pause de la télécommande
			if (results.value == 0x30 || results.value == 0x10030)
			{
				// Change toutes les LEDs en blanc
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 255, 255));
				Serial.println("Switch color Blanc");
				switch_colorLed = true;
				FastLED.show();
			}
			// D'autre condition ici (S'il en a d'autre à l'avenir)

			// Prépare pour le prochain signal IR
			irrecv.resume();
		}
	}
}
