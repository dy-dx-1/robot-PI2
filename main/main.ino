/// Code central qui gère toute la logique des opérations

// Importation des modules 
#include "deplacements.h"

const int bouton = 42;   // définition de la broche 42 de la carte en tant que variable
const int led_rouge = 46;   // définition de la broche 46 de la carte en tant que variable
const int led_jaune = 48;   // définition de la broche 48 de la carte en tant que variable
const int led_verte = 50;   // définition de la broche 50 de la carte en tant que variable
int etat = HIGH;
int n;


void setup() {
  // put your setup code here, to run once:
  pinMode(bouton, INPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);

  // Setup des moteurs 
  stepper_setup(); 

  Serial.begin(9600); 
}

void loop() { 
  //translation(-300); 
  //Serial.println("recul"); 
  //translation(150); 
  turn(2); 
  while (true){}
}


int demarrage(int etat){
  etat = digitalRead(bouton); 
  if(etat == HIGH) {
    digitalWrite(led_verte, HIGH); // éteint la LED
    digitalWrite(led_rouge, LOW);  // allume la LED
    digitalWrite(led_jaune, HIGH); // éteint la LED
  }
  else {
    delay(500); 
    digitalWrite(led_jaune, HIGH); // éteint la LED
    digitalWrite(led_verte, LOW); // allume la LED
    digitalWrite(led_rouge, HIGH); // éteint la LED
  }
  return (etat);
}

