#include <Stepper.h>
#include <LoRa.h>

#define STEPS_PER_REV 200
#define LED_PIN 8

Stepper stepper(STEPS_PER_REV, 4, 5, 7, 9); 
float lastDistance = 0.0; // Letzte empfangene Distanz
bool motorStatus = false; // Zustand des Motors, standardmäßig in der Ausgangsposition

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  stepper.setSpeed(60);

  if (!initLoRa()) {
    Serial.println("LoRa initialisation failed.");
    blinkLED();
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    float distance = LoRa.parseFloat();
    if (distance != lastDistance) {
      handleDistanceChange(distance);
      lastDistance = distance;
    }
  }
  delay(100);
}

bool initLoRa() {
  if (!LoRa.begin(433E6)) {
    return false;
  }
  return true;
}

void handleDistanceChange(float distance) {
  if (distance < 15 && !motorStatus) {
    digitalWrite(LED_PIN, HIGH);
    stepper.step(STEPS_PER_REV);
    motorStatus = true;
    Serial.println("Objekt erkannt, Entfernung weniger als 15cm!");
  } else if(distance >= 15 && motorStatus) {
    digitalWrite(LED_PIN, LOW);
    stepper.step(-STEPS_PER_REV);
    motorStatus = false;
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
