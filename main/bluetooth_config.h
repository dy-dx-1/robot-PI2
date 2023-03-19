// tutoriel: https://learn.adafruit.com/introducing-the-adafruit-bluefruit-le-uart-friend/wiring 

// Paramètres généraux de communication 
#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLE_READPACKET_TIMEOUT         500   // Timeout in ms waiting to read a response

// Paramètres du hardware 
#define BLUEFRUIT_HWSERIAL_NAME Serial1 
#define BLUEFRUIT_UART_MODE_PIN -1 // -1 pour signifier qu'il n'est pas utilisé 

// Paramètres du software
#define FACTORYRESET_ENABLE         1         // 1 pour effectuer un factory reset, 0 pour ne pas le faire 
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

// Forward declaration de l'objet ble de type Adafruit_BluefruitLE_UART afin de définir les fonctions dans ce fichier 
extern Adafruit_BluefruitLE_UART ble; 
extern int distance_translation; 

// Fonction qui aide à afficher les erreurs 
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// Forward déclaration de fonctions définies dans packetparser.cpp 
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

void start_bluetooth_connection(){ 
  // Initialisation du module 
  Serial.println("Initialisation du module bluetooth"); 
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println("Initialisation complète");

  if ( FACTORYRESET_ENABLE )// Si on veut faire un factory reset
  {
    Serial.println(F("Factory reset demande"));
    if ( ! ble.factoryReset() ){error(F("Couldn't factory reset"));}
  }

  ble.echo(false); // Déactivation de la commande echo de bluefruit 
  ble.verbose(false);  // On n'a plus besoin d'info pour debug 

  // On en attente de la connection 
  Serial.println("En attente de connection"); 
  while (! ble.isConnected()) {
    delay(500);
  }
  Serial.println("Connection complete!"); 
  Serial.println("******************************");

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println("Mode choisi pour le LED indicateur: " MODE_LED_BEHAVIOUR);
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set Bluefruit to DATA mode
  Serial.println("Changement en mode DATA");
  ble.setMode(BLUEFRUIT_MODE_DATA);
  Serial.println("******************************");
}

int listen_for_codes(){
  /* Wait for new data to arrive */
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return 0; // retour de 0 si on trouve rien 

  // Boutons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    int button_return = buttnum;  // le numéro du bouton qui sera retourné 
    //Serial.print ("Button "); Serial.print(buttnum);
    if (pressed) {
      //Serial.println(" pressed");
      button_return = button_return + 10; // si un bouton est appuyé, on reçoit la valeur du bouton + 10 
    } else {
      //Serial.println(" released");
    }
    return button_return; 
  }

  // Couleur
  if (packetbuffer[1] == 'C') {
    Serial.println("Couleur reçue");
    distance_translation = 50;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
  // Location GPS
  if (packetbuffer[1] == 'L') {
    Serial.println("Coordonnée gps reçue.");
    distance_translation = 1000;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
  // Accelerometre
  if (packetbuffer[1] == 'A') {
    Serial.println("Donnée d'accélèromètre reçue");
    distance_translation = 400;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
  // Magnetometre
  if (packetbuffer[1] == 'M') {
    Serial.println("Donnée du magnétomètre reçue");
    distance_translation = 800;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
  // Gyroscope
  if (packetbuffer[1] == 'G') {
    Serial.println("Gyroscope");
    distance_translation = 600;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
  // Quaternions
  if (packetbuffer[1] == 'Q') {
    Serial.println("Quaternion reçu");
    distance_translation = 200;
    Serial.print("Nouvelle valeur en translation: "); Serial.print(distance_translation); Serial.println(" mm"); 
    }
}