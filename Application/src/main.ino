#include "main.h"
#include "prototypes.h"
#include "broches.h"

// Définit les paramètres pour les LED : luminosité, couleurs et palette
uint8_t brightness;
CRGB color_leds[NUM_LEDS];
CRGBPalette16 palette = RainbowColors_p;


// Configuration des signaux infrarouges
const uint16_t kRecvPin = 36; // Broche de réception
IRrecv irrecv(kRecvPin); // Initialisation du récepteur infrarouge
decode_results results; // Stockage des résultats des signaux
const uint32_t kBaudRate = 115200; // Taux de bauds pour la communication série


// États des différents modes et fonctionnalités
bool switch_colorLed = false;
bool loading_active = false;
bool buzzer_ON = true;


/*
*************************************************
----- Variable pour les modes de jeux -----
*************************************************
*/
// Réflex Times
bool reflex_time_active = false;
bool reflex_time_running = false;


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
	pinMode(REFLEX_TIME, INPUT_PULLUP);
	pinMode(SWITCH_COLOR, INPUT_PULLUP);
	pinMode(SOUND_PIN, INPUT_PULLUP);
	pinMode(tonePin, OUTPUT);
}


/*
*************************************************
----- Boucle principale du programme -----
*************************************************
*/
void loop()
{
	// Vérifiez si le mode d'entraînement AIM doit être activé
	if (digitalRead(REFLEX_TIME) == HIGH && !reflex_time_active)
	{
		reflex_time_active = true;
		switch_colorLed = false;
		loading_active = true;
		Reflex_Time();
	}
	else if (digitalRead(REFLEX_TIME) == LOW && reflex_time_active)
	{
		reflex_time_active = false;
		loading_active = false;
		fill_solid(color_leds, NUM_LEDS, CRGB::Black); // Éteindre toutes les LEDs
		FastLED.show();
	}
	else if (digitalRead(SWITCH_COLOR) == LOW)
	{
		reflex_time_active = false;
		loading_active = false;
		if (!switch_colorLed)
		{
			loading_active = false;
			fill_solid(color_leds, NUM_LEDS, CRGB::White);
			FastLED.show();
		}
		Switch_Color();
	}
	else if (!reflex_time_active && loading_active)
	{
		loading_active = false;
		fill_solid(color_leds, NUM_LEDS, CRGB::Black); // Éteindre toutes les LEDs
		FastLED.show();
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
void Led_Intensity(uint8_t new_brightness)
{
	brightness = new_brightness;
	FastLED.setBrightness(brightness);
}


/**
********************************
* --- Start_Effect
*******************************
*/
// Fonction pour l'effet de chargement
void Start_Effect()
{
	#define START_DELAY 50 // Délai entre chaque étape de chargement en millisecondes

	// Réglage des paramètres de l'effet de démarrage
	Led_Intensity(200);
	int num_iterations = 3;
	// int delay_PerIteration = 1000;
	CRGB colors[] = {CRGB::Red, CRGB::Orange, CRGB::Green};
	int num_Colors = sizeof(colors) / sizeof(colors[0]);
	bool sound_played = false;

	// Boucle pour chaque tour et arrêter si le chargement n'est plus actif
	for (int i = 0; i < num_iterations && loading_active; i++)
	{
		sound_played = false;

		// Boucle pour chaque LED
		for (int j = 0; j < NUM_LEDS; j++)
		{
			fill_solid(color_leds, NUM_LEDS, CRGB::Black); // Éteindre toutes les LEDs

			// Boucle pour chaque groupe de 3 LED's
			for (int k = 0; k < 3; k++)
			{
				// Changer la couleur des trois LED's
				color_leds[(j + k) % NUM_LEDS] = colors[i % num_Colors];
			}
			FastLED.show();

			// Vérifie si le son n'a pas été joué pour cette itération
			if (buzzer_ON && !sound_played)
			{
				tone(tonePin, 1047, 150); // Do5 (C5), durée de la note : 150 ms
				delay(150);
				noTone(tonePin);
				sound_played = true;
			}
			delay(100); // Attendre un court instant entre les bips
		}
	}

	// Si le chargement est encore actif
	if (loading_active)
	{
		// Allumer toutes les LED's en bleu
		fill_solid(color_leds, NUM_LEDS, CRGB::Blue);
		FastLED.show();

		// Vérifier si le buzzer est activé
		if (buzzer_ON)
		{
			// Jouer le son de commencement
			tone(tonePin, 1294.54, 1000); // Do5 (C5), durée de la note : 800 ms
			delay(1000);
			noTone(tonePin);
		}
		else
		{
			// Attendre 1000 ms sans jouer de son
			delay(1000);
		}

		// Éteindre toutes les LED's
		fill_solid(color_leds, NUM_LEDS, CRGB::Black);
		FastLED.show();
		loading_active = false; // Arrêter le chargement

		if (!reflex_time_running)
		{
			reflex_time_running = true;
			Reflex_Time();
		}
	}
}


/**
********************************
* --- Commentaires
*******************************
*/
void sound()
{
	bool ETAT_SOUND = digitalRead(SOUND_PIN);

	if (ETAT_SOUND)
	{
		buzzer_ON = true;
		Serial.println("Le son est détecté.");
	}
	else
	{
		buzzer_ON = false;
		Serial.println("Le son n'est pas detecté.");
	}
}


/**
********************************
* --- Commentaires
*******************************
*/
// Mode d'entraînement - Réfléx-Time
void Reflex_Time()
{
	// Vérifie si le jeu n'est pas déjà en cours
	if (!reflex_time_running)
	{
		reflex_time_running = true;
		switch_colorLed = false;

		// Appel les fonctions
		Start_Effect();
		delay(1000);
		Led_Intensity(20);

		// Temps de départ du jeu | Temps écouler depuis le début du jeu
		unsigned long start_time = millis();
		unsigned long elapsed_time = 0;

		// Jouer le jeu pendant x temps : 1000 = 1 secondes
		while (elapsed_time < 100000)
		{
			// Sélectionner aléatoirement la couleur à afficher | Vert et Rouge
			CRGB color = random(2) ? CRGB::Green : CRGB::Red;

			// Afficher la couleur pendant 1,5 secondes
			fill_solid(color_leds, NUM_LEDS, color);
			FastLED.show();
			delay(1500);

			// Éteindre les LED's pendant une durée aléatoire entre 0.5 et 3 secondes
			unsigned long offTime = random(500, 3001);
			fill_solid(color_leds, NUM_LEDS, CRGB::Black);
			FastLED.show();
			delay(offTime);

			// Mettre à jou temps écoulé depuis le début du jeu
			elapsed_time = millis() - start_time;
		}

		// Effet de fin de jeu
		endGameEffect();

		// Mettre à jour l'état du jeu pour indiquer qu'il est en cours
		reflex_time_running = false;
	}
}


/**
********************************
* --- Commentaires
*******************************
*/
// Fonction Fin du Jeu
void endGameEffect()
{
	// Définir la vitesse de rotation des couleurs et la luminosité
	uint8_t color_rotation_speed = 2;
	Led_Intensity(200);

	// Boucle infinie pour afficher l'effet de fin de jeu
	while (true)
	{
		// Faire tourner les couleurs et jouer le son
		for (int i = 0; i < NUM_LEDS; i++)
		{
			// Jouer un son pour indiquer la fin du jeu
			tone(tonePin, 1319, 50); // Note Do6 pendant 250 ms
			delay(20);
			tone(tonePin, 1175, 50); // Note La5 pendant 250 ms
			delay(20);
			tone(tonePin, 1047, 50); // Note Do5 pendant 250 ms
			delay(20);

			// Allumer les LED avec la couleur actuelle | Les afficher
			color_leds[i] = ColorFromPalette(RainbowColors_p, millis() / color_rotation_speed + i * 100);
			FastLED.show();

			// Attendre un court instant avant de passer à la LED suivante
			delay(10);
		}

		// Faire clignoter les LEDs doucement
		for (int j = 0; j < 256; j++)
		{
			for (int i = 0; i < NUM_LEDS; i++)
			{
				// Faire disparaître la luminosité lentement
				color_leds[i].fadeToBlackBy(1);
			}

			// Afficher les LEDs | et attendre entre chaque clignotement
			FastLED.show();
			delay(10);
		}
	}
}


/**
********************************
* --- Commentaires
*******************************
*/
// Fonction pour changer de couleur en fonction de la télécommande IR
void Switch_Color()
{
	const unsigned long PROGMEM expectedHex_switch_color_rouge = 0xFF6897;
	const unsigned long PROGMEM expectedHex_switch_color_vert = 0xFF7A85;
	const unsigned long PROGMEM expectedHex_switch_color_bleu = 0xFF52AD;
	const unsigned long PROGMEM expectedHex_switch_color_blanc = 0xFF42BD;

	if (irrecv.decode(&results))
	{
		Serial.print("Code IR reçu: 0x");
		Serial.println(results.value, HEX); // Affiche le code reçu en HEX.

		if (results.value == expectedHex_switch_color_rouge)
		{
			// Change toutes les LEDs en rouge
			fill_solid(color_leds, NUM_LEDS, CRGB(255, 0, 0));
			Serial.println("Switch color Rouge");
			switch_colorLed = true;
			FastLED.show();
		}
		if (results.value == expectedHex_switch_color_vert)
		{
			// Change toutes les LEDs en vert
			fill_solid(color_leds, NUM_LEDS, CRGB(0, 255, 0));
			Serial.println("Switch color Vert");
			switch_colorLed = true;
			FastLED.show();
		}
		if (results.value == expectedHex_switch_color_bleu)
		{
			// Change toutes les LEDs en bleu
			fill_solid(color_leds, NUM_LEDS, CRGB(0, 0, 255));
			Serial.println("Switch color Bleu");
			switch_colorLed = true;
			FastLED.show();
		}
		if (results.value == expectedHex_switch_color_blanc)
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
