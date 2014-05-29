/*  FUN MOOC "Fabrication Numérique" #MOOCFab
   ===========================================
    Licence : CCO 1.0 Universal
    Auteur : Guillaume ROUAN
    Date : mai 2014
   -------------------------------------------
    S4 : Thérémine lumineux
*/

/*
  Entrée et sortie analogiques + communications série
 
 Ce programme va allumer une LED branchée sur la broche 9.
 L'intensité lumineuse de la LED sera proportielle à la luminosité
 captée par la photorésistance branchée sur la broche A0.
 
 */

/*
    L'exercice consiste à modifier l'exemple AnalogInOutSerial vu cette semaine et l'adapter pour que 
    la luminosité mesurée par la photorésistance soit proportionelle à la fréquence jouée un buzzer 
    branché sur la broche 8 : plus la luminosité reçue par la photorésistance est importante, 
    plus la fréquence jouée par le buzzer sera élevée (et inversement, si on passe notre main 
    devant le capteur de luminosité alors le son émis sera grave→fréquence basse).
    
    Vous aurez besoin de la fonction tone qui prend deux paramètres :
        la broche où le buzzer est branché
        la fréquence que l'on veut jouer avec le buzzer (exprimée en Hertz)

tone(8, 440);  // la note La (440Hz) jouée sur un buzzer branché sur la broche 8

    Lorsque l'on reçoit beaucoup de lumière sur notre photo-résistance, la fréquence générée devra être proche de 3000Hz 
    et lorsque la lumière est faible, la fréquence devra être proche de 50Hz.
    Le buzzer doit avoir une patte connectée à la broche 8 et l'autre au GND

*/

// Initialisation des constantes :
const int photoResistance = A0;   // Numéro de la broche à laquelle est connecté la photorésistance
const int buzzer = 8;   // Numéro de la broche à laquelle est connectée le buzzer
const int LED = 9;      // Numéro de la broche à laquelle est connectée la LED

int sensorValue = 0;         // Valeur lue sur la photorésistance
int outputValueBuzzer = 0;   // Valeur envoyée au buzzer
int outputValueLED = 0;      // Valeur envoyée vers la LED

void setup() {
  // Initialise la communication avec l'ordinateur
  Serial.begin(9600);
  
  // Indique l'entrée :
  pinMode (photoResistance, INPUT);
  // Indique les sorties :
  pinMode (buzzer, OUTPUT);
  pinMode (LED, OUTPUT);  
}

void loop() {
  // lit la valeur de la photorésistance et
  // stocke le résultat dans sensorValue :
  sensorValue = analogRead(photoResistance);            
  // change sensorValue vers une intervalles :
  outputValueBuzzer = map(sensorValue, 0, 1023, 50, 3000);  // 50Hz à 3000Hz
  outputValueLED = map(sensorValue, 0, 1023, 0, 255);  // 0 à 255
  // envoie de cette nouvelle valeur sur le buzzer
  tone (buzzer, outputValueBuzzer);
  analogWrite (LED, outputValueLED);
  
  delay (10);

  // envoie tout ça vers l'ordinateur
  Serial.print("PhotoResistance = " );                       
  Serial.print(sensorValue);      
  Serial.print(" / Buzzer = ");      
  Serial.println(outputValueBuzzer);
  Serial.print(" / LED = ");      
  Serial.println(outputValueLED);
  Serial.print("\n");
}
