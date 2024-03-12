#include "main.h"
#include "pitches.h"
#include "prototypes.h"
#include "broches.h"
#include "music/music.h"


/*
*************************************************
----- Variable pour les modes de jeux -----
*************************************************
*/
// Réflex Times
bool reflex_time_active = false;
bool reflex_time_running = false;
CRGB color_leds[NUM_LEDS];

// Définir la broche de réception IR
const int RECV_PIN = 2;

// Créer une instance de récepteur IR
IRrecv irrecv(RECV_PIN);

decode_results results;

// Définir les codes IR pour chaque couleur
const unsigned long IR_CODE_RED = 0xFFA25D; // Code IR pour la couleur rouge
const unsigned long IR_CODE_GREEN = 0xFF629D; // Code IR pour la couleur verte

// Définir les variables pour le score et le code IR actuel
int score = 0;
unsigned long current_code = 0;

void Reflex_Time()
{
    // Constantes
    const int GAME_DURATION = 5000; // Durée du jeu en millisecondes
    const int MIN_OFF_TIME = 500; // Temps minimum d'extinction des LED en millisecondes
    const int MAX_OFF_TIME = 3000; // Temps maximum d'extinction des LED en millisecondes

    // Vérifie si le jeu n'est pas déjà en cours
    if (!reflex_time_running)
    {
        reflex_time_running = true;

        // Appel les fonctions
        Start_Effect();
        delay(1000);
        Led_Intensity(20);

        // Temps de départ du jeu
        unsigned long start_time = millis();

        // Initialiser le récepteur IR
        irrecv.enableIRIn();

        // Jouer le jeu pendant un certain temps
        while (millis() - start_time < GAME_DURATION)
        {
            // Vérifier si un signal IR a été reçu
            if (irrecv.decode(&results))
            {
                // Vérifier si le code IR correspond à la couleur actuelle
                if (results.value == current_code)
                {
                    // Le joueur a gagné un point
                    score++;
                }
                else
                {
                    // Le joueur a perdu un point
                    score--;
                }

                // Réinitialiser le récepteur IR
                irrecv.resume();
            }

            // Sélectionner aléatoirement la couleur à afficher (vert ou rouge)
            CRGB color = random(2) ? CRGB::Green : CRGB::Red;

            // Mettre à jour le code IR actuel en fonction de la couleur sélectionnée
            current_code = (color == CRGB::Red) ? IR_CODE_RED : IR_CODE_GREEN;

            // Afficher la couleur
            fill_solid(color_leds, NUM_LEDS, color);
            FastLED.show();

            delay(1500);

            // Éteindre les LED's pendant une durée aléatoire
            unsigned long off_time = random(MIN_OFF_TIME, MAX_OFF_TIME);
            fill_solid(color_leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            delay(off_time);
        }

        // Afficher les scores finaux
        Serial.print("Score final : ");
        Serial.println(score);

        // Effet de fin de jeu
        End_Game_Effect();

        // Mettre à jour l'état du jeu
        reflex_time_running = false;
    }
}
