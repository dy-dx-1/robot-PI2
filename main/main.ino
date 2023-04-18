/// Code principal qui gère toute la logique des opérations

// Importation des modules
#include "setup.h"        // est en premier afin que les constantes globales entrent dans le scope général tout de suite 
#include "interactions.h"
#include "deplacements.h"
//#include "operation_pince.h"
////////////////////////////////////////////#include "operation_pince.h"

int comm_code = 0;  // est utilisé pour traduire les boutons appuyés à des actions sur l'arduino 
void dispatch(int current_num) { 
  Serial.print("# received: ");Serial.println(current_num); 
  switch (current_num){
    case 17: 
      // turn left 
      turn(false); 
      break; 
    case 18: 
      turn(true); 
      break; 
    case 7: 
      // turn left 
      stop_translation();  
      break; 
    case 8: 
      stop_translation(); 
      break;    
    case 16: 
      // translation vers l'arrière 
      translation(-1); 
      break; 
    case 15: 
      // translation vers l'avant 
      translation(1); 
      break; 
    case 5: 
      // stop translation 
      stop_translation(); 
      break; 
    case 6: 
      stop_translation(); 
      break; 
    case 13: 
      // ouverture boîte 
      pignon.write(130); 
      Serial.println("Servo pos 180deg"); 
      break; 
    case 14: 
      // fermeture boîte 
      pignon.write(0); 
      Serial.println("Servo pos 0"); 
      break;
    case 11: 
      // Montée verticale 
      Serial.println("Translation de la boîte "); 
      digitalWrite(led_verte, HIGH); 

      digitalWrite(lift_dir1, LOW); 
      digitalWrite(lift_dir2, HIGH);
      analogWrite(m_lift, 255); 
      
      wait_for_button(endstop_top);  

      Serial.println("Translation de la boîte finie"); 
      digitalWrite(led_verte, LOW); 
      digitalWrite(m_lift, LOW); 
      digitalWrite(lift_dir1, LOW); 
      digitalWrite(lift_dir2, LOW);
      break; 
    case 12:   
      // Descente verticale
      Serial.println("Translation de la boîte "); 
      digitalWrite(led_verte, HIGH); 
      digitalWrite(lift_dir1, HIGH); 
      digitalWrite(lift_dir2, LOW);
      analogWrite(m_lift, 255); 

      wait_for_button(endstop_bottom); 

      Serial.println("Translation de la boîte finie"); 
      digitalWrite(led_verte, LOW); 
      digitalWrite(m_lift, LOW); 
      digitalWrite(lift_dir1, LOW); 
      digitalWrite(lift_dir2, LOW); 
      break;
  }
}

void loop() { 
  //// Logique centrale du code, distances en mm et angles en degrés 
  comm_code = listen_for_codes(); 
  dispatch(comm_code); 

}