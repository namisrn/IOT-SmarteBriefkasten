#include <WiFiNINA.h>

#define TRIGGER_PIN 2 // Trigger-Pin des Ultraschallsensors
#define ECHO_PIN 4 // Echo-Pin des Ultraschallsensors
#define LED_PIN 7 // Definiert den Pin für die LED
#define INTERVAL 1000 // Intervall für die Entfernungsmessung
#define MAX_TRIES 5 // Maximale Anzahl von Verbindungsversuchen

const char* ssid = "PS";
const char* password = "+PaSa_(8991)+";
const char* HOST = "192.168.178.114"; // Ersetzen Sie 192.168.X.X durch die tatsächliche IP-Adresse des Empfänger-Arduinos
const uint16_t PORT = 80;

bool objectDetected = false; // Variable, die den Zustand des Detektors speichert
unsigned long previousMillis = 0; // Variablen für die Verzögerung mit millis()

void setup() {
  Serial.begin(9600); // Startet die serielle Kommunikation
  
  pinMode(TRIGGER_PIN, OUTPUT); // Definiert TRIGGER_PIN als Ausgang
  digitalWrite(TRIGGER_PIN, LOW); // Setzt den TRIGGER_PIN auf LOW
  pinMode(ECHO_PIN, INPUT); // Definiert ECHO_PIN als Eingang

  int tries = 0;
  while(WiFi.status() != WL_CONNECTED && tries < MAX_TRIES) {
    connectToWiFi(); // Verbindet mit WiFi
    tries++;
  }

  pinMode(LED_PIN, OUTPUT); // Setzt den LED-Pin als Ausgang
}

void loop() {
  unsigned long currentMillis = millis(); // Aktuelle Zeit
  if(currentMillis - previousMillis >= INTERVAL) { // Prüft, ob das Intervall vergangen ist
    previousMillis = currentMillis; // Aktualisiert die Zeit
    objectDetection(); // Führt die Objekterkennung durch
  }
}

void objectDetection() {
  long duration, distanceCm;

  // Sendet einen Ultraschallimpuls
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Misst die Zeit, die der Ultraschallimpuls benötigt, um zurückzukommen
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Umwandlung der gemessenen Zeit in eine Entfernung in cm
  distanceCm = duration * 0.034/2;
  
  // Wenn ein Objekt erkannt wird und zuvor kein Objekt erkannt wurde, sendet ein Signal an den Empfänger
  if (distanceCm < 15 && !objectDetected) {
    digitalWrite(LED_PIN, HIGH); // Schaltet die LED ein
    sendSignalToReceiver();
    objectDetected = true; // Aktualisiert den Zustand auf 'Objekt erkannt'
  } 
  else if (distanceCm >= 15 && objectDetected) {
    digitalWrite(LED_PIN, LOW); // Schaltet die LED aus
    sendSignalToReceiver();
    objectDetected = false; // Aktualisiert den Zustand auf 'Kein Objekt erkannt'
  }
}

// Verbindet das Gerät mit dem WiFi
void connectToWiFi() {
  int status = WL_IDLE_STATUS; // Beginnt mit dem Status 'Untätig'
  Serial.print("Verbindungsversuch mit WLAN-Netzwerk: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, password); // Versucht, eine Verbindung mit dem WiFi herzustellen
  if(status == WL_CONNECTED) {
    Serial.println("Mit WLAN-Netzwerk verbunden."); // Gibt eine Meldung aus, wenn die Verbindung hergestellt wurde
    blinkLED(2); // Blinkt die LED zweimal schnell
  } else {
    Serial.println("Verbindung zum WLAN-Netzwerk fehlgeschlagen."); // Gibt eine Meldung aus, wenn die Verbindung fehlgeschlagen ist
  }

}

// Sendet ein Signal an den Empfänger
void sendSignalToReceiver() {
  WiFiClient client;
  if (client.connect(HOST, PORT)) {
    client.println("POST / HTTP/1.1");
    client.println((String)"Host: " + HOST);
    client.println("Content-Type: text/plain");
    client.println("Content-Length: 6"); // Die Länge der Nachricht
    client.println(); // Leere Zeile, um Header und Body der Anforderung zu trennen
    client.println("object"); // Die Nachricht
    client.stop(); // Beendet die Verbindung zum Server
    Serial.println("Signal gesendet!"); // Gibt eine Meldung aus, wenn das Signal gesendet wurde
  } else {
    Serial.println("Verbindung zum Empfänger fehlgeschlagen."); // Gibt eine Fehlermeldung aus, wenn die Verbindung zum Empfänger fehlgeschlagen ist
    blinkLED(4); // Blinkt die LED viermal
  }

}

void blinkLED(int times) {
  for(int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(250); // LED bleibt für 250 ms an
    digitalWrite(LED_PIN, LOW);
    delay(250); // LED bleibt für 250 ms aus
  }
}

