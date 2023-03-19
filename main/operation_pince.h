////// Fonctions associées à l'opération de la pince et de son système d'élévation 
 
void lift_box(bool going_up){
  //// Indique au moteur DC de la pince s'il doit monter ou descendre et effectue l'action jusqu'à que l'endstop soit atteint 
  Serial.println("Mouvement en translation verticale commence"); 
  if (going_up){
    // TODO: Ajouter set des pins (ou whatever méthode) pour indiquer direction
  }
  else{ 
    // TODO: Ajouter set des pins (ou whatever méthode) pour indiquer direction
  }
  digitalWrite(moteur_lift, HIGH); 
  // TODO: ajouter condition d'arrêt, pour l'instant ce sera juste un timer de 5s pour démontrer 
  unsigned long t1 = millis();
  while ((millis()-t1)<=3000){
    //wait 
  }
  digitalWrite(moteur_lift, LOW); 
  Serial.println("Mouvement en translation verticale fini"); 
}

void open_box(int width){
  //// Ouvre la pince d'un certain nb de mm 
  // On considère qu'il n'y a pas de glissement entre la crémaillère et le pignon 
  int angle = (width / (diametre_pignon/2))*(180/3.14159); // angle en radians converti en degrés  
  Serial.print("Ouverture de la pince commencee: "); Serial.print(angle); Serial.println("degres"); 
  pignon.write(angle); // on considère qu'on a le range nécéssaire pour complèter l'ouverture 
  Serial.println("Pince ouverte"); 
}
