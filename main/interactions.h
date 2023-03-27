////// Fichier regroupant les fonctions nécessaires à l'intéraction entre la voiture et les utilisateurs 
////// ex: clignoter une lumière, démarrer le prototype, etc... 

void wait_for_button(int switch_button){
  //// Pause le programme en attendant qu'on appuie sur le bouton de démarrage 
  digitalWrite(led_rouge, HIGH);    // Lumière rouge allumée, toutes les autres éteintes en attendant 
  digitalWrite(led_jaune, LOW); 
  digitalWrite(led_verte, LOW); 
  Serial.println("En attente du bouton"); 
  while (digitalRead(switch_button)!=0){
    // Ne rien faire pendant que le bouton n'est pas appuyé
  }  
  delay(100);   // Attente de 0.1s pour éviter des interférences de 'bounce' si on call cette fonction encore rapidement après 
  Serial.println("Attente finie"); 
  digitalWrite(led_rouge, LOW);     // On éteint la lumière rouge pour signaler que le temps d'attente est fini 
}

void blink_led(String couleur){
  //// Clignote une des leds du prototype 
  int led_pin{};
  int dtime = 400;                  // Période du clignotage en ms 
  if (couleur == "rouge"){
    led_pin = led_rouge; 
  }
  else if (couleur == "verte"){
    led_pin = led_verte; 
  }
  else if (couleur == "jaune"){
    led_pin = led_jaune; 
  }
  else if (couleur == "bleue"){
    led_pin = led_bleue; 
  }
  else {
    Serial.println("COULEUR DE LED INTROUVABLE"); 
    return; 
  }
  for (int i=0; i<=2; i++){
    delay(dtime); 
    digitalWrite(led_pin, HIGH); 
    delay(dtime); 
    digitalWrite(led_pin, LOW);
  } 
}