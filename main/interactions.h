////// Fichier regroupant les fonctions nécessaires à l'intéraction entre la voiture et les utilisateurs 
////// ex: clignoter une lumière, démarrer le prototype, etc... 

void wait_for_button(){
  //// Pause le programme en attendant qu'on appuie sur le bouton de démarrage 
  digitalWrite(led_rouge, HIGH); 
  digitalWrite(led_jaune, LOW); 
  digitalWrite(led_verte, LOW); 
  while (digitalRead(button)!=0){ // Pendant que le bouton n'est pas appuyé
    Serial.println("Waiting for startup"); 
  }
  digitalWrite(led_rouge, LOW); 
  digitalWrite(led_verte, HIGH); 
}

void blink_led(String couleur){
  int led_pin{};
  int dtime = 500;  
  if (couleur == "rouge"){
    led_pin = led_rouge; 
  }
  else if (couleur == "verte"){
    led_pin = led_verte; 
  }
  else if (couleur == "jaune"){
    led_pin = led_jaune; 
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