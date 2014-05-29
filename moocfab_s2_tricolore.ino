/*  FUN MOOC "Fabrication Numérique" #MOOCFab
   ===========================================
    Licence : CCO 1.0 Universal
    Auteur : Guillaume ROUAN
    Date : mai 2014
   -------------------------------------------
    S2 : feux tricolores clignotants
*/

// LED
int vert = 10;
int orange = 12;
int rouge = 13;

void setup () {
  pinMode (vert, OUTPUT);
  pinMode (orange, OUTPUT);
  pinMode (rouge, OUTPUT);
}

void loop () {
  /* Orange pdt 1 sec */
  digitalWrite (orange, HIGH);
  delay(1000);
  digitalWrite (orange, LOW);
  
  /* Rouge pdt 3 sec */
  digitalWrite (rouge, HIGH);
  delay(3000);
  digitalWrite (rouge, LOW);
  
  /* Vert pdt 3 sec */
  digitalWrite (vert, HIGH);
  delay(3000);
  digitalWrite (vert, LOW);
  
}

