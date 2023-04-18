////// Fonctions associées au déplacement du robot 

void translation(bool going_front){
  //// Fonction permettant de se déplacer d'une distance de x mm
  // Conversion de mm à pas, les valeurs négatives sont supportées par la fonction 
  digitalWrite(led_verte, HIGH);

  if (going_front){
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
  Serial.println("Translation"); 
}

void stop_moving(){
  digitalWrite(led_verte, LOW); 
  digitalWrite(m1, LOW); 
  digitalWrite(m2, LOW); 
  Serial.println("Moteurs des roues éteints"); 
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
  Serial.println("Turning");
}