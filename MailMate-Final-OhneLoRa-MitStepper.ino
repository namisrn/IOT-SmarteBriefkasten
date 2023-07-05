#include <Stepper.h>  // Bibliothek für die Steuerung von Schrittmotoren einbinden

// Pins definieren
#define TRIG_PIN 7  // Trig Pin für Ultraschallsensor
#define ECHO_PIN 6  // Echo Pin für Ultraschallsensor
#define LED_PIN 13  // Pin für LED
#define STEPS_PER_REV 200  // Schritte pro Umdrehung für den spezifischen Schrittmotor

// Stepper-Objekt erstellen. Pin 8, 9, 10 und 11 am Arduino sind mit den Eingangspins am L293DNE verbunden
Stepper stepper(STEPS_PER_REV, 8, 9, 10, 11); 

bool ledStatus = false; // Zustand der LED, standardmäßig ausgeschaltet
bool motorStatus = false; // Zustand des Motors, standardmäßig in der Ausgangsposition

void setup() {
  // Pins als Ausgang bzw. Eingang festlegen
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Serielle Kommunikation starten
  Serial.begin(9600);
  
  // Geschwindigkeit des Motors setzen
  stepper.setSpeed(120);  
}

void loop() {
  // Trigger-Impuls senden
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo-Laufzeit messen
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Distanz berechnen (Formel: distanz = (Laufzeit/2) / 29.1)
  float distance = (duration/2) / 29.1;

  // Überprüfen, ob ein Objekt innerhalb von 15 cm ist
  if (distance < 15 && ledStatus == false) {
    // LED einschalten
    digitalWrite(LED_PIN, HIGH);
    ledStatus = true;
    // Statusmeldung ausgeben
    Serial.println("Objekt erkannt, Entfernung weniger als 15cm!");
    // Motor drehen, wenn er noch nicht gedreht hat
    if (!motorStatus) {
      stepper.step(STEPS_PER_REV/2);  // Drehung um eine halbe Umdrehung
      motorStatus = true;
    }
  } else if(distance >= 15 && ledStatus == true){
    // LED ausschalten
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    // Statusmeldung ausgeben
    Serial.println("Kein Objekt innerhalb von 15cm erkannt.");
    // Motor zurückdrehen, wenn er gedreht hat
    if (motorStatus) {
      stepper.step(-STEPS_PER_REV/2);  // Drehung um eine halbe Umdrehung zurück
      motorStatus = false;
    }
  }

  // Verzögerung hinzufügen, um saubere Messungen zu gewährleisten
  delay(100);
}
