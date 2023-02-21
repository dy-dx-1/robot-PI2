/// Code central qui gère toute la logique des opérations

// Importation des modules 
#include "deplacements.h"

const int button= 53;   // définition de la broche 42 de la carte en tant que variable
const int led_rouge = 46;   // définition de la broche 46 de la carte en tant que variable
const int led_jaune = 48;   // définition de la broche 48 de la carte en tant que variable
const int led_verte = 50;   // définition de la broche 50 de la carte en tant que variable


void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);

  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton
  // Setup des moteurs 
  stepper_setup(); 

  Serial.begin(9600); 
}

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  wait_for_button(); 
  translation(-100); 
  translation(50); 
}


void wait_for_button(){
  digitalWrite(led_rouge, HIGH); 
  digitalWrite(led_jaune, LOW); 
  digitalWrite(led_verte, LOW); 
  while (digitalRead(button)!=0){ // Pendant que le bouton n'est pas appuyé
    Serial.println("Waiting for startup"); 
  }
  digitalWrite(led_rouge, LOW); 
  digitalWrite(led_verte, HIGH); 
}
