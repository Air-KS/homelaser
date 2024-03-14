//src/main.ino

#include "main.h"
#include "pitches.h"
#include "prototypes.h"
#include "broches.h"
#include "music/music.h"
#include "games/games.h"

// Définit les paramètres pour les LED : luminosité, couleurs et palette
uint8_t brightness;
CRGB color_leds[NUM_LEDS];
CRGBPalette16 palette = RainbowColors_p;


// Configuration des signaux infrarouges
const uint16_t kRecvPin = 36; // Broche de réception
IRrecv irrecv(kRecvPin); // Initialisation du récepteur infrarouge
// Stockage des résultats des signaux
const uint32_t kBaudRate = 115200; // Taux de bauds pour la communication série

decode_results results;

// États des différents modes et fonctionnalités
bool wifiConnected = false;
bool ledColorSet = false;
// bool switch_colorLed = false;
bool loading_active = false;
bool buzzer_ON = true;

bool switch_colorLed = false;
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
	Init_WiFi();
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
	// La connexion au Wi-Fi
	if (WiFi.status() != WL_CONNECTED)
	{
		// La carte n'est pas connectée au réseau Wi-Fi
		Serial.println("Connexion Wi-Fi échoué...");
		wifiConnected = false;

		// Définir la couleur des LED en rouge
		fill_solid(color_leds, NUM_LEDS, CRGB::Red);
		FastLED.show();

		// Réinitialiser la variable ledColorSet à false
		ledColorSet = false;
		// Tenter de se reconnecter au réseau Wi-Fi
		Init_WiFi();
	}
	else
	{
		// La carte est connectée au réseau Wi-Fi
		if (!wifiConnected)
		{
			Serial.println("Connexion Wi-Fi réussi...");
			wifiConnected = true;

			// Vérifier si le buzzer est activé
			if (buzzer_ON)
			{
				// Jouer un son positif pour indiquer que la connexion Internet est établie
				tone(tonePin, 440, 200); // La4 (A4), durée de la note : 200 ms
				delay(200);
				noTone(tonePin);
				delay(200);
				tone(tonePin, 880, 200); // La5 (A5), durée de la note : 200 ms
				delay(200);
				noTone(tonePin);
			}

		}
		// Vérifiez si la couleur des LED a déjà été définie
		if (!ledColorSet)
		{
			// Définir la couleur des LED en vert (ou une autre couleur de votre choix)
			fill_solid(color_leds, NUM_LEDS, CRGB::Green);
			FastLED.show(); // Ou strip.show() si vous utilisez la bibliothèque Adafruit NeoPixel

			ledColorSet = true; // Mettre à jour la variable pour indiquer que la couleur des LED a été définie
		}

////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

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
	FastLED.show();
}

/**
********************************
* --- Start_Effect
*******************************
*/
// Fonction pour l'effet de chargement
void Start_Effect()
{
	//Led_Intensity(200);
	#define START_DELAY 50 // Délai entre chaque étape de chargement en millisecondes

	// Réglage des paramètres de l'effet de démarrage
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
// Fonction Fin du Jeu
void End_Game_Effect()
{
	// Définir la vitesse de rotation des couleurs et la luminosité
	uint8_t color_rotation_speed = 2;
	//Led_Intensity(200);

	// Boucle infinie pour afficher l'effet de fin de jeu
	while (true)
	{
		// Faire tourner les couleurs et jouer le son
		for (int i = 0; i < NUM_LEDS; i++)
		{
			// Musique fin de la partie
			// Music_Tapion();
			// Music_Clair_Lune();
			// Little_Start();

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
