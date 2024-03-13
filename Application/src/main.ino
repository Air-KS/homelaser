//src/main.ino

#include "main.h"
#include "pitches.h"
#include "prototypes.h"
#include "broches.h"
#include "music/music.h"

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
bool wifiConnected = false;
bool ledColorSet = false;
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
*************************************************
----- Variable de Test -----
*************************************************
*/
const unsigned long PROGMEM expectedHex_touche_0 = 0x10000;
const unsigned long PROGMEM expectedHex_touche_1 = 0x10001;
const unsigned long PROGMEM expectedHex_touche_2 = 0x10002;
const unsigned long PROGMEM expectedHex_touche_3 = 0x10003;
const unsigned long PROGMEM expectedHex_touche_4 = 0x10004;
const unsigned long PROGMEM expectedHex_touche_5 = 0x10005;
const unsigned long PROGMEM expectedHex_volume_up = 0x10020;
const unsigned long PROGMEM expectedHex_volume_down = 0x10021;


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

	// Ajoute la détection de la télécommande infrarouge ici
	if (irrecv.decode(&results))
	{
		Serial.println("Télécommande détectée !");
		Serial.println(results.value, HEX);
		irrecv.resume(); // Continue à écouter les signaux IR
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
* --- Mode de jeu ---
* *** Réfléx-Time ***
*******************************
*/

void Reflex_Time() {
    int score_red = 0;
    int score_green = 0;

    // Constantes
    const int GAME_DURATION = 30000; // Durée du jeu en millisecondes
    const int MIN_OFF_TIME = 500; // Temps minimum d'extinction des LED en millisecondes
    const int MAX_OFF_TIME = 3000; // Temps maximum d'extinction des LED en millisecondes

    Serial.println("Début du jeu, préparation...");
    delay(1000); // Délai initial pour la préparation
    Serial.println("Jeu démarré.");

    // Vérifie si le jeu n'est pas déjà en cours
    if (!reflex_time_running) {
        reflex_time_running = true;

        Start_Effect();
        Led_Intensity(20);

        // Temps de départ du jeu
        unsigned long start_time = millis();

        while (millis() - start_time < GAME_DURATION) {
            CRGB color = random(2) ? CRGB::Green : CRGB::Red;
            bool isColorGreen = (color == CRGB::Green);

            fill_solid(color_leds, NUM_LEDS, color);
            FastLED.show();

            Serial.print("Affichage couleur ");
            Serial.println(isColorGreen ? "Verte" : "Rouge");
            delay(5); // Petite pause avant de commencer à accepter les tirs

            unsigned long display_time = random(MIN_OFF_TIME, MAX_OFF_TIME);
            Serial.print("Durée d'affichage : ");
            Serial.println(display_time);

            unsigned long display_start_time = millis();
            bool target_hit = false;

            while (millis() - display_start_time < display_time && !target_hit) {
                if (irrecv.decode(&results)) {
                    Serial.print("Signal IR reçu : 0x");
                    Serial.println(results.value, HEX);

                    if ((results.value == 0x6D || results.value == 0x1006D) && !isColorGreen) {
                        score_red++;
                        Serial.println("Cible Rouge touché +1 point");
						tone(tonePin, 1000, 100);
						delay(5);
                    } else if ((results.value == 0x6E || results.value == 0x1006E) && isColorGreen) {
                        score_green++;
                        Serial.println("Cible Verte touché +1 point");
						tone(tonePin, 1000, 100);
						delay(5);
                    } else if ((results.value == 0x6D || results.value == 0x1006D) && isColorGreen) {
                        score_red = max(0, score_red - 1);
                        Serial.println("Cible Rouge touché -1 point");
						tone(tonePin, 200, 100);
						delay(5);
                    } else if ((results.value == 0x6E || results.value == 0x1006E) && !isColorGreen) {
                        score_green = max(0, score_green - 1);
                        Serial.println("Cible Verte touché -1 point");
						tone(tonePin, 200, 100);
						delay(5);
                    }

                    if ((results.value == 0x6D || results.value == 0x1006D) || (results.value == 0x6E || results.value == 0x1006E)) {
                        target_hit = true; // Marque qu'un tir valide a été effectué
                    }

                    Serial.print("Rouge : ");
                    Serial.println(score_red);
                    Serial.print("Vert : ");
                    Serial.println(score_green);

                    irrecv.resume(); // Prépare à recevoir le prochain signal
                    delay(5);
                }
            }

            if (target_hit) {
                // Faire disparaître la cible immédiatement après avoir été touchée
                fill_solid(color_leds, NUM_LEDS, CRGB::Black);
                FastLED.show();
                Serial.println("Cible touchée, extinction des LEDs.");
            }

            delay(MIN_OFF_TIME); // Pause avant de réafficher une nouvelle couleur
        }

        Serial.println("Fin du jeu. Affichage des scores finaux :");
        Serial.print("Score Rouge : ");
        Serial.println(score_red);
        Serial.print("Score Vert : ");
        Serial.println(score_green);

        End_Game_Effect();

        reflex_time_running = false;
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

/**
********************************
* --- Commentaires
*******************************
*/
// Fonction pour changer de couleur en fonction de la télécommande IR
void Switch_Color()
{
	//const unsigned long PROGMEM expectedHex_switch_color_rouge = 0x10001;
	//const unsigned long PROGMEM expectedHex_switch_color_vert = 0x10002;
	//const unsigned long PROGMEM expectedHex_switch_color_bleu = 0x10003;
	//const unsigned long PROGMEM expectedHex_switch_color_blanc = 0x10004;

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
