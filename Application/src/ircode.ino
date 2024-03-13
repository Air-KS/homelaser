#include "main.h"

#define DATA_PIN 33
#define NUM_LEDS 10
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define SWITCH_COLOR 22

// Définit les paramètres pour les LED : luminosité, couleurs et palette
uint8_t brightness;
CRGB color_leds[NUM_LEDS];


// Configuration des signaux infrarouges
const uint16_t kRecvPin = 36; // Broche de réception
IRrecv irrecv(kRecvPin); // Initialisation du récepteur infrarouge
decode_results results; // Stockage des résultats des signaux
const uint32_t kBaudRate = 115200; // Taux de bauds pour la communication série

// États des différents modes et fonctionnalités
bool switch_colorLed = false;


/*
    --------- --------- --------- --------- ---------- ---------- ----------
  --------- --------- --------- ------------- ---------- ---------- ----------
--------- --------- --------- ----------------- ---------- ---------- ----------
  --------- --------- --------- ------------- ---------- ---------- ----------
    --------- --------- --------- --------- ---------- ---------- ----------
*/


/*
*************************************************
----- Initialisation des paramètres -----
*************************************************
*/
void setup()
{
	// Initialise la communication et Attend qu'elle soit prête = 115200
	Serial.begin(kBaudRate);
	while (!Serial)
	{
		delay(50);
	}

	// Initialise les LED's, définit la luminosité et active la réception infrarouge
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(color_leds, NUM_LEDS);
	FastLED.setBrightness(30);
	irrecv.enableIRIn();

	// Configuration des broches pour les différentes fonctionnalités
	pinMode(SWITCH_COLOR, INPUT_PULLUP);
}


/*
*************************************************
----- Boucle principale du programme -----
*************************************************
*/
void loop()
{
	if (digitalRead(SWITCH_COLOR) == LOW)
	{
		if (!switch_colorLed)
		{
			fill_solid(color_leds, NUM_LEDS, CRGB::White);
			FastLED.show();
		}
		Switch_Color();
	}
}


/*
    --------- --------- --------- --------- ---------- ---------- ----------
  --------- --------- --------- ------------- ---------- ---------- ----------
--------- --------- --------- ----------------- ---------- ---------- ----------
  --------- --------- --------- ------------- ---------- ---------- ----------
    --------- --------- --------- --------- ---------- ---------- ----------
*/

/**
*******************************
* Led_Intensity
* Cette fonction ajuste l'intensité lumineuse des LED.
********************************
*/
void Led_Intensity(uint8_t newBrightness)
{
	brightness = newBrightness;
	FastLED.setBrightness(brightness);
}

/**
********************************
* --- Commentaires
*******************************
*/
// Fonction pour changer de couleur en fonction de la télécommande IR
void Switch_Color()
{
	const unsigned long PROGMEM expectedHex_switch_color_rouge = 0x10001;
	const unsigned long PROGMEM expectedHex_switch_color_vert = 0x10002;
	const unsigned long PROGMEM expectedHex_switch_color_bleu = 0x10003;
	const unsigned long PROGMEM expectedHex_switch_color_blanc = 0x10004;

	if (irrecv.decode(&results))
	{
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
		// Touche 0 de la télécommande
		if (results.value == 0x0 || results.value == 0x10000)
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
