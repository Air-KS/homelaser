/* src/games/Switch_Color.cpp */

/* Library */
#include "games.h"

String colorToString(CRGB color)
{
	return "R:" + String(color.r) + " G:" + String(color.g) + " B:" + String(color.b);
}

/**
********************************
* --- Switch Color
*******************************
*/
// Fonction pour changer de couleur en fonction de la télécommande IR
void Switch_Color() {
	if (digitalRead(SWITCH_COLOR) == LOW && irrecv.decode(&results)) {
		Led_Intensity(30);
		Serial.print("Code IR reçu: 0x");
		Serial.println(results.value, HEX); // Affiche le code reçu en HEX.

		if (switch_colorLed) {
			// Envoyer un message à la carte maître via Bluetooth
			SerialBT.println("Color changed: " + colorToString(color_leds[0])); // Envoyer la couleur de la première LED
			switch_colorLed = false; // Réinitialiser le flag pour éviter l'envoi répété
		}

		switch (results.value) {
			case 0x6D:
			case 0x1006D:
				// Change toutes les LEDs en rouge
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 0, 0));
				SerialBT.println("Couleur changée: Rouge");
				Serial.println("Switch color Rouge");
				switch_colorLed = true;
				break;
			case 0x6E:
			case 0x1006E:
				// Change toutes les LEDs en vert
				fill_solid(color_leds, NUM_LEDS, CRGB(0, 255, 0));
				SerialBT.println("Couleur changée: Vert");
				Serial.println("Switch color Vert");
				switch_colorLed = true;
				break;
			case 0x70:
			case 0x10070:
				// Change toutes les LEDs en bleu
				fill_solid(color_leds, NUM_LEDS, CRGB(0, 0, 255));
				SerialBT.println("Couleur changée:Bleu");
				Serial.println("Switch color Bleu");
				switch_colorLed = true;
				break;
			case 0x6F:
			case 0x1006F:
				// Change toutes les LEDs en Jaune Gold
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 215, 0));
				SerialBT.println("Couleur changée: Jaune-Gold");
				Serial.println("Switch color Jaune");
				switch_colorLed = true;
				break;
			case 0x30:
			case 0x10030:
				// Change toutes les LEDs en blanc
				fill_solid(color_leds, NUM_LEDS, CRGB(255, 255, 255));
				SerialBT.println("Couleur changée: Blanc");
				Serial.println("Switch color Blanc");
				switch_colorLed = true;
				break;
			// Ajoutez des cas pour d'autres valeurs IR si nécessaire
			default:
				// Valeur IR non reconnue
				break;
		}

		FastLED.show();
		irrecv.resume(); // Prépare pour le prochain signal IR
	}
}
