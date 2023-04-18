////// Fonctions associées au déplacement du robot 

int convert_dist_pas(int distance_mm){
  //// Fonction qui converti une distance linéaire en mm à un nombre de pas équivalent pour nos steppers, en supposant un roulement sans glisser 
  if (distance_mm<0){
    // Si on a une distance négative, il faut forcer une valeur positive avant de faire le calcul pour avoir une bonne valeur car unsigned long ne peut être négatif
    distance_mm = -distance_mm; 
    unsigned long nominateur = 1024L*distance_mm;  // important de convertir 1024 à long pour faire la multi et avoir le bon résultat 
    return -((nominateur)/(rayon_roue * 3.14159));  // ici on force un négatif pour reculer 
  }
  else {
    unsigned long nominateur = 1024L*distance_mm;  // important de convertir 1024 à long pour faire la multi et avoir le bon résultat
    return (nominateur)/(rayon_roue * 3.14159); 
  }
}

void translation(int x){
  //// Fonction permettant de se déplacer d'une distance de x mm
  // Conversion de mm à pas, les valeurs négatives sont supportées par la fonction 
  digitalWrite(led_verte, HIGH);

  if (x>0){
    digitalWrite(mot_dir1, HIGH); 
    digitalWrite(mot_dir2, LOW); 

    digitalWrite(mot_dir3, HIGH); 
    digitalWrite(mot_dir4, LOW); 
  }
  else{
    digitalWrite(mot_dir1, LOW); 
    digitalWrite(mot_dir2, HIGH); 

    digitalWrite(mot_dir3, LOW); 
    digitalWrite(mot_dir4, HIGH); 
  }

  analogWrite(m1, 150); 
  analogWrite(m2, 150); 
  Serial.println("In movement"); 
}
void stop_translation(){
  digitalWrite(led_verte, LOW); 
  digitalWrite(m1, LOW); 
  digitalWrite(m2, LOW); 
  Serial.println("Stop translation"); 
}
void turn(bool turning_right){
  if (turning_right){
    digitalWrite(mot_dir1, HIGH); 
    digitalWrite(mot_dir2, LOW); 
    digitalWrite(mot_dir3, LOW); 
    digitalWrite(mot_dir4, HIGH); 
  }
  else{
    digitalWrite(mot_dir1, LOW); 
    digitalWrite(mot_dir2, HIGH); 
    digitalWrite(mot_dir3, HIGH); 
    digitalWrite(mot_dir4, LOW); 
  }
  analogWrite(m1, 150); 
  analogWrite(m2, 150); 
  Serial.println("In movement");
}
