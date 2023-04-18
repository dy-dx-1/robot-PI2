/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite 
#include "interactions.h"
#include "deplacements.h"

void lift_box(bool going_up){
  // Descente verticale
  Serial.println("Translation de la boîte "); 
  digitalWrite(led_verte, HIGH);

  if (going_up){
    digitalWrite(lift_dir1, LOW); 
    digitalWrite(lift_dir2, HIGH);
  }
  else{
    digitalWrite(lift_dir1, HIGH); 
    digitalWrite(lift_dir2, LOW);
  }
  analogWrite(m_lift, 255); 
  
  if (going_up){
    wait_for_button(endstop_top);
  }
  else{
    wait_for_button(endstop_bottom);
  } 

  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_verte, LOW); 
  digitalWrite(m_lift, LOW); 
  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, LOW); 
}

int comm_code = 0;  // est utilisé pour traduire les boutons appuyés à des actions sur l'arduino 
void dispatch(int current_num) { 
  Serial.print("# received: ");Serial.println(current_num); 
  switch (current_num){
    // Pour les boutons 5,6,7,8 on relâche les flêches de mvt so on veut arrêter tt rotation ou translation plane 
    case 5:
      stop_moving(); 
      break; 
    case 6: 
      stop_moving(); 
      break; 
    case 7: 
      stop_moving();  
      break; 
    case 8: 
      stop_moving(); 
      break;  

    // Pour 11, 12, 13, 14, on appuie sur le bouton du servo ou translation verticale 
    // on n'a donc qu'à effectuer l'action immédiatement 1 fois   
    case 11: 
      // Montée verticale 
      lift_box(true); 
      break;
    case 12:   
      // Descente verticale
      lift_box(false);
      break;
    case 13: 
      // ouverture boîte 
      pignon.write(130); 
      Serial.println("Servo pos 130deg"); 
      break; 
    case 14: 
      // fermeture boîte 
      pignon.write(0); 
      Serial.println("Servo pos 0"); 
      break;

    // Pour 15,16,17,18 on appuie sur une flèche de mvt donc on met les moteurs en mvt indéfiniment, lorsqu'on relâchera ils seront éteints 
    case 15: 
      // translation vers l'arrière 
      translation(false); 
      break; 
    case 16: 
      // translation vers l'avant 
      translation(true); 
      break; 
    case 17: 
      // tour à droite 
      turn(true); 
      break; 
    case 18: 
      // turn left 
      turn(false); 
      break; 
  }
}

void loop() { 
  comm_code = listen_for_codes(); 
  dispatch(comm_code); 
}
