//////Fichier déclarant toutes les constantes globales nécéssaires, ainsi que la fonction setup. 

//// Importation des librairies nécéssaires 
#include <Servo.h>
#include <AccelStepper.h>

//// Déclaration des constantes des moteurs 
const int base_stepper_speed = 988; // en steps/s 
const float stepper_accel = 400; 
const int rayon_roue = 33; // rayon des roues motrices en mm 
const int d_entre_roues = 132; // distance entre les roues motrices en mm //////////////////////////// À UPDATE!!!!!!!!!!!!!!!!!!!!!

// Création des objets représentant les moteurs 
AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);
Servo pignon; 

//// Déclaration des constantes associées aux pins 
const int button = 53;          // bouton de démarrage 
const int led_rouge = 46;   
const int led_jaune = 48;   
const int led_verte = 50;   
const int servo_pin = 12; 

void setup() {
  pignon.attach(servo_pin); 
  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);

  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton

  Serial.begin(9600); 
}