#include <WiFiNINA.h>
#include <Servo.h>
#define LED_PIN 8 // Definiert den Pin für die LED

const char* ssid = "PS";
const char* password = "+PaSa_(8991)+";

WiFiServer server(80); // Startet einen HTTP-Server auf Port 80

Servo servoMotor; // Erstellt ein Servo-Objekt
bool servoState = false; // Variable, die den Zustand des Servos speichert

void setup() {
  servoMotor.attach(9); // Befestigt den Servo an Pin 9
  Serial.begin(9600); // Startet die serielle Kommunikation


  connectToWiFi(); // Verbindet mit WiFi
  server.begin(); // Startet den Server
  Serial.println("Server gestartet."); // Gibt eine Meldung aus, wenn der Server gestartet wurde
  Serial.print("IP-Adresse: "); 
  Serial.println(WiFi.localIP()); // Gibt die IP-Adresse des Servers aus
  pinMode(LED_PIN, OUTPUT); // Setzt den LED-Pin als Ausgang

}

void loop() {
  WiFiClient client = server.available(); // Prüft, ob ein Client eine Verbindung hergestellt hat

  if (client) { // Wenn ein Client verbunden ist
    String currentLine = ""; // Speichert die aktuelle Zeile der Anforderung
    while (client.connected()) { // Solange der Client verbunden ist
      if (client.available()) { // Wenn Daten verfügbar sind
        char c = client.read(); // Liest das nächste Zeichen
        Serial.write(c); // Zeigt das gelesene Zeichen an
        if (c == '\n') { // Wenn das Ende einer Zeile erreicht ist
          if (currentLine.length() == 0) { // Wenn das Ende der Anforderung erreicht ist
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close"); // Schließt die Verbindung nach dem Senden der Antwort
            client.println(); // Leere Zeile, um Header und Body der Antwort zu trennen
            client.stop(); // Beendet die Verbindung zum Client
            currentLine = ""; // Setzt die aktuelle Zeile zurück
          } else if (currentLine.indexOf("POST") >= 0) { // Wenn es sich um eine POST-Anforderung handelt
            // Wechselt den Zustand des Servos
            if (!servoState) {
              digitalWrite(LED_PIN, HIGH); // Schaltet die LED ein
              servoMotor.write(180); // Dreht den Servo auf 180 Grad
              servoState = true; // Aktualisiert den Zustand auf 'gedreht'
            } else {
              digitalWrite(LED_PIN, LOW); // Schaltet die LED aus
              servoMotor.write(0); // Dreht den Servo auf 0 Grad
              servoState = false; // Aktualisiert den Zustand auf 'nicht gedreht'
            }
            currentLine = ""; // Setzt die aktuelle Zeile zurück
          } else {
            currentLine = ""; // Setzt die aktuelle Zeile zurück, wenn es sich nicht um eine POST-Anforderung handelt
          }
        } else if (c != '\r') { // Wenn es sich nicht um ein Wagenrücklaufzeichen handelt
          currentLine += c; // Fügt das Zeichen zur aktuellen Zeile hinzu
        }
      }
    }
    delay(1); // Wartet kurz, bevor der nächste Zyklus beginnt
    client.stop(); // Beendet die Verbindung zum Client
  }
}

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
