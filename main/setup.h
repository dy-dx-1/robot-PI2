//////Fichier déclarant toutes les constantes globales nécéssaires, ainsi que la fonction setup. 

//// Importation des librairies nécéssaires 
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "bluetooth_config.h"

#include <Servo.h> 

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
const int mot_dir1 = 22; 
const int mot_dir2 = 24; // Pins de direction du moteur DC
const int mot_dir3 = 43; 
const int mot_dir4 = 45; 
const int m1 = 3;  
const int m2 = 2;  
Servo pignon; 

const int m_lift = 9; 
const int lift_dir1 = 34; 
const int lift_dir2 = 32; 

//// Déclaration des constantes associées aux pins 
const int button = 53;          // bouton de démarrage 
const int endstop_bottom = 31; 
const int endstop_top = 33; 
const int led_rouge = 8;   
const int led_jaune = 7;   
const int led_verte = 6;  
const int led_bleue = 5;  
const int servo_pin = 12; 

void setup() {
  Serial.begin(115200); 
  pignon.attach(servo_pin);      // création d'un lien entre le servo et le pin d'info PWM 
  pignon.write(0);            // On place le servo à sa position de départ 
  pinMode(mot_dir1, OUTPUT); 
  pinMode(mot_dir2, OUTPUT); 
  pinMode(mot_dir3, OUTPUT); 
  pinMode(mot_dir4, OUTPUT); 
  pinMode(m1, OUTPUT); 
  pinMode(m2, OUTPUT); 
  pinMode(m_lift, OUTPUT); 

  pinMode(led_rouge, OUTPUT);
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_bleue, OUTPUT); 
  pinMode(button, INPUT_PULLUP);  // utilisation d'un pullup resistor pour façiliter l'utilisation du bouton
  pinMode(endstop_bottom, INPUT_PULLUP); 
  pinMode(endstop_top, INPUT_PULLUP); 

  digitalWrite(lift_dir1, LOW); // on s'assure que le moteur DC est figé 
  digitalWrite(lift_dir2, LOW); 
  
  void wait_for_button(int button); //défini dans intéractions 
  wait_for_button(button); 
  digitalWrite(led_jaune, HIGH); // pour signifier qu'on est en attente de connection 
  start_bluetooth_connection(); 
  // connection completée avec succès 
  void led_rainbow(); 
  led_rainbow(); 
  digitalWrite(led_bleue, HIGH); 
}