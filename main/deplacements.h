/// Fonctions associées au déplacement du robot 
#include <Stepper.h>
#include <AccelStepper.h>

AccelStepper moteur_G(AccelStepper::FULL4WIRE, 11, 9, 10, 8);
AccelStepper moteur_D(AccelStepper::FULL4WIRE, 7, 5, 6, 4);

void stepper_setup(){
    moteur_G.setMaxSpeed(400); //= à 11.7 rpm
    moteur_G.setAcceleration(200.0);
    moteur_D.setMaxSpeed(400); //= à 11.7 rpm
    moteur_D.setAcceleration(200.0);
}

int convert_dist_pas(int distance_mm){
  int rayon_roue = 30; // en mm 
  //Serial.print("------>>>>>>>>>>>>>>>");
  unsigned long nominateur = 1024L*distance_mm;  // important de convertir 1024 à long pour faire la multi et avoir le bon résultat
  return (nominateur)/(rayon_roue * 3.14159); 
}

void stop(){
    moteur_G.move(1); 
    moteur_D.move(1);
    while (moteur_G.distanceToGo()!=0){
      moteur_G.run();
      moteur_D.run(); 
    }
}

void translation(int x){
    // Fonction permettant de se déplacer d'une distance de x cm 
    // je te laisse libre si tu veux faire plusieurs fonctions (ex move_front, move_back, turn_right, turn_left, etc)
    // ou si tu veux handle tout avec une fonction et des paramètres (ex: move(distance, front) )
    // perso je préfère cette dernière option, c'est plus clair 

    // On prend la valeur de distance en mm et on la converti en pas 
    int N{}; 
    bool negatif{false}; 
    if (x<0){ 
      negatif = true; 
      x = -x; 
    }
    N = convert_dist_pas(x);
    if (negatif){
      N = -N; 
    }
    moteur_G.move(N); 
    moteur_D.move(-N);
    int distance_left{10}; 
    while (distance_left != 0){
      moteur_G.run();
      moteur_D.run();
      distance_left = moteur_D.distanceToGo(); 
    }
}

void turn(int theta){
    // Fonction permettant de tourner sur place
    moteur_G.move(10000); 
    moteur_D.move(10000); 
    int distance_left{10}; 
    while (distance_left != 0){
      moteur_G.run();
      moteur_D.run();
      distance_left = moteur_D.distanceToGo(); 
    }
}