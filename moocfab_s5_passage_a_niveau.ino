/*  FUN MOOC "Fabrication Numérique" #MOOCFab
   ===========================================
    Licence : CCO 1.0 Universal
    Auteur : Guillaume ROUAN
    Date : mai 2014
   -------------------------------------------
    S5 : passage à niveau avec feux bicolores
*/



/*
Le fonctionnement normal est un feu allumé au rouge et une barrière fermée (0°).
Le fonctionnement normal est interrompu par l'appui sur un bouton poussoir.

Si l'appui du bouton est détecté, alors la barrière (actionnée par 
le servomoteur) se relève doucement. Lorsque la barrière est à 
la verticale (90°), le feu vert s'allume pendant 5 secondes pendant 
lesquelles la barrière reste ouverte (90°). Après les 5 secondes,
le feu repasse au rouge, la barrière redescend doucement et 
le fonctionnement normal reprend.

Aussi, nous souhaitons recevoir le message "Bouton appuye" dans 
le moniteur série lorsque l'appui a été détecté.
*/

#include <Servo.h>  // Librairie ServoMoteur
Servo barriere;     // ServoMoteur

#include <LiquidCrystal.h>  // Librairie écran LCD


const int vert = 2;      // LED verte
const int rouge = 3;     // LED rouge
const int PinBouton = 9; // Bouton
int EtatBouton = 0;      // Etat du bouton
int pos = 0;             // Position de la barrière = 0°

void setup () {
  // Barrière
  barriere.attach(13);
  // Feux bicolores
  pinMode (vert, OUTPUT);
  pinMode (rouge, OUTPUT);
  // Bouton
  pinMode (PinBouton, INPUT);
}

void loop () {
  
  // Feu rouge (état normal)
  digitalWrite (rouge, HIGH);
  
  EtatBouton = digitalRead (PinBouton); // Lecture de l'état du Bouton
  
  if (EtatBouton == HIGH) { // Bouton appuyé
    
    Serial.println("Bouton appuyé");
    
    // Ouverture de la barrière 
    for(pos = 90; pos>=0; pos--) {
      barriere.write(pos);
      delay(15);
    }
    
    // Feu vert pdt 5 sec
    digitalWrite (rouge, LOW);
    digitalWrite (vert, HIGH);
    delay(3000);
    
    // Feu rouge
    digitalWrite (vert, LOW);
    digitalWrite (rouge, HIGH);
    
    // Fermeture de la barrière
    for(pos = 0; pos <= 90; pos++) {
      barriere.write(pos);
      delay(15);
    }
    
  } // end IF

} // end LOOP

