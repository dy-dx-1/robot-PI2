////// Fichier regroupant les fonctions nécessaires à l'intéraction entre la voiture et les utilisateurs 
////// ex: clignoter une lumière, démarrer le prototype, etc... 

void wait_for_button(int switch_button){
  //// Pause le programme en attendant qu'on appuie sur le bouton de démarrage 
  digitalWrite(led_rouge, HIGH);    // Lumière rouge allumée, toutes les autres éteintes en attendant 
  digitalWrite(led_jaune, LOW); 
  digitalWrite(led_verte, LOW); 
  Serial.print("En attente du bouton "); Serial.println(switch_button); 
  while (digitalRead(switch_button)!=0){
    // Ne rien faire pendant que le bouton n'est pas appuyé
  }  
  delay(100);   // Attente de 0.1s pour éviter des interférences de 'bounce' si on call cette fonction encore rapidement après 
  Serial.println("Attente finie"); 
  digitalWrite(led_rouge, LOW);     // On éteint la lumière rouge pour signaler que le temps d'attente est fini 
}

void led_rainbow(){
  for (int i=0; i<=3; i++){
    digitalWrite(led_rouge, HIGH); 
    delay(100); 
    digitalWrite(led_rouge, LOW);

    digitalWrite(led_jaune, HIGH); 
    delay(100); 
    digitalWrite(led_jaune, LOW);

    digitalWrite(led_verte, HIGH); 
    delay(100); 
    digitalWrite(led_verte, LOW);

    digitalWrite(led_bleue, HIGH); 
    delay(100); 
    digitalWrite(led_bleue, LOW);
  }
}