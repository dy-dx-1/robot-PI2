////// Fonctions associées à l'opération de la pince et de son système d'élévation 
 
void lift_box(int height){
  //// Prend une hautur en mm et la converti en le nb de pas que le stepper doit faire pour monter/descendre la plaque
  int steps{}; 
  // conversion hauteur-steps 
  // Translation 
  Serial.print("Translation de la boîte de ");Serial.print(height); Serial.println(" mm"); 
  digitalWrite(led_bleue, HIGH); 
  moteur_lift.move(steps); 
  while (moteur_lift.distanceToGo()!=0){
    // attendre tant qu'on est pas rendus 
    moteur_lift.run(); 
  }
  Serial.println("Translation de la boîte finie"); 
  digitalWrite(led_bleue, LOW); 
}

void open_box(int width){
  //// Ouvre la pince d'un certain nb de mm 
  // On considère qu'il n'y a pas de glissement entre la crémaillère et le pignon 
  int angle = (width / (diametre_pignon/2))*(180/3.14159); // angle en radians converti en degrés  
  Serial.print("Ouverture de la pince commencée: "); Serial.print(angle); Serial.println("degrés"); 
  pignon.write(angle); // on considère qu'on a le range nécéssaire pour complèter l'ouverture 
  Serial.println("Pince ouverte"); 
}
