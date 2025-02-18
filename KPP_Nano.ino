// Déclaration des broches
const int pinsMomentary[] = {2, 3, 4, 5, 6, 7, 8}; // Boutons momentanés
const int ledsMomentary[] = {A0, A1, A2, A3, A6}; // LEDs associées aux boutons 2 à 6

const int pinsLatch[] = {9, 11, 10, 12}; // Boutons latch
const int ledsLatch[] = {A4, A5, 13, A7}; // LEDs associées aux boutons latch

// Variables d'état des boutons
int lastStateMomentary[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};  
int lastStateLatch[4] = {HIGH, HIGH, HIGH, HIGH};  
int retainedStateLatch[4] = {LOW, LOW, LOW, LOW};  // État mémorisé des boutons latch
int activeLed = -1;  // Stocke la LED actuellement allumée

void setup() {
  Serial1.begin(9600);  // UART avec l'Arduino Micro Pro

  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(pinsMomentary[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 5; i++) {
    pinMode(ledsMomentary[i], OUTPUT);
    digitalWrite(ledsMomentary[i], HIGH); // Allume toutes les LEDs au démarrage pour test
  }

  for (int i = 0; i < 4; i++) {
    pinMode(pinsLatch[i], INPUT_PULLUP);
    pinMode(ledsLatch[i], OUTPUT);
    digitalWrite(ledsLatch[i], HIGH);  // LEDs latch éteintes au départ
  }

  delay(4000);  // Attendre 2 secondes pour voir si elles s’allument
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledsMomentary[i], LOW);
      // Puis les éteindre
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(ledsLatch[i], LOW);  // LEDs latch éteintes au départ
  }
}

void loop() {
  bool momentaryPressed = false;
  
  // 🔹 Gestion des boutons momentanés (D2 à D8)
  for (int i = 0; i < 5; i++) {  // Seuls les boutons 2 à 6 sont pris en compte
    int currentState = digitalRead(pinsMomentary[i]);

    if (currentState == LOW && lastStateMomentary[i] == HIGH) {  // Détection de l'appui
      momentaryPressed = true; // Un bouton momentary a été pressé
      if (activeLed != -1) {
        digitalWrite(ledsMomentary[activeLed], LOW);  // Éteint l'ancienne LED
      }
      digitalWrite(ledsMomentary[i], HIGH);  // Allume la nouvelle LED
      activeLed = i;  // Met à jour la LED active

      // Envoi du message via Serial1
      Serial1.print(pinsMomentary[i]);
      Serial1.print(";");
      Serial1.println(currentState);
    }

    lastStateMomentary[i] = currentState;
  }

  // 🔹 Gestion des boutons latch (D9 à D12)
  for (int i = 0; i < 4; i++) {
    int currentState = digitalRead(pinsLatch[i]);

    // Détection du relâchement du bouton (passage LOW → HIGH)
    if (currentState == HIGH && lastStateLatch[i] == LOW) {
      retainedStateLatch[i] = !retainedStateLatch[i];  // Inversion de l'état mémorisé
      digitalWrite(ledsLatch[i], retainedStateLatch[i]);  // Allume ou éteint la LED correspondante

      // Envoi du message via Serial1
      Serial1.print(pinsLatch[i]);
      Serial1.print(";");
      Serial1.println(retainedStateLatch[i]);
    }

    lastStateLatch[i] = currentState;  // Mise à jour de l'état précédent
  }

  // 🔹 Extinction des LEDs latch si un bouton momentary est pressé
  if (momentaryPressed) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledsLatch[i], LOW);
      retainedStateLatch[i] = LOW;
    }
  }

  delay(50);  // Petit délai pour éviter les rebonds excessifs
}
