/*  FUN MOOC "Fabrication Numérique" #MOOCFab
   ===========================================
    Licence : CCO 1.0 Universal
    Auteur : Guillaume ROUAN
    Date : mai 2014
   -------------------------------------------
    S9 : passage à niveau avec feux bicolores + écran LCD
*/

/*
Le fonctionnement normal est un feu allumé au rouge, une barrière fermée (0°) 
et un afficheur LCD qui affiche sur la première ligne "Voiture numero:" puis 
sur la seconde ligne le nombre de fois où le bouton a été appuyé depuis 
le démarrage de l'Arduino. Le fonctionnement normal est interrompu par 
l'appui sur un bouton poussoir.

Si l'appui du bouton est détecté, alors la barrière (actionnée par le servomoteur) 
se relève doucement. Lorsque la barrière est à la verticale (90°), le feu vert 
s'allume pendant 5 secondes pendant lesquelles la barrière reste ouverte (90°). 
Après les 5 secondes, le feu repasse au rouge, la barrière redescend doucement 
et on vient ajouter un au compteur affiché sur la seconde ligne de l'écran LCD.
Enfin, le fonctionnement normal reprend.

Impératif : Votre code devra contenir une fonction appellée mouvementBarriere
prenant deux paramètres : la position de départ et la position d'arrivée. 
Cette fonction devra être capable de lever ou baisser la barrière en fonction 
de la valeur de ces paramètres.

Aussi, nous souhaitons recevoir le message "Voiture numero:" suivi du nombre
d'appuis sur le bouton dans le moniteur série lorsque l'appui a été détecté.
*/

#include <Servo.h>  // Librairie ServoMoteur
Servo barriere;     // ServoMoteur

#include <LiquidCrystal.h>  // Librairie écran LCD
#include <Wire.h>
#include <LCD.h>
#define LCD_rs 2            // Brochage LCD
#define LCD_enable 3
#define LCD_d4 4
#define LCD_d5 5
#define LCD_d6 6
#define LCD_d7 7
#define LCD_LIGHT_PIN A4 // backlight
LiquidCrystal lcd(LCD_rs, LCD_enable, LCD_d4, LCD_d5, LCD_d6, LCD_d7);  // Ecran LCD

const int vert       = 11;  // LED verte
const int rouge      = 12;  // LED rouge
const int PinBouton  = 9;  // Bouton
int EtatBouton       = 0;  // Etat du bouton
int pos              = 0;  // Position de la barrière = 0°
int voiture          = 0;  // Numéro de la voiture (nombre de clics bouton / levées de barrière)

void setup () {
  Serial.begin(9600); // initialise la communication avec l'ordinateur
  // Barrière
  barriere.attach(13);
  // Feux bicolores
  pinMode (vert, OUTPUT);
  pinMode (rouge, OUTPUT);
  // Bouton
  pinMode (PinBouton, INPUT);
}

// Fonction pour positionner la barrière
int mouvementBarriere (int posDepart, int posArrivee) {
   if (posDepart <= posArrivee) { // fermeture
     for (pos = posDepart; pos <= posArrivee; pos++) {
      barriere.write(pos);
      delay(15);
    }
   }
   else {  // ouverture
     for (pos = posDepart; pos >= posArrivee; pos--) {
       barriere.write(pos);
       delay(15);
     }
   }
}


void loop () {
  
  // Feu rouge (état normal)
  digitalWrite (rouge, HIGH);
  // Affichage LCD
  lcd.begin(16, 2);
  lcd.display();
  digitalWrite(LCD_LIGHT_PIN, HIGH);
  lcd.setCursor(0, 0);
  lcd.println("Voiture numero :");
  
  EtatBouton = digitalRead (PinBouton); // Lecture de l'état du Bouton
  
  if (EtatBouton == HIGH) { // Bouton appuyé
    
    voiture +=1;
    
    mouvementBarriere (90, 0); // Ouverture de la barrière 
    
    // Affichage moniteur série
    Serial.print("Voiture numero : ");
    Serial.println(voiture);
    
    // Affichage LCD
    lcd.setCursor(0, 1);
    lcd.print(voiture);                // Afficher le numéro de la voiture
    
    // Feu vert pdt 5 sec
    digitalWrite (rouge, LOW);
    digitalWrite (vert, HIGH);
    delay(3000);
    
    // Feu rouge
    digitalWrite (vert, LOW);
    digitalWrite (rouge, HIGH);
    
    mouvementBarriere (0, 90); // Fermeture de la barrière
    
  } // end IF

} // end LOOP

