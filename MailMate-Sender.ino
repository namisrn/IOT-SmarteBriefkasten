#include <WiFiNINA.h>

const char* ssid = "PS";
const char* password = "+PaSa_(8991)+";
const char* HOST = "192.168.178.114"; // Ersetzen Sie 192.168.X.X durch die tatsächliche IP-Adresse des Empfänger-Arduinos
const uint16_t PORT = 80;

#define TRIGGER_PIN 2 // Trigger-Pin des Ultraschallsensors
#define ECHO_PIN 4 // Echo-Pin des Ultraschallsensors

bool objectDetected = false; // Variable, die den Zustand des Detektors speichert

void setup() {
  Serial.begin(9600); // Startet die serielle Kommunikation
  
  pinMode(TRIGGER_PIN, OUTPUT); // Definiert TRIGGER_PIN als Ausgang
  digitalWrite(TRIGGER_PIN, LOW); // Setzt den TRIGGER_PIN auf LOW
  pinMode(ECHO_PIN, INPUT); // Definiert ECHO_PIN als Eingang

  connectToWiFi(); // Verbindet mit WiFi
}

void loop() {
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
    sendSignalToReceiver();
    objectDetected = true; // Aktualisiert den Zustand auf 'Objekt erkannt'
  } else if (distanceCm >= 15 && objectDetected) {
    // Wenn kein Objekt erkannt wird und zuvor ein Objekt erkannt wurde, sendet ein Signal an den Empfänger
    sendSignalToReceiver();
    objectDetected = false; // Aktualisiert den Zustand auf 'Kein Objekt erkannt'
  }

  delay(1000); // Wartet eine Sekunde vor dem nächsten Zyklus
}

// Verbindet das Gerät mit dem WiFi
void connectToWiFi() {
  int status = WL_IDLE_STATUS; // Beginnt mit dem Status 'Untätig'
  while (status != WL_CONNECTED) {
    Serial.print("Verbindungsversuch mit WLAN-Netzwerk: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password); // Versucht, eine Verbindung mit dem WiFi herzustellen
    delay(10000); // Wartet 10 Sekunden, bevor der nächste Verbindungsversuch unternommen wird
  }

  Serial.println("Mit WLAN-Netzwerk verbunden."); // Gibt eine Meldung aus, wenn die Verbindung hergestellt wurde
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
  }
}
