////// Fonctions associées à l'opération de la pince et de son système d'élévation 
 
void lower_box(){
  extern int led_verte; 
  extern int lift_dir1; 
  extern int lift_dir2;
  extern int m_lift;  
  Serial.println("Translation de la boîte "); 
  digitalWrite(led_verte, HIGH); 
  digitalWrite(lift_dir1, HIGH); 
  digitalWrite(lift_dir2, LOW);
  analogWrite(m_lift, 200); 

  wait_for_button(endstop_top); 

  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_verte, LOW); 
  digitalWrite(m_lift, LOW); 
  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, LOW);
}

void lift_box(){
  extern int led_verte; 
  extern int lift_dir1; 
  extern int lift_dir2;
  extern int m_lift;  
  Serial.println("Translation de la boîte "); 
  digitalWrite(led_verte, HIGH); 

  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, HIGH);
  analogWrite(m_lift, 200); 
  
  wait_for_button(endstop_bottom);  

  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_verte, LOW); 
  analogWrite(m_lift, 0); 
  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, LOW);
}
/*
void open_box(int width){
  //// Ouvre la pince d'un certain nb de mm 
  // On considère qu'il n'y a pas de glissement entre la crémaillère et le pignon
  extern int  
  int angle = (width / (diametre_pignon/2))*(180/3.14159); // angle en radians converti en degrés  
  Serial.print("Ouverture de la pince commencée: "); Serial.print(angle); Serial.println("degrés"); 
  pignon.write(angle); // on considère qu'on a le range nécéssaire pour complèter l'ouverture 
  Serial.println("Pince ouverte"); 
}
*/ 
