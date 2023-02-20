////// Fonctions associées au déplacement du robot 

#include <AccelStepper.h>
const int max_stepper_speed = 400; 
const float stepper_accel = 200.0; 

// Création des objets représentant les steppers 
AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);

void stepper_setup(){
  //// Fonction ajustant les paramètres de fonctionnement des moteurs 
    moteur_G.setMaxSpeed(max_stepper_speed); //= à 11.7 rpm
    moteur_G.setAcceleration(stepper_accel);
    moteur_D.setMaxSpeed(max_stepper_speed); //= à 11.7 rpm
    moteur_D.setAcceleration(stepper_accel);
}

int convert_dist_pas(int distance_mm){
  //// Fonction qui converti une distance linéaire en mm à un nombre de pas équivalent pour nos steppers, en supposant un roulement sans glisser 
  int rayon_roue = 30; // en mm 

  if (distance_mm<0){
    // Si on a une distance négative, il faut forcer une valeur positive avant de faire le calcul pour avoir une bonne valeur car unsigned long ne peut être négatif
    distance_mm = -distance_mm; 
    unsigned long nominateur = 1024L*distance_mm;  // important de convertir 1024 à long pour faire la multi et avoir le bon résultat 
    return -(nominateur)/(rayon_roue * 3.14159);  // ici on force un négatif pour reculer 
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

    // Déclaration du nb de pas à faire au moteur 
    moteur_G.move(N); 
    moteur_D.move(-N);     // Un des moteurs n'est pas dans le même sens physique, d'où la valeur <0 pour préserver une ligne droite 
    int distance_left{10}; 

    // La méthode run doit être appellée en continu jusqu'à qu'on arrive à destination
    while (distance_left != 0){
      moteur_G.run();
      moteur_D.run();
      distance_left = moteur_D.distanceToGo(); // distanceToGo donne le nb de pas restants avant de se rendre à notre objectif 
    }
}

void turn(int theta){
    //// Fonction permettant de tourner sur place

    // Conversion de l'angle donné à un nombre de pas 
    int N = 5000; ///////////////////////////////////////////////////////////TODO: ajouter maths pour faire la conversion 

    // Déclaration du nb de pas à faire et activation de ceux-ci jusqu'à que ce soit atteint 
    moteur_G.move(N); 
    moteur_D.move(N); 
    int distance_left{10}; 
    while (distance_left != 0){
      moteur_G.run();
      moteur_D.run();
      distance_left = moteur_D.distanceToGo(); 
    }
}