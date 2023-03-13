//////Fichier déclarant toutes les constantes globales nécéssaires, ainsi que la fonction setup. 

//// Importation des librairies nécéssaires 
#include <Servo.h> 
#include <AccelStepper.h>

//// Déclaration des constantes des moteurs 
const int base_stepper_speed = 988; // en steps/s 
const float stepper_accel = 400;    // steps/s^2
const int rayon_roue = 33;          // rayon des roues motrices en mm 
const int d_entre_roues = 132;      // distance entre les roues motrices en mm 

// Création des objets représentant les moteurs 
AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);
AccelStepper moteur_lift(AccelStepper::FULL4WIRE, 29, 25, 27, 23); // moteur pour la translation verticale de la pince
Servo pignon; 

//// Déclaration des constantes associées aux pins 
const int button = 53;          // bouton de démarrage 
const int led_rouge = 46;   
const int led_jaune = 48;   
const int led_verte = 50;   
const int servo_pin = 12; 

void setup() {
  pignon.attach(servo_pin);      // création d'un lien entre le servo et le pin d'info PWM 

  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton

  void stepper_setup(); 
  stepper_setup(); // Initialisation des vitesses et accélérations des steppers 

  Serial.begin(9600); 
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

  moteur_lift.setSpeed(base_stepper_speed); 
  moteur_lift.setMaxSpeed(base_stepper_speed); 
  moteur_lift.setAcceleration(base_stepper_speed); 
}