//////Fichier déclarant toutes les constantes globales nécéssaires, ainsi que la fonction setup. 

//// Importation des librairies nécéssaires 
#include <string.h> 
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "bluetooth_config.h"

#include <Servo.h> 
#include <AccelStepper.h>

//// Création de l'objet bluetooth
Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN); 

//// Déclaration des constantes des moteurs 
const int base_stepper_speed = 988; // en steps/s 
const float stepper_accel = 400;    // steps/s^2
const int rayon_roue = 33;          // rayon des roues motrices en mm 
const int d_entre_roues = 132;      // distance entre les roues motrices en mm 

const int diametre_pignon = 24;     // Diamètre du pignon du servo de la boîte en mm 
int distance_translation = 100; // Distance en translation fixe de base [mm], peut être modifié avec l'appli (voir deplacements.h)

// Création des objets représentant les moteurs 
AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);
const int moteur_lift = 35; // Pin signal du moteur DC de la pince 
//TODO: Ajouter pins de direction pour le moteur DC 
Servo pignon; 

//// Déclaration des constantes associées aux pins 
const int button = 53;          // bouton de démarrage 
const int led_rouge = 46;   
const int led_jaune = 48;   
const int led_verte = 50;  
const int led_bleue = 52;  
const int servo_pin = 12; 

void setup() {
  Serial.begin(115200); 
  pignon.attach(servo_pin);      // création d'un lien entre le servo et le pin d'info PWM 
  pignon.write(0);            // On place le servo à sa position de départ 
  pinMode(moteur_lift, OUTPUT); 

  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_bleue, OUTPUT); 
  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton

  void stepper_setup(); // Forward declaration de stepper_setup pour le mettre en bas de setup() 
  stepper_setup(); // Initialisation des vitesses et accélérations des steppers 
  
  start_bluetooth_connection(); 
}

void stepper_setup(){
  //// Fonction ajustant les paramètres de fonctionnement des moteurs à leur valeurs de défaut 
  // setSpeed --> s'applique juste quand runSpeed() est appellé (pendant les tours) 
  // setMaxSpeed --> s'applique juste quand move() est appellé (pendant les translations) 
  // setAcceleration --> s'applique partout 
  moteur_G.setSpeed(base_stepper_speed); 
  moteur_G.setMaxSpeed(base_stepper_speed); 
  moteur_G.setAcceleration(stepper_accel);

  moteur_D.setSpeed(base_stepper_speed); 
  moteur_D.setMaxSpeed(base_stepper_speed); 
  moteur_D.setAcceleration(stepper_accel);
}