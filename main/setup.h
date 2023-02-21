//////Fichier déclarant toutes les constantes globales nécéssaires. 

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

  Serial.begin(9600); 
}