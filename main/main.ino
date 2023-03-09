/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite  
#include "communication.h"
#include "interactions.h"
#include "deplacements.h"
#include "operation_pince.h"

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  wait_for_button(); 
  translation(500); 
}