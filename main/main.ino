/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite 
#include "interactions.h"
#include "deplacements.h"
////////////////////////////////////////////#include "operation_pince.h"

int comm_code = 0;  // est utilisé pour traduire les boutons appuyés à des actions sur l'arduino 
int last_significant_command = 0; // permet de tenir compte de la dernière commande passée (par exemple quand on appuie sur un bouton)
void dispatch(int current_num) { 
  Serial.print("# received: ");Serial.println(current_num); 
  if (current_num!=0){
    last_significant_command = current_num; // signal de traiter un événement qui vient de se passer 
  }
  if (current_num == 0 && last_significant_command != 0){
    // Si on rentre ici, il faut traiter l'événement 
    // Tout d'abord on considère les cas où on a relâché un bouton de déplacement, donc on veut juste retourner à l'état d'attente 
    // les valeurs des boutons de déplacement sont de 5 à 8 lorsque il sont relâchés  
    if ((last_significant_command-10)<0 && last_significant_command>=5){
      stop_translation(); 
      last_significant_command = 0; // indication de ne plus considèrer qu'on a intéragi avec un bouton 
    }
    // Maintenant on considère le cas où on a appuyé sur un bouton de déplacement, donc on veut call l'action de déplacement 
    // en permanence jusqu'à que le bouton soit relâché (le if juste en haut). Les boutons sont 15, 16, 17, 18
    else if ((last_significant_command-10)>0 && last_significant_command>=15){
      switch (last_significant_command){
        case 15: 
          translation(distance_translation); 
          break; 
        case 16:
          translation(-distance_translation); 
          break; 
        case 17:
          turn(true); 
          break; 
        case 18:
          turn(false); 
          break; 
      }
      // Notez qu'il n'y a pas de réassignation de last_significant_command, étant donné qu'on veut retourner ici jusqu'à que le bouton soit 
      // relaché, ce qui arrivera quand current_num != 0 
    }
    // Ensuite, il ne reste que les boutons d'actions spécifiques, celles-ci sont activées 1 seule fois lorsque le bouton est appuyé 
    // donc on ne considère que quand on reçoit 11, 12, 13 et 14. 1, 2, 3 et 4 sont ignorés car on peut forcer le retour à la normale après 
    // l'execution de la fonction associée au bouton 
    else if ((last_significant_command-10)<0 && last_significant_command<=5){
      switch (last_significant_command){ 
        case 11:
          break;
        case 12:
          break; 
        case 13:
          break;
        case 14:
          break; 
      }
      last_significant_command = 0;  // tel que mentionné plus tôt, on on peut maintenant ignoré qu'on a appuyé sur un bouton 
    }
    else{
      // si on arrive ici, on est entrain d'appuyer sur le bouton d'action spéciale donc on ne fait qu'ignorer jusqu'à qu'on relâche
    }
  }
}

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  comm_code = listen_for_codes(); 
  dispatch(comm_code); 

}