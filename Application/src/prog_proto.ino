#include "main.h"

#define DATA_PIN 33 // Broche de données à laquelle la guirlande LED est connectée
#define NUM_LEDS 10 // Nombre total de LEDs dans votre guirlande

CRGB leds[NUM_LEDS];

#define LED_TYPE WS2812B // Type de LEDs WS2812B
#define COLOR_ORDER GRB // L'ordre des couleurs dans votre guirlande LED (GRB est courant)

#define FASTLED_ALLOW_INTERRUPTS 0 // Désactiver les interruptions pendant l'envoi de données

CRGB couleur_leds_actuelle = CRGB(60, 60, 60);

CRGB couleur_leds_vies_10 = CRGB(0, 255, 0);
CRGB couleur_leds_vies_9 = CRGB(28, 227, 0);
CRGB couleur_leds_vies_8 = CRGB(57, 198, 0);
CRGB couleur_leds_vies_7 = CRGB(85, 170, 0);
CRGB couleur_leds_vies_6 = CRGB(113, 142, 0);
CRGB couleur_leds_vies_5 = CRGB(142, 113, 0);
CRGB couleur_leds_vies_4 = CRGB(170, 85, 0);
CRGB couleur_leds_vies_3 = CRGB(198, 57, 0);
CRGB couleur_leds_vies_2 = CRGB(227, 28, 0);
CRGB couleur_leds_vies_1 = CRGB(255, 0, 0);


CRGB couleur_leds_vies_0 = CRGB(0, 0, 0);

CRGB orange_homelaser = CRGB(255, 77, 0);

const int LedsDefaultBrightness = 200;

bool animation_leds_policier = false;

const uint16_t kRecvPin = 36;  // Pin connected to the IR receiver.

IRrecv irrecv(kRecvPin);
decode_results results;

//NEC IR code for TEAMS
const unsigned long PROGMEM expectedHex_TirEquipe_Rouge = 0xFF9867;
const unsigned long PROGMEM expectedHex_TirEquipe_Verte = 0xFF629D;
const unsigned long PROGMEM expectedHex_TirEquipe_Bleue = 0xFF30CF;
const unsigned long PROGMEM expectedHex_TirEquipe_Seul = 0xFF5AA5;

//NEC IR code for MODIFS
const unsigned long PROGMEM expectedHex_plus_une_vie = 0xFFA25D;
const unsigned long PROGMEM expectedHex_changement_apparence_rouge = 0xFF6897;
const unsigned long PROGMEM expectedHex_changement_apparence_vert = 0xFF7A85;
const unsigned long PROGMEM expectedHex_changement_apparence_bleu = 0xFF52AD;
const unsigned long PROGMEM expectedHex_changement_apparence_blanc = 0xFF42BD;
const unsigned long PROGMEM expectedHex_changement_apparence_invisible = 0xFF4AB5;
//const unsigned long PROGMEM expectedHex_prout_laser = 0xFF38C7;
//const unsigned long PROGMEM expectedHex_munition_max_1 = 0xFF10EF;
//const unsigned long PROGMEM expectedHex_munition_max_5 = 0xfd906f;
//const unsigned long PROGMEM expectedHex_munition_max_10 = 0xFF18E7;
//const unsigned long PROGMEM expectedHex_munition_max_20 = 0xFF906F;
//const unsigned long PROGMEM expectedHex_munition_max_30 = 0xFFA857;
//const unsigned long PROGMEM expectedHex_munition_max_40 = 0xFFE01F;
//const unsigned long PROGMEM expectedHex_munition_max_100 = 0xfd8877;
//const unsigned long PROGMEM expectedHex_munition_max_200 = 0xfc66F79;
//const unsigned long PROGMEM expectedHex_interdire_recharge = 0xfd50af;
//const unsigned long PROGMEM expectedHex_autoriser_recharge = 0xFF22DD;
const unsigned long PROGMEM expectedHex_bouclier = 0xFFC23D;
const unsigned long PROGMEM expectedHex_invincible = 0xFFE21D;

//const unsigned long PROGMEM expectedHex_no_respawn = 0xfd30cf;
//const unsigned long PROGMEM expectedHex_respawn_now = 0xfd30cf;
//const unsigned long PROGMEM expectedHex_yes_respawn = 0xfd6897;
const unsigned long PROGMEM expectedHex_murder = 0xfdb04f;
const unsigned long PROGMEM expectedHex_innocent = 0xfd48b7;
const unsigned long PROGMEM expectedHex_policier = 0xfd08f9;
//const unsigned long PROGMEM expectedHex_frienly_fire_ON = 0xFFA36cb;
//const unsigned long PROGMEM expectedHex_frienly_fire_OFF = 0xFFA79fd;
//const unsigned long PROGMEM expectedHex_vies_illimites_ON = 0xfde9bd;
//const unsigned long PROGMEM expectedHex_vies_illimites_OFF = 0xfd701fc;

//const unsigned long PROGMEM expectedHex_contagion_ON = 0xBAD9A92;
//const unsigned long PROGMEM expectedHex_contagion_OFF = 0xBAE2B10;
//const unsigned long PROGMEM expectedHex_mode_fantome = 0xBAF2C31;
//const unsigned long PROGMEM expectedHex_mode_loup_garou = 0xBAA4D60;
//const unsigned long PROGMEM expectedHex_menu_selection_rouge = 0xBA00EB8;
//const unsigned long PROGMEM expectedHex_menu_selection_vert = 0xBA27FA7;
//const unsigned long PROGMEM expectedHex_menu_selection_bleu = 0xBA18AB2;
//const unsigned long PROGMEM expectedHex_menu_selection_seul = 0xBA89B1C;
//const unsigned long PROGMEM expectedHex_menu_selection_aleatoire = 0xBA25C2D;
//const unsigned long PROGMEM expectedHex_ingame_selection_rouge = 0xBA95D0E;
//const unsigned long PROGMEM expectedHex_ingame_selection_vert = 0xBA8E76F;
//const unsigned long PROGMEM expectedHex_ingame_selection_bleu = 0xBA0F95A;
//const unsigned long PROGMEM expectedHex_ingame_selection_seul = 0xBA1A00B;
//const unsigned long PROGMEM expectedHex_ingame_selection_aleatoire = 0xBA1B29C;

//--------------------------------------------
//DIP SWITCHES

//SI aucune des vies n'est cochée, alors vies illimitées
#define vies_1 13
#define vies_2 14
#define vies_3 27
#define vies_4 26
#define vies_5 25
#define vies_6 32
#define vies_7 35
#define vies_8 34
#define vies_9 39
#define vies_10 23


#define mode_cible_ou_points_de_vie 22
#define mode_contagion 21

#define delai_reapparition_0 19
#define delai_reapparition_5 18
#define delai_reapparition_10 5
#define delai_reapparition_20 17

#define vibreur_on 16
#define son_on 4



//
int vies_initiales = 0;
int vies = 5; //nombre de vies par défaut
bool vies_changees = 0;

bool mort = false;
int delai_de_reapparition = 3000; //en ms
bool bouclier = false;
bool invincible = false;
bool mort_def = false;
bool apparence_changee = false;

bool contagion = false;
bool couleur_changee_manuellement = false;
bool apparence_rouge = false;
bool apparence_verte = false;
bool apparence_bleue = false;
bool apparence_blanche = false;
bool apparence_invisible = false;

bool buzzer_ON = true;
bool haptic_feedback_ON = true;

bool etat_pds_initial = false;
bool changement_d_etat_pdvs = false;
bool bouclier_casse = false;



#define tonePin 12
#define moteur_vibrant 15
unsigned long debutActivation; // Moment de l'activation du moteur
unsigned long dureeActivation;

unsigned long debutTempsRespawn; // Moment de l'activation du moteur
unsigned long dureeTempsRespawn;

unsigned long debutTempsMortDef; // Moment de l'activation du moteur
unsigned long dureeTempsMortDef;

const uint32_t kBaudRate = 115200;  // Baud rate for serial communications.

bool ETAT_precedent;
bool vient_d_etre_touche = false;
bool actualisation_initiale = false;
bool ETAT_precedent_contagion;

//------------------------------------------------------
//-----------------------MULTICOEUR---------------------

TaskHandle_t task1;
int LEDmode = 0;
int ancienLEDmode;
int stateDuration;
int fadeDuration;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(kBaudRate);
  while (!Serial) { // Wait for the serial connection to be established.
    delay(50);
  }


  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(200); // Réglez la luminosité si nécessaire



  irrecv.enableIRIn();  // Start the IR receiver.
  Serial.println("Ready to receive IR signals");


  pinMode(vies_1, INPUT_PULLUP);
  pinMode(vies_2, INPUT_PULLUP);
  pinMode(vies_3, INPUT_PULLUP);
  pinMode(vies_4, INPUT_PULLUP);
  pinMode(vies_5, INPUT_PULLUP);
  pinMode(vies_6, INPUT_PULLUP);
  pinMode(vies_7, INPUT_PULLUP);
  pinMode(vies_8, INPUT_PULLUP);
  pinMode(vies_9, INPUT_PULLUP);
  pinMode(vies_10, INPUT_PULLUP);
  pinMode(mode_cible_ou_points_de_vie, INPUT_PULLUP);
  pinMode(mode_contagion, INPUT_PULLUP);
  pinMode(delai_reapparition_0, INPUT_PULLUP); //si aucun delais de reapparition, alors 3 sec par défaut
  pinMode(delai_reapparition_5, INPUT_PULLUP); //les delais de reapparition se cumulent
  pinMode(delai_reapparition_10, INPUT_PULLUP);
  pinMode(delai_reapparition_20, INPUT_PULLUP);
  pinMode(vibreur_on, INPUT_PULLUP);
  pinMode(son_on, INPUT_PULLUP);


  pinMode(tonePin, OUTPUT);
  pinMode(moteur_vibrant, OUTPUT);

  determiner_delai_de_reapparition();

  determiner_etat_son_et_vibration();

  vibration_2_petites_vibrations();

  ETAT_precedent = digitalRead(mode_cible_ou_points_de_vie);

  //-----------------------------------------
  //------------------MULTICOEUR-------------

  Serial.println(F("Activation du Coeur Secondaire..."));

  // Créer la première tâche sur le cœur 0
  xTaskCreatePinnedToCore(
    LEDsManagement,   // Fonction de la tâche
    "Task1",         // Nom de la tâche
    10000,           // Taille de la pile
    NULL,            // Paramètres de la tâche (nous n'en avons pas besoin ici)
    1,               // Priorité (plus élevée signifie plus prioritaire)
    &task1,          // Gestionnaire de tâche
    0                // Cœur 0
  );

  Serial.println(F("Coeur Secondaire activé"));


} //fin setup


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void loop() {


  //QUEL MODE ?
  bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);
  determiner_delai_de_reapparition();
  determiner_etat_son_et_vibration();

  if (ETAT_precedent != ETAT_mode_cible_ou_points_de_vie) {
    //mettre ici toutes les variables à changer entre les deux mode de jeux

    couleur_changee_manuellement = false; //important pour l'autre mode si on change en cours de route
    LEDmode = 0; //idem
    actualisation_initiale = false;



    etat_pds_initial = false;

  }


  if (ETAT_mode_cible_ou_points_de_vie == 0) { //mode points de vie *********************
  ETAT_precedent = ETAT_mode_cible_ou_points_de_vie;
  determiner_points_de_vie(); //pour déterminer les points de vies initialement définis, ou détecter un changement de parametres de vie

  if (etat_pds_initial == false) {
    changement_couleur_leds_vies();
    actualiser_couleur_leds();
    etat_pds_initial = true;
  }



  if (irrecv.decode(&results)) {

      Serial.print("Code IR reçu: 0x");
      Serial.println(uint64ToString(results.value, HEX)); // Display the received code in HEX.

    if (results.value == expectedHex_TirEquipe_Rouge || results.value == expectedHex_TirEquipe_Verte || results.value == expectedHex_TirEquipe_Bleue || results.value == expectedHex_TirEquipe_Seul) { // Vérifier si le code reçu est de 32 bits.


      if (invincible == true) {
        //ne rien faire
        Serial.println("touché ! mais je suis invincible");
      }
      else {
        if (bouclier == true) {
        bouclier_casse = true;
        }
        couleur_leds_actuelle = CRGB::White;
        lumieres_touches();
      }


      if (bouclier == true) {
        //retirer le bouclier sans perdre de vie
        bouclier = false;
        Serial.println("touché ! --> perte du bouclier");
        Serial.print("Rappel : nombre de vies restantes : ");
        Serial.println(vies);

        son_bouclier_DOWN();
        vibration_2_petites_vibrations();

        changement_couleur_leds_vies();
        actualiser_couleur_leds();
      }

      else if (bouclier == false && invincible == false) {


        vies -= 1;
        mort = true;
        Serial.print("touché ! - 1 vie    |||||    ");
        Serial.print("Nombre de vies restantes : ");
        Serial.println(vies);

        vibration_touche();
        son_touche();


        delais_avant_respawn();

        check_if_mort_def();
      }
    }

    if (results.value == expectedHex_plus_une_vie) {
      if (vies == vies_initiales) {
        //ne rien faire car les vies ne peuvent excéder le nombre de vies initialement set
      }
      else {
      vies += 1;
      Serial.print("Plus une vie !   |||||    vies restantes : ");
      Serial.println(vies);

      son_plus_une_vie();
      vibration_2_petites_vibrations();

      changement_couleur_leds_vies();
      actualiser_couleur_leds();

    }
    }


    if (results.value == expectedHex_changement_apparence_rouge) {
      couleur_leds_actuelle = CRGB(255, 0, 0);
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
      Serial.println("changement apparence rouge");
    }

    if (results.value == expectedHex_changement_apparence_vert) {
      couleur_leds_actuelle = CRGB(0, 255, 0);
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
      Serial.println("changement apparence verte");
    }

    if (results.value == expectedHex_changement_apparence_bleu) {
      couleur_leds_actuelle = CRGB(0, 0, 255);
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
      Serial.println("changement apparence bleue");
    }

    if (results.value == expectedHex_changement_apparence_blanc) {
      couleur_leds_actuelle = CRGB(255, 255, 255);
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
      Serial.println("changement apparence blanc");
    }

    if (results.value == expectedHex_changement_apparence_invisible) {
      couleur_leds_actuelle = CRGB(0, 0, 0);
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
      Serial.println("changement apparence invisible");
    }

    if (results.value == expectedHex_bouclier) {
      if (bouclier == true) {

      }
      else {
      bouclier = true;

      son_bouclier_UP();
      Serial.println("bouclier reçu !");
      vibration_2_petites_vibrations();

      couleur_leds_actuelle = CRGB(0, 255, 255);
      actualiser_couleur_leds();
      }
    }

    if (results.value == expectedHex_invincible) { //ne peut pas être ciblé
      if (invincible == true) {
        invincible = false;
        changement_couleur_leds_vies();
        actualiser_couleur_leds();
        LEDmode = 0;
        son_bouclier_DOWN();
        Serial.println("je ne suis plus invincible");
        vibration_2_petites_vibrations();
        delay(2000);
        changement_couleur_leds_vies();
        actualiser_couleur_leds();
      }
      else {
        invincible = true;
        Serial.println("Je suis invincible");

        son_bouclier_UP();
        vibration_2_petites_vibrations();

        couleur_leds_actuelle = orange_homelaser;
        LEDmode = 6;
        actualiser_couleur_leds();
      }
    }


    irrecv.resume(); // Prepare for the next value.
  }

  } // fin if (ETAT_mode_cible_ou_points_de_vie == 0) // mode PDVS


  if (ETAT_mode_cible_ou_points_de_vie == 1) { //mode CIBLE *********//************
    ETAT_precedent = ETAT_mode_cible_ou_points_de_vie;

    bool ETAT_mode_contagion = digitalRead(mode_contagion);
    if (ETAT_mode_contagion == HIGH) {
      contagion = true;
      ETAT_precedent_contagion = contagion;
      //Serial.println("contagion TRUE : ");
      //Serial.println(ETAT_mode_contagion);
      //couleur_changee_manuellement = false;
    }
    else {

      contagion = false;
      mettre_les_apparences_a_false();
      if (ETAT_precedent_contagion != contagion) {
        actualisation_initiale = false;
      }

    }

    //actualisation initiale
    if (actualisation_initiale == false) {
    actualisation_couleur_cible();
    actualisation_initiale = true;
    }



    //système de touche
  if (irrecv.decode(&results)) {

      Serial.print("Code IR reçu: 0x");
      Serial.println(uint64ToString(results.value, HEX)); // Display the received code in HEX.


    if (results.value == expectedHex_TirEquipe_Rouge) {
      couleur_leds_actuelle = CRGB::Red;
      traitement_reception_tir();

      mettre_les_apparences_a_false();
      apparence_rouge = true;

    }

    if (results.value == expectedHex_TirEquipe_Verte) {
      couleur_leds_actuelle = CRGB::Green;
      traitement_reception_tir();

      mettre_les_apparences_a_false();
      apparence_verte = true;
    }

    if (results.value == expectedHex_TirEquipe_Bleue) {
      couleur_leds_actuelle = CRGB::Blue;
      traitement_reception_tir();

      mettre_les_apparences_a_false();
      apparence_bleue = true;
    }

    if (results.value == expectedHex_TirEquipe_Seul) {
      couleur_leds_actuelle = CRGB::White;
      traitement_reception_tir();

      mettre_les_apparences_a_false();
      apparence_blanche = true;
    }



    if (results.value == expectedHex_changement_apparence_rouge) {
      couleur_leds_actuelle = CRGB::Red;
      couleur_changee_manuellement = true;
      mettre_les_apparences_a_false();
      apparence_rouge = true;
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
    }

    if (results.value == expectedHex_changement_apparence_vert) {
      couleur_leds_actuelle = CRGB::Green;
      couleur_changee_manuellement = true;
      mettre_les_apparences_a_false();
      apparence_verte = true;
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
    }

    if (results.value == expectedHex_changement_apparence_bleu) {
      couleur_leds_actuelle = CRGB::Blue;
      couleur_changee_manuellement = true;
      mettre_les_apparences_a_false();
      apparence_bleue = true;
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
    }

    if (results.value == expectedHex_changement_apparence_blanc) {
      couleur_leds_actuelle = CRGB::White;
      couleur_changee_manuellement = true;
      mettre_les_apparences_a_false();
      apparence_blanche = true;
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
    }

    if (results.value == expectedHex_changement_apparence_invisible) {
      couleur_leds_actuelle = CRGB::Black;
      couleur_changee_manuellement = true;
      mettre_les_apparences_a_false();
      apparence_invisible = true;
      actualiser_couleur_leds();
      vibration_2_petites_vibrations();
    }


    if (results.value == expectedHex_policier) { //leds policier (atout chasseur mode loup garou)
      if (animation_leds_policier == true) { //si déjà policier
        mettre_les_apparences_a_false();
        actualiser_couleur_leds();
        animation_leds_policier = false;
        LEDmode = 0;
        actualisation_couleur_cible();
      }
      else {
        mettre_les_apparences_a_false();
        actualiser_couleur_leds();
        animation_leds_policier = true;
        actualisation_couleur_cible();

      }
      vibration_2_petites_vibrations();
    }







    irrecv.resume(); // Prepare for the next value.


  }





  } // fin if (ETAT_mode_cible_ou_points_de_vie == 1) // mode CIBLE






// Vérifier si la durée d'activation est dépassée pour éteindre le moteur vibrant
check_si_on_doit_eteindre_moteur_vibrant();




} //fin loop



///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//                                    FONCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////



void lumieres_touches() {
  Serial.println("fonction activée : lumieres_touches()");
  ancienLEDmode = LEDmode;
  Serial.print("ancienLEDmode (en mémoire) = ");
  Serial.print(ancienLEDmode);
  LEDmode = 5;
  Serial.print(" ET nouveau LEDmode temporaire = ");
  Serial.println(LEDmode);
  FastLED.clear();
  Serial.println("FastLED.clear() OK dans la fonction lumieres_touches()");

}


void LEDsManagement(void* parameter) {
  while (1) {

    if (LEDmode == 0) {
      while (LEDmode == 0) {
        delay(10);
      }

    }

    else if (LEDmode == 1) { //policier
      Serial.println("ANIMATION LED POLICIER");
      FastLED.setBrightness(200); // Luminosité maximale
      stateDuration = 200;

      while (LEDmode == 1) {
        if (mort == true) {
          // Éteindre les 5 LEDs bleues
        for (int i = 0; i < 5; i++) {
          leds[i] = CRGB::Black; // Éteindre la LED
        }
        Serial.println("while (LEDmode == 1) et if (mort == true) donc on eteint les leds");

        // Mettre à jour la guirlande LED
        FastLED.show();
        delay(15);

        while (mort == true) {
          //ne rien faire
          delay(15);
          if (LEDmode == 1) {
            break;
            Serial.println("LEDmode == 1 detecté dans la boucle while (mort == true) donc break;");

          }
        }

        }

        else {
          // Allumer les 5 premières LEDs en bleu
      for (int i = 0; i < 5; i++) {
        leds[i] = CRGB(0, 0, 255); // Couleur bleue
      }

      // Mettre à jour la guirlande LED
      FastLED.show();

      // Attendre la durée de l'état bleu
      delay(stateDuration);

      // Éteindre les 5 LEDs bleues
      for (int i = 0; i < 5; i++) {
        leds[i] = CRGB::Black; // Éteindre la LED
      }

      // Allumer les 5 LEDs suivantes en rouge
      for (int i = 5; i < 10; i++) {
        leds[i] = CRGB(255, 0, 0); // Couleur rouge
      }

      // Mettre à jour la guirlande LED
      FastLED.show();

      // Attendre la durée de l'état rouge
      delay(stateDuration);

      // Allumer les 5 LEDs suivantes en rouge
      for (int i = 5; i < 10; i++) {
        leds[i] = CRGB::Black; // Éteindre la LED
      }

      }
        }


      }

    else if (LEDmode == 2) { //capture de zone
      //Serial.println("ANIMATION LED CAPTURE DE ZONE");
      FastLED.setBrightness(200); // Luminosité maximale
        fadeDuration = 70;

        for (int i = 0; i < NUM_LEDS; i++) {
        // Calculer le nombre d'étapes de fondu
        int steps = fadeDuration / 2;

        for (int step = 0; step <= steps; step++) {
          int brightness = map(step, 0, steps, 0, 255);
          int prevBrightness = map(step, 0, steps, 255, 0);

          int currentIndex = i;
          int prevIndex = (i - 8 + NUM_LEDS) % NUM_LEDS; //i - 1 pour seulement deux leds qui tournent

          CRGB currentColor = couleur_leds_actuelle;
          CRGB prevColor = couleur_leds_actuelle;

          currentColor.nscale8(brightness); // Ajuster la luminosité sans changer la couleur
          prevColor.nscale8(prevBrightness); // Ajuster la luminosité sans changer la couleur

          leds[prevIndex] = prevColor; // fade-in
          leds[currentIndex] = currentColor; // fade-out

          FastLED.show();
        }
      }
      }

    else if (LEDmode == 3) { //la partie va bientôt démarrer (fade-in/fade-out)
        fadeDuration = 1500;
        Serial.println("ANIMATION LED PARTIE EN ATTENTE");
        FastLED.setBrightness(200); // Luminosité maximale

      while (LEDmode == 3) {

      // Fade-in
        for (int i = 0; i <= 255; i++) {
        FastLED.setBrightness(i); // Ajustez la luminosité
        fill_solid(leds, NUM_LEDS, couleur_leds_actuelle);
        FastLED.show();
        delay(fadeDuration / 255);
      }

      delay(750); // Pause

      // Fade-out
      for (int i = 255; i >= 0; i--) {
        FastLED.setBrightness(i); // Ajustez la luminosité
        fill_solid(leds, NUM_LEDS, couleur_leds_actuelle);
        FastLED.show();
        delay(fadeDuration / 255);
      }

      delay(750); // Pause

      }

      }


    else if (LEDmode == 4) { //clignoter 1 fois (reminder d'éteindre l'appareil)

      FastLED.clear();

      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White; // Éteindre la LED
      }
      FastLED.show();
      delay(300);
      FastLED.clear();

      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black; // Éteindre la LED
      }
      FastLED.show();


      LEDmode = 0;
    }

  else if (LEDmode == 5) { //lumières touchés
    Serial.println("lumières touché (LEDmode == 5)");
    int iterations_flash = 8;
    FastLED.setBrightness(255);


    if (delai_de_reapparition == 0) {
      iterations_flash = 3;
      Serial.println("iterations_flash = 3 CAR delai_de_reapparition == 0");

    }

  // Clignoter les LEDs rapidement en blanc plusieurs fois
  for (int i = 0; i < iterations_flash; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = couleur_leds_actuelle;
    }
    FastLED.show();
    delay(45); // Temps de clignotement rapide
    FastLED.clear();
    FastLED.show();
    delay(45); // Temps d'extinction
  }

  // Mettre toutes les LEDs en blanc à pleine luminosité pendant 1 seconde
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = couleur_leds_actuelle;
  }
  FastLED.show();
  delay(350);

  // Éteindre toutes les LEDs
  FastLED.clear();
  FastLED.show();

  Serial.print("Fin des leds touchés, redirection vers le LEDmode ");
  Serial.println(ancienLEDmode);

  LEDmode = ancienLEDmode;
  FastLED.setBrightness(LedsDefaultBrightness);

  if (bouclier_casse == true) {
    bouclier_casse = false;
    bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);
  if (ETAT_mode_cible_ou_points_de_vie == 0) {
    changement_couleur_leds_vies();
    actualiser_couleur_leds();
  }
  }


  }

  else if (LEDmode == 6) {
    // Durée du fondu (en millisecondes)
  int fadeDuration = 50;

  for (int i = 0; i < NUM_LEDS; i++) {
    // Couleur couleur_equipe (R=255, G=165, B=0)
    //CRGB couleur_equipe = CRGB(255, 165, 0);

    // Éteindre toutes les LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Calculer le nombre d'étapes de fondu
    int steps = fadeDuration / 20; // 20 ms par étape

    for (int step = 0; step <= steps; step++) {
      int brightness = map(step, 0, steps, 0, 255);
      int prevBrightness = map(step, 0, steps, 255, 0);

      for (int j = 0; j < NUM_LEDS; j++) {
        int currentIndex = (i + j) % NUM_LEDS;
        int prevIndex = (i + j - 1 + NUM_LEDS) % NUM_LEDS;

        leds[currentIndex] = CRGB(brightness, brightness * 165 / 255, 0);
        leds[prevIndex] = CRGB(prevBrightness, prevBrightness * 165 / 255, 0);

        FastLED.show();
        delay(20);
      }
    }
  }
  }


  } //fin boucle coeur secondaire
} //fin fonction coeur secondaire



void determiner_points_de_vie() {


  int nombreDIPSwitches = 10;
  bool ETAT_vies[nombreDIPSwitches];

  // Remplacez les indices 0 à 9 par vos variables ETAT_vies_1 à ETAT_vies_10
  ETAT_vies[0] = digitalRead(vies_1);
  ETAT_vies[1] = digitalRead(vies_2);
  ETAT_vies[2] = digitalRead(vies_3);
  ETAT_vies[3] = digitalRead(vies_4);
  ETAT_vies[4] = digitalRead(vies_5);
  ETAT_vies[5] = digitalRead(vies_6);
  ETAT_vies[6] = digitalRead(vies_7);
  ETAT_vies[7] = digitalRead(vies_8);
  ETAT_vies[8] = digitalRead(vies_9);
  ETAT_vies[9] = digitalRead(vies_10);

  int nombreDIPSwitchActifs = 0;

  // Utiliser une boucle for pour parcourir la liste des DIP switches
  for (int i = 0; i < nombreDIPSwitches; i++) {
    if (ETAT_vies[i]) {
      nombreDIPSwitchActifs++;
    }
  }

  // Vérifier le nombre de DIP switches activés simultanément
  if (nombreDIPSwitchActifs != 1) {
    Serial.print(nombreDIPSwitchActifs);
    Serial.println(" DIP switches sont activés simultanément OU aucun DIP switches n'est activé. (nombre de vies)");
    vies_initiales = 5;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[9] == HIGH && vies_initiales != 10) {
    vies_initiales = 10;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[8] == HIGH && vies_initiales != 9) {
    vies_initiales = 9;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[7] == HIGH && vies_initiales != 8) {
    vies_initiales = 8;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[6] == HIGH && vies_initiales != 7) {
    vies_initiales = 7;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[5] == HIGH && vies_initiales != 6) {
    vies_initiales = 6;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[4] == HIGH && vies_initiales != 5) {
    vies_initiales = 5;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[3] == HIGH && vies_initiales != 4) {
    vies_initiales = 4;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[2] == HIGH && vies_initiales != 3) {
    vies_initiales = 3;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[1] == HIGH && vies_initiales != 2) {
    vies_initiales = 2;
    changement_d_etat_pdvs = true;
  }

  else if (ETAT_vies[0] == HIGH && vies_initiales != 1) {
    vies_initiales = 1;
    changement_d_etat_pdvs = true;
  }

  if (changement_d_etat_pdvs == true) {
    vies = vies_initiales;
    mort_def = false;

    Serial.print(vies);
    Serial.println(" VIES mises");

    changement_couleur_leds_vies();
    actualiser_couleur_leds();

    changement_d_etat_pdvs = false;
  }


}


void changement_couleur_leds_vies() {

  if (vies == 10) {
couleur_leds_actuelle = couleur_leds_vies_10;
Serial.println("changement couleur vies = 10");
  }

  else if (vies == 9) {
couleur_leds_actuelle = couleur_leds_vies_9;
Serial.println("changement couleur vies = 9");
  }
  else if (vies == 8) {
couleur_leds_actuelle = couleur_leds_vies_8;
Serial.println("changement couleur vies = 8");
  }
  else if (vies == 7) {
couleur_leds_actuelle = couleur_leds_vies_7;
Serial.println("changement couleur vies = 7");
  }
  else if (vies == 6) {
couleur_leds_actuelle = couleur_leds_vies_6;
Serial.println("changement couleur vies = 6");
  }
  else if (vies == 5) {
couleur_leds_actuelle = couleur_leds_vies_5;
Serial.println("changement couleur vies = 5");
  }
  else if (vies == 4) {
couleur_leds_actuelle = couleur_leds_vies_4;
Serial.println("changement couleur vies = 4");
  }
  else if (vies == 3) {
couleur_leds_actuelle = couleur_leds_vies_3;
Serial.println("changement couleur vies = 3");
  }
  else if (vies == 2) {
couleur_leds_actuelle = couleur_leds_vies_2;
Serial.println("changement couleur vies = 2");
  }
  else if (vies == 1) {
couleur_leds_actuelle = couleur_leds_vies_1;
Serial.println("changement couleur vies = 1");
  }
  else if (vies == 0) {
couleur_leds_actuelle = couleur_leds_vies_0;
Serial.println("changement couleur vies = 0");
  }

}

void actualiser_couleur_leds() {
  if (LEDmode == 0) {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = couleur_leds_actuelle;
    }
    FastLED.show();
    bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);
    if (ETAT_mode_cible_ou_points_de_vie == 0) {
      Serial.println("leds actualisés");
    }
  }

}


void delais_avant_respawn() {
  if (mort == true) {
    debutTempsRespawn = millis(); // Enregistrer le moment de l'activation
    dureeTempsRespawn = delai_de_reapparition;
    while (mort == true) {
      delay(10);
      check_si_on_doit_eteindre_moteur_vibrant();
      if (millis() - debutTempsRespawn >= dureeTempsRespawn) {
        mort = false;
        bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);
        if (ETAT_mode_cible_ou_points_de_vie == 0) {
          vibration_2_petites_vibrations();
        }

      }
    }

  }

  if (animation_leds_policier == false) {
      while (LEDmode != 0) {
        delay(5);
      }
  }


  bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);
  if (ETAT_mode_cible_ou_points_de_vie == 0) {
    changement_couleur_leds_vies();
    actualiser_couleur_leds();
  }
  if (contagion == true) {
    actualiser_couleur_leds();
  }

}


void determiner_delai_de_reapparition() {

  int nombreDIPSwitches02 = 4;
  bool ETAT_delai_de_reapparition[nombreDIPSwitches02];

  // Remplacez les indices 0 à 9 par vos variables ETAT_vies_1 à ETAT_vies_10
  ETAT_delai_de_reapparition[0] = digitalRead(delai_reapparition_0);
  ETAT_delai_de_reapparition[1] = digitalRead(delai_reapparition_5);
  ETAT_delai_de_reapparition[2] = digitalRead(delai_reapparition_10);
  ETAT_delai_de_reapparition[3] = digitalRead(delai_reapparition_20);

  int nombreDIPSwitchActifs02 = 0;

  // Utiliser une boucle for pour parcourir la liste des DIP switches
  for (int i = 0; i < nombreDIPSwitches02; i++) {
    if (ETAT_delai_de_reapparition[i]) {
      nombreDIPSwitchActifs02++;
    }
  }

  // Vérifier le nombre de DIP switches activés simultanément
  if (nombreDIPSwitchActifs02 != 1) {
    Serial.print(nombreDIPSwitchActifs02);
    Serial.println(" DIP switches sont activés simultanément OU aucun DIP switches n'est activé (delai de reapparition).");
    delai_de_reapparition = 3000;
  }

  else if (ETAT_delai_de_reapparition[0] == HIGH) {
    delai_de_reapparition = 0;
  }

  else if (ETAT_delai_de_reapparition[1] == HIGH) {
    delai_de_reapparition = 5000;
  }

  else if (ETAT_delai_de_reapparition[2] == HIGH) {
    delai_de_reapparition = 10000;
  }

  else if (ETAT_delai_de_reapparition[3] == HIGH) {
    delai_de_reapparition = 20000;
  }

}


void check_if_mort_def() {
  if (vies == 0) {
    mort_def = true;
    Serial.println("Game OVER");

    son_game_over();
    vibration_game_over();

    //delay(10000);

    debutTempsMortDef = millis(); // Enregistrer le moment de l'activation
    dureeTempsMortDef = 30000;


    while (mort_def == true) {
      //boucler car mort définitivement et check si on change les parametres de vies ou changer de mode de jeu

      determiner_points_de_vie();
      if (vies > 0) {
        mort_def = false;
        break;
      }

      check_si_on_doit_eteindre_moteur_vibrant();

      bool ETAT_mode_cible_ou_points_de_vie = digitalRead(mode_cible_ou_points_de_vie);

      if (ETAT_mode_cible_ou_points_de_vie == 1) {
        mort_def = false;
        break;
      }

      determiner_etat_son_et_vibration();

      delay(15);

      if (millis() - debutTempsMortDef >= dureeTempsMortDef) {

        LEDmode = 4;
        if (buzzer_ON) {
          tone(tonePin, 1047, 150);  // Do5 (C5), durée de la note : 250 ms
          delay(300);
          tone(tonePin, 1047, 150);  // Do5 (C5), durée de la note : 250 ms
          delay(150);
          noTone(tonePin);  // Éteindre le buzzer
        }

        debutTempsMortDef = millis();

      }

    }
  }
}


void son_touche() {
  if (buzzer_ON) {
    //tone(tonePin, 1027.47, 800);  // Do5 (C5), durée de la note : 250 ms
    tone(tonePin, 1294.54, 800);  // Do5 (C5), durée de la note : 250 ms
        delay(300);  // Pause entre les notes
        //tone(tonePin, 784, 250);  // Sol5 (G5)
        //delay(300);
        //noTone(tonePin);  // Éteindre le buzzer
  }

}

void son_plus_une_vie() {
  if (buzzer_ON) {
  tone(tonePin, 256.87, 250);  // Do6 (C6), durée de la note : 250 ms
      delay(300);  // Pause entre les notes
      //tone(tonePin, 342.88, 250);  // Sol6 (G6)
      //delay(300);
      tone(tonePin, 513.74, 250);  // Sol6 (G6)
      delay(300);
      noTone(tonePin);  // Éteindre le buzzer
  }
}

void son_bouclier_UP() {
  if (buzzer_ON) {
      tone(tonePin, 523, 250);  // Do5 (C5), durée de la note : 250 ms
      delay(200);  // Pause entre les notes
      tone(tonePin, 659, 250);  // Mi5 (E5)
      delay(200);
      noTone(tonePin);  // Éteindre le buzzer
  }
}

void son_bouclier_DOWN() {
  if (buzzer_ON) {
  tone(tonePin, 659, 250);  // Mi5 (E5), durée de la note : 250 ms
        delay(300);  // Pause entre les notes
        tone(tonePin, 523, 250);  // Do5 (C5)
        delay(300);
        noTone(tonePin);  // Éteindre le buzzer
  }
}

void son_game_over() {
  if (buzzer_ON) {
    tone(tonePin, 392, 400);  // Sol4 (G4)
    delay(450);  // Pause entre les notes
    tone(tonePin, 329, 400);  // Mi4 (E4)
    delay(450);
    tone(tonePin, 261, 400);  // Do4 (C4), durée de la note : 400 ms
    delay(450);
    noTone(tonePin);  // Éteindre le buzzer
  }
}

void desactiverMoteur() {
  digitalWrite(moteur_vibrant, LOW); // Désactiver le moteur
}

void vibration_2_petites_vibrations() {
  if (haptic_feedback_ON) {
    digitalWrite(moteur_vibrant, HIGH);
    delay(75);
    digitalWrite(moteur_vibrant, LOW);
    delay(75);
    digitalWrite(moteur_vibrant, HIGH);
    debutActivation = millis(); // Enregistrer le moment de l'activation
    dureeActivation = 75; //pour gagner 75ms de code avant désactivation du moteur vibrant
  }
}

void vibration_touche() {
  if (haptic_feedback_ON) {
    digitalWrite(moteur_vibrant, HIGH);
    debutActivation = millis(); // Enregistrer le moment de l'activation

    if (delai_de_reapparition == 0) {
        dureeActivation = 1000;
    }
    else {
      dureeActivation = 1750;
    }
  }
}


void vibration_game_over() {
  if (haptic_feedback_ON) {
    digitalWrite(moteur_vibrant, HIGH);
    delay(750);
    digitalWrite(moteur_vibrant, LOW);
    delay(500);
    digitalWrite(moteur_vibrant, HIGH);
    delay(750);
    digitalWrite(moteur_vibrant, LOW);
    delay(500);
    digitalWrite(moteur_vibrant, HIGH);
    delay(1750);
    digitalWrite(moteur_vibrant, LOW);
  }
}

void check_si_on_doit_eteindre_moteur_vibrant() {
  // Vérifier si la durée d'activation est dépassée pour éteindre le moteur vibrant
  if (millis() - debutActivation >= dureeActivation) {
    desactiverMoteur();
  }
}


void determiner_etat_son_et_vibration() {
  bool ETAT_vibreur_on = digitalRead(vibreur_on);
  bool ETAT_son_on = digitalRead(son_on);

  if (ETAT_vibreur_on == true) {
    haptic_feedback_ON = true;
  }
  else {
    haptic_feedback_ON = false;
  }

  if (ETAT_son_on == true) {
    buzzer_ON = true;
  }
  else {
    buzzer_ON = false;
  }
}


void traitement_reception_tir() {

  Serial.println("Touché !");


  if (animation_leds_policier == true) {
    vient_d_etre_touche = true;
    Serial.println("vient_d_etre_touche = true car animation_leds_policier == true");
  }

  if (contagion == true) {
      Serial.println("traitement_reception_tir --> contagion == true");

        actualiser_couleur_leds();
        lumieres_touches();
  }

  else {
    Serial.println("traitement_reception_tir --> else");
    lumieres_touches();
    actualisation_initiale = false;
  }
  vibration_touche();
  son_touche();
  mort = true;
  delais_avant_respawn();
  }

void mettre_les_apparences_a_false() {
    apparence_rouge = false;
    apparence_verte = false;
    apparence_bleue = false;
    apparence_blanche = false;
    apparence_invisible = false;
}

void actualisation_couleur_cible() {

      if (animation_leds_policier == true) {
        if (vient_d_etre_touche == true) {
          vient_d_etre_touche = false;
          Serial.println("vient_d_etre_touche = false car vient_d_etre_touche == true (dans actualisation_couleur_cible())");
        }
        else {
          LEDmode = 1;
          Serial.println("switch à LEDmode = 1 dans dans actualisation_couleur_cible()");
        }

      }

      else if (contagion == true || couleur_changee_manuellement == true) {

          if (apparence_rouge) {
            couleur_leds_actuelle = CRGB::Red;
          }
          else if (apparence_verte) {
            couleur_leds_actuelle = CRGB::Green;
          }
          else if (apparence_bleue) {
            couleur_leds_actuelle = CRGB::Blue;
          }
          else if (apparence_blanche) {
            couleur_leds_actuelle = CRGB::White;
          }
          else if (apparence_invisible) {
            couleur_leds_actuelle = couleur_leds_vies_0; //aucune couleur
          }
          else {
             couleur_leds_actuelle = orange_homelaser; // couleur de la cible par défaut lorsque le mode contagion est activé
          }

      }

      else {
        couleur_leds_actuelle = orange_homelaser; // couleur de la cible par défaut
      }

      actualiser_couleur_leds();
}
