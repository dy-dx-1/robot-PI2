/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite 
#include "interactions.h"
#include "deplacements.h"
#include "operation_pince.h"

void dispatch(int num) { 
  switch (num){
    case 0:  
      break; 
    case 1: 
      break; 
    case 2:
      break; 
    case 3:
      break; 
    case 4:
      break; 
    case 5: 
      break; 
    case 6:
      break; 
    case 7:
      break; 
    case 8:
      break; 
  } 
  Serial.print("# received: ");Serial.println(num); 
}

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  comm_code = listen_for_codes(); 
  dispatch(comm_code);   
  comm_code = 0; 
}