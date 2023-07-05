#include <LoRa.h>

#define TRIG_PIN 7
#define ECHO_PIN 6
#define LED_PIN 3
#define LORA_SS_PIN 10
#define LORA_DIO0_PIN 2

float lastDistance = 0.0; // Letzte gemessene Distanz
bool ledStatus = false; // Zustand der LED, standardmäßig ausgeschaltet

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  if (!initLoRa()) {
    Serial.println("LoRa initialisation failed.");
    blinkLED();
  }
}

void loop() {
  // Trigger Impuls senden
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo lesen
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Distanz berechnen (nach Formel: distanz = (Laufzeit/2) / 29.1)
  float distance = (duration/2) / 29.1;

  if (distance != lastDistance) {
    handleDistanceChange(distance);
    lastDistance = distance;
  }

  // Sende die Distanz über LoRa
  LoRa.beginPacket();
  LoRa.print(distance);
  LoRa.endPacket();

  delay(1000);
}

bool initLoRa() {
  if (!LoRa.begin(433E6)) {
    return false;
  }
  return true;
}

void handleDistanceChange(float distance) {
  if (distance < 15 && ledStatus == false) {
    digitalWrite(LED_PIN, HIGH);
    ledStatus = true;
    Serial.println("Objekt erkannt, Entfernung weniger als 15cm!");
  } else if(distance >= 15 && ledStatus == true){
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    Serial.println("Kein Objekt innerhalb von 15cm erkannt.");
  }
}

void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}
