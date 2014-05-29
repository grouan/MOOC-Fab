/*  FUN MOOC "Fabrication Numérique" #MOOCFab
   ===========================================
    Licence : CCO 1.0 Universal
    Auteur : Guillaume ROUAN
    Date : mai 2014
   -------------------------------------------
    S3 : feux tricolores + feux piétons
*/

// LED Voitures
const int V_vert = 10;
const int V_orange = 11;
const int V_rouge = 12;

// LED Piétons
const int P_vert = 8;
const int P_rouge = 9;

// Délais
const int tps_orange = 1000;     // 1 sec
const int tps_vert_rouge = 5000;       // 5 sec

// Bouton
const int PinBouton = 2;
int EtatBouton = 0;

void setup () {
  // Pin LED
  pinMode (V_vert, OUTPUT);
  pinMode (V_orange, OUTPUT);
  pinMode (V_rouge, OUTPUT);
  pinMode (P_vert, OUTPUT);
  pinMode (P_rouge, OUTPUT);
  // Pin Bouton
  pinMode (PinBouton, INPUT);
}

// Fonction pour le passage piétons
int passagePietons () {
  /* Voitures = Orange pdt 1 sec */
  digitalWrite (V_orange, HIGH); /*  Le feu tricolore passe au orange allumé pendant 1 seconde */
  delay(tps_orange);
  digitalWrite (V_orange, LOW);
  /* Rouge pdt 5 sec */
  digitalWrite (V_rouge, HIGH); /*  Le feu tricolore passe au rouge allumé pendant 5 secondes */
  digitalWrite (P_vert, HIGH); /*  Le feu piétons passe au vert allumé pendant 5 secondes */
  delay(tps_vert_rouge);
  digitalWrite (V_rouge, LOW);
  digitalWrite (P_vert, LOW);
}

void loop () {
  
  // ORANGE
  
    /* Voitures = Orange pdt 1 sec */
    digitalWrite (V_orange, HIGH);
    digitalWrite (P_rouge, HIGH);
    delay(tps_orange);
    digitalWrite (V_orange, LOW);
  
  // ROUGE
  
    /* Voitures = Rouge pdt 3 sec */
    digitalWrite (V_rouge, HIGH);
    digitalWrite (P_rouge, LOW);
    digitalWrite (P_vert, HIGH);
    delay(tps_vert_rouge);
    digitalWrite (V_rouge, LOW);
    digitalWrite (P_vert, LOW);
  
  // VERT
  
  EtatBouton = digitalRead (PinBouton); /* Lecture de l'état du Bouton */
  
  if (EtatBouton == HIGH) { /* Bouton appuyé => passage piétons */
    passagePietons();
  }
  else {
    /* Voitures = Vert pdt 3 sec */
    digitalWrite (V_vert, HIGH);
    digitalWrite (P_rouge, HIGH);
    delay(tps_vert_rouge);
    digitalWrite (V_vert, LOW);
  }
  
}

