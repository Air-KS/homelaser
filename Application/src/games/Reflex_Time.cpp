// src/games/Reflex_Time.cpp
#include "games.h"

/*
*************************************************
----- Réflex Times -----
*************************************************
*/

// Constantes - millisecondes
const int GAME_DURATION = 180000; // Durée du jeu (180000 = 3 minutes)
const int MIN_OFF_TIME = 500; // Temps minimum d'extinction des LED
const int MAX_OFF_TIME = 3000; // Temps maximum d'extinction des LED

// Définitions des variables globales
int score_red = 0;
int score_green = 0;
bool target_touched[NUM_LEDS] = {false};

// Fonction principale du jeu Reflex Time
void Reflex_Time() {
	if (!reflex_time_running) {
		reflex_time_running = true; // Le jeu en cours

		// comment
		//Start_Effect();
		delay(1000);
		Led_Intensity(20);

		// Temps de démarrage du jeu
		unsigned long start_time = millis();

		while (millis() - start_time < GAME_DURATION) {
			// Génération aléatoire de la couleur de la cible Green ? Red
			bool isColorGreen = random(2) % 2 == 0;
			fill_solid(color_leds, NUM_LEDS, isColorGreen ? CRGB::Green : CRGB::Red);
			FastLED.show();
			Serial.println(isColorGreen ? "Couleur Verte" : "Couleur Rouge");

			// Durée d'affichage de la cible
			unsigned long display_time = random(MIN_OFF_TIME, MAX_OFF_TIME) + millis();

			// Réinitialisation de la détection de cible touchée
			bool target_hit = false;

			// Boucle pour détecter si une cible est touchée pendant la durée d'affichage
			while (millis() < display_time && !target_hit) {
				if (irrecv.decode(&results)) {
					// Vérification du code IR reçu
					if ((results.value == 0x6D || results.value == 0x1006D ||
						 results.value == 0x6E || results.value == 0x1006E)) {
						// Traitement du signal IR s'il correspond à un code autorisé
						if (!target_touched[0]) { // Vérification si la cible n'a pas déjà été touchée
							if (((results.value == 0x6D || results.value == 0x1006D) && !isColorGreen) ||
								((results.value == 0x6E || results.value == 0x1006E) && isColorGreen)) {
								// Tir valide
								//playPositiveSound();

								// Mettre à jour les scores en respectant les règles
								if (isColorGreen) {
									if (score_green < 10) {
										score_green++;
										if (score_red + score_green > 10) {
											score_red = 10 - score_green;
										}
									}
								} else {
									if (score_red < 10) {
										score_red++;
										if (score_red + score_green > 10) {
											score_green = 10 - score_red;
										}
									}
								}

								// Si l'un des joueurs atteint 10 points, terminer le jeu
								if (score_red == 10 || score_green == 10) {
									Serial.print("score final Rouge: ");
									Serial.println(score_red);
									Serial.print("score final Vert: ");
									Serial.println(score_green);
									End_Game_Effect();
									reflex_time_running = false; // Le jeu est terminé
									irrecv.resume(); // Prêt pour le prochain signal
									return;
								}

								// Cible touchée
								target_touched[0] = true;

								// Faire clignoter uniquement la cible touchée
								for (int i = 0; i < 5; i++) {
									fill_solid(color_leds, NUM_LEDS, CRGB::Black);
									FastLED.show();
									delay(100);
									fill_solid(color_leds, NUM_LEDS, isColorGreen ? CRGB::Green : CRGB::Red);
									FastLED.show();
									delay(100);
								}

								// Attendre un court moment avant de passer à la prochaine cible
								delay(500);
							} else if ((results.value == 0x6D || results.value == 0x1006D) && isColorGreen) {
								// Tir rouge sur cible verte
								//playNegativeSound();
								Serial.println("Tir incorrect : -1 point");
								if (score_red > 0)
									score_red--;
							} else if ((results.value == 0x6E || results.value == 0x1006E) && !isColorGreen) {
								// Tir vert sur cible rouge
								//playNegativeSound();
								Serial.println("Tir incorrect : -1 point");
								if (score_green > 0)
									score_green--;
							}

							// Affichage des scores mis à jour
							Serial.print("Score Rouge: ");
							Serial.println(score_red);
							Serial.print("Score Vert: ");
							Serial.println(score_green);

							// Marquer qu'une cible a été touchée
							target_hit = true;
						}
					}
					irrecv.resume(); // Prêt pour le prochain signal
				}
			}

			// S'assurer que les LEDs sont éteintes avant d'afficher la prochaine cible
			fill_solid(color_leds, NUM_LEDS, CRGB::Black);
			FastLED.show();
			delay(MIN_OFF_TIME); // Temporisation avant l'affichage de la prochaine cible

			// Réinitialiser la cible touchée pour la prochaine itération
			target_touched[0] = false;
		}

		// Effet de fin de jeu
		End_Game_Effect();
		reflex_time_running = false; // Le jeu est terminé
	}
}

// Fonction de sons positif en cas de cible touché
void playPositiveSound() {
	tone(tonePin, 1000, 100);
	delay(105);
}

// Fonction de sons negatif en cas de cible manqué
void playNegativeSound() {
	tone(tonePin, 200, 100);
	delay(105);
}
