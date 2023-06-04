#include <Servo.h> 

#define TRIG_PIN 2 // Definiere den Pin für das Trig-Signal des Ultraschallsensors.
#define ECHO_PIN 4 // Definiere den Pin für das Echo-Signal des Ultraschallsensors.

Servo servoMotor; // Erzeuge ein Servo-Objekt, das wir verwenden, um den Servomotor zu steuern.

bool isServoTurned = false; // Eine boolesche Variable, die speichert, ob der Servomotor gedreht wurde. Anfangs ist der Wert 'false'.()

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Den Trig-Pin als Ausgang setzen.
  pinMode(ECHO_PIN, INPUT); // Den Echo-Pin als Eingang setzen.
  Serial.begin(9600); 
  
  servoMotor.attach(9); // Das Servo-Objekt mit dem Pin 9 verbinden.
}

void loop() {
  digitalWrite(TRIG_PIN, LOW); // Das Trig-Signal zunächst auf LOW setzen
  delayMicroseconds(2); // Warte 2 Mikrosekunden.
  digitalWrite(TRIG_PIN, HIGH); // Setze das Trig-Signal auf HIGH...
  delayMicroseconds(10); // ...halte es für 10 Mikrosekunden auf HIGH...
  digitalWrite(TRIG_PIN, LOW); // ...und setze es dann wieder auf LOW. Das sendet den Ultraschallimpuls aus.
  
  long duration = pulseIn(ECHO_PIN, HIGH); // Messe die Dauer, wie lange das Echo-Signal HIGH ist. Das ist die Zeit, die der Ultraschallimpuls für die Hin- und Rückreise benötigt.
  
  float distance = (duration/2) / 29.1; // Berechne die Entfernung in cm. Wir teilen die Dauer durch 2 (weil die Zeit für Hin- und Rückreise gemessen wurde) und teilen dann durch 29.1 um die Einheit in Zentimeter zu konvertieren.
  
  Serial.print("Entfernung: "); // Gebe "Entfernung: " aus...
  Serial.print(distance); // ...gefolgt von der gemessenen Entfernung...
  Serial.println(" cm"); // ...und " cm" am Ende, um anzugeben, dass die Entfernung in Zentimeter ist.

  // Wenn die gemessene Entfernung kleiner als 30 cm ist und der Servo noch nicht gedreht wurde, drehen wir den Servomotor.
  if (distance < 24 && !isServoTurned) {
    servoMotor.write(180); // Drehen den Servomotor um 180 Grad.
    isServoTurned = true; // Setzen die Variable 'isServoTurned' auf true, da wir den Servomotor jetzt gedreht haben.
    delay(1000); // Warten eine Sekunde, um sicherzustellen, dass der Servomotor Zeit zum Drehen hat.
  }
  
  // Wenn die gemessene Entfernung größer oder gleich 30 cm ist und der Servomotor bereits gedreht wurde, drehen wir ihn zurück auf 0 Grad.
  if (distance >= 24 && isServoTurned) {
    servoMotor.write(0); // Drehen den Servomotor auf 0 Grad zurück.
    isServoTurned = false; // Setzen die Variable 'isServoTurned' zurück auf false, da der Servomotor nun nicht mehr gedreht ist.
    delay(1000); // Warten eine Sekunde, um sicherzustellen, dass der Servomotor Zeit zum Drehen hat.
  }
  
  delay(500); // Warten 0,5 Sekunden bevor wir die Schleife erneut starten.
}
