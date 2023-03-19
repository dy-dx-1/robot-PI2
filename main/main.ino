/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite 
#include "interactions.h"
#include "deplacements.h"
#include "operation_pince.h"

int comm_code = 0;  // est utilisé pour traduire les boutons appuyés à des actions sur l'arduino 

void dispatch(int current_num) { 
  Serial.print("# received: ");Serial.println(current_num); 
  switch (current_num){
    case 0:
      // Rien ne se passe, car pas de nouvelle information 
      break; 
    case 1:
      // Monter la boîte 
      lift_box(true);
      break; 
    case 2:
      lift_box(false); 
      break; 
    case 3:
      pignon.write(90); 
      break; 
    case 4:
      pignon.write(180); 
      break; 
    case 5:
      // Translation vers l'avant, distance_translation peut être modifié dans bluetooth_config.h
      translation(distance_translation); 
      break; 
    case 6:
      // Translation vers l'arrière, distance_translation peut être modifié dans bluetooth_config.h
      translation(-distance_translation); 
      break; 
    case 7:
      turn(45, 5); // Need to do tests and fix parameters 
      break; 
    case 8:
      turn(-45, 5); // Need to do tests and fix parameters 
      break; 
  }
}

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  comm_code = listen_for_codes(); 
  dispatch(comm_code); 
}