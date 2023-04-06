////// Fonctions associées à l'opération de la pince et de son système d'élévation 
 
void lift_box(){
  extern int led_bleue; 
  extern int lift_dir1; 
  extern int lift_dir2;
  extern int m_lift;  
  Serial.println("Translation de la boîte "); 
  digitalWrite(led_bleue, HIGH); 

  digitalWrite(lift_dir1, HIGH); 
  digitalWrite(lift_dir2, LOW);
  digitalWrite(m_lift, HIGH); 
  unsigned long t1 = millis(); 
  while ((t1 - millis())<=2000){
    // attendre tant qu'on est pas rendus  
  }
  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_bleue, LOW); 
  digitalWrite(m_lift, LOW); 
  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, LOW);
}
void lower_box(){
  extern int led_bleue; 
  extern int lift_dir1; 
  extern int lift_dir2;
  extern int m_lift;  
  Serial.println("Translation de la boîte "); 
  digitalWrite(led_bleue, HIGH); 

  digitalWrite(lift_dir1, LOW); 
  digitalWrite(lift_dir2, HIGH);
  digitalWrite(m_lift, HIGH); 
  unsigned long t1 = millis(); 
  while ((t1 - millis())<=2000){
    // attendre tant qu'on est pas rendus  
  }
  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_bleue, LOW); 
  digitalWrite(m_lift, LOW); 
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
