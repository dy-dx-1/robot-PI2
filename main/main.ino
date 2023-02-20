/// Code central qui gère toute la logique des opérations

// Importation des modules 
#include "deplacements.h"

#include <Stepper.h>
#include <AccelStepper.h>

const int bouton = 42;   // définition de la broche 42 de la carte en tant que variable
const int led_rouge = 46;   // définition de la broche 46 de la carte en tant que variable
const int led_jaune = 48;   // définition de la broche 48 de la carte en tant que variable
const int led_verte = 50;   // définition de la broche 50 de la carte en tant que variable
int etat = HIGH;
int n;

AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);

void setup() {
  // put your setup code here, to run once:
  pinMode(bouton, INPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  etat=demarrage(etat);
  if (etat == LOW){
    deplacement();
    moteur_G.run();
    moteur_D.run();

  }
}

int demarrage(int etat){


  if(etat == HIGH) {
    etat = digitalRead(bouton); // Rappel : bouton = 42
    digitalWrite(led_verte, HIGH); // éteint la LED
    digitalWrite(led_rouge, LOW);  // allume la LED
    digitalWrite(led_jaune, HIGH); // éteint la LED
  }
  else {
    digitalWrite(led_jaune, HIGH); // éteint la LED
    digitalWrite(led_verte, LOW); // allume la LED
    digitalWrite(led_rouge, HIGH); // éteint la LED
  }
  return (etat);
  
}


void deplacement() {

  moteur_G.setMaxSpeed(400); //= à 11.7 rpm
  moteur_G.setAcceleration(200.0);
  moteur_G.moveTo(-4000);
  moteur_D.setMaxSpeed(400);
  moteur_D.setAcceleration(200.0);
  moteur_D.moveTo(4000);

  
}
