//////Fichier déclarant toutes les constantes globales nécéssaires, ainsi que la fonction setup. 

//// Déclaration des constantes 
const int button = 53;          // bouton de démarrage 
const int led_rouge = 46;   
const int led_jaune = 48;   
const int led_verte = 50;   

void setup() {
  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);

  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton

  Serial.begin(9600); 
}