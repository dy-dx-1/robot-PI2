////// Fonctions associées au déplacement du robot 

void stepper_setup(){
  //// Fonction ajustant les paramètres de fonctionnement des moteurs 
  moteur_G.setSpeed(base_stepper_speed); 
  moteur_G.setSpeed(base_stepper_speed); 
  moteur_G.setMaxSpeed(base_stepper_speed); 
  moteur_G.setAcceleration(stepper_accel);
  moteur_D.setMaxSpeed(base_stepper_speed); 
  moteur_D.setAcceleration(stepper_accel);
}

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
  int N = convert_dist_pas(x);
  Serial.print("Nombre de pas en translation: ");
  Serial.print(N); 
  Serial.print(" ; Temps: "); Serial.println(N/base_stepper_speed);
  
  // Déclaration du nb de pas à faire au moteur 
  moteur_G.move(-N); 
  moteur_D.move(N);     // Un des moteurs n'est pas dans le même sens physique, d'où la valeur <0 pour préserver une ligne droite 

  // Commencement du déplacement est indiqué par la lumière verte 
  digitalWrite(led_verte, HIGH); 

  // La méthode run doit être appellée en continu jusqu'à qu'on arrive à destination
  while (moteur_D.distanceToGo() != 0){ // distanceToGo donne le nb de pas restants avant de se rendre à notre objectif 
    moteur_G.run();
    moteur_D.run();
  }
  digitalWrite(led_verte, LOW);   // on éteint la lumière pour signifier qu'on a fini le mouvement 
}

void turn(float theta, int time_for_turn){
  //// Fonction permettant de tourner 
  // 'theta': angle position finale [deg] positif si va de l'est vers le nord et négatif s'il va de ouest vers le nord. 
  // 'primary_wheel'--> roue tournant le plus vite --> base_stepper_speed 
  // 'secondary_wheel'--> roue tournant le plus lentement / la plus proche de l'axe de rotation
  // 'time_for_turn' --> temps alloué pour la rotation
  theta = theta*3.14159/180; 
  float secondary_wheel_speed = base_stepper_speed - (((abs(d_entre_roues*theta))/(rayon_roue*time_for_turn))*(1024/3.14159)); // rad/s converti à step/s
  if (theta<0) { // on veut tourner 'à gauche', ouest vers nord 
    moteur_D.setSpeed(base_stepper_speed); 
    moteur_G.setSpeed(-secondary_wheel_speed); 
  }
  else { // on assume que notre code n'enverra pas de theta = 0
    moteur_D.setSpeed(secondary_wheel_speed); 
    moteur_G.setSpeed(-base_stepper_speed); 
  }

  digitalWrite(led_verte, HIGH); 
  Serial.print("Début d'un tour avec base_speed "); Serial.print(base_stepper_speed); Serial.print(" ; secondary_speed: "); Serial.println(secondary_wheel_speed); 
  unsigned long time_for_turn_ms = time_for_turn*1000; 
  unsigned long start_timer = millis(); 
  while ((millis()-start_timer)<time_for_turn_ms){
    moteur_G.runSpeed(); 
    moteur_D.runSpeed(); 
  }

  digitalWrite(led_verte, LOW); 
  Serial.println("Tour fini"); 
}