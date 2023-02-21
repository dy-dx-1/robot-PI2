/// Code central qui gère toute la logique des opérations

// Importation des modules
#include "setup.h" // inclut en premier afin que les constantes globales entrent dans le scope général tout de suite  
#include "interactions.h"
#include "deplacements.h"

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  stepper_setup(); // préparation des steppers (accel et vitesse)
  wait_for_button(); 
  translation(50); 
  blink_led("jaune"); 
  translation(50); 
}
