#include <Stepper.h>

// Pins definieren
#define TRIG_PIN 7  // Trig Pin für Ultraschallsensor
#define ECHO_PIN 6  // Echo Pin für Ultraschallsensor
#define LED_PIN 13  // Pin für LED
#define STEPS_PER_REV 200  // Schritte pro Umdrehung für den spezifischen Schrittmotor

// Stepper-Objekt erstellen. Pin 8, 9, 10 und 11 am Arduino sind mit den Eingangspins am L293DNE verbunden
Stepper stepper(STEPS_PER_REV, 8, 9, 10, 11); 

bool ledStatus = false;
bool motorStatus = false;

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
  
  // Distanz berechnen
  float distance = (duration/2) / 29.1;

  // Überprüfen, ob ein Objekt innerhalb von 11 cm ist
  if (distance < 11 && ledStatus == false) {
    digitalWrite(LED_PIN, HIGH);
    ledStatus = true;
    Serial.println("Objekt erkannt, Entfernung weniger als 11cm!");
    if (!motorStatus) {
      stepper.step(STEPS_PER_REV/2);
      motorStatus = true;
    }
  } else if(distance >= 11 && ledStatus == true){
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    Serial.println("Kein Objekt innerhalb von 11cm erkannt.");
    if (motorStatus) {
      stepper.step(-STEPS_PER_REV/2);
      motorStatus = false;
    }
  }

  delay(100);
}
