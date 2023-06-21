#include <Servo.h> // Die Servo-Bibliothek wird inkludiert, die zur Steuerung des Servomotors benötigt wird.

#define TRIG_PIN 2 // Der Pin für das Trig-Signal des Ultraschallsensors wird definiert.
#define ECHO_PIN 4 // Der Pin für das Echo-Signal des Ultraschallsensors wird definiert.

Servo servoMotor; // Ein Servo-Objekt wird erstellt, das zur Steuerung des Servomotors verwendet wird.

bool isServoTurned = false; // Eine boolesche Variable wird initialisiert, die speichert, ob der Servomotor gedreht wurde. Der Anfangswert ist 'false'.

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Der Trig-Pin wird als Ausgang festgelegt.
  pinMode(ECHO_PIN, INPUT); // Der Echo-Pin wird als Eingang festgelegt.
  Serial.begin(9600); // Die serielle Kommunikation wird mit einer Baudrate von 9600 begonnen.
  
  servoMotor.attach(9); // Das Servo-Objekt wird mit dem Pin verbunden, an den der Servomotor angeschlossen ist. In diesem Fall ist das Pin 9.
}

void loop() {
  digitalWrite(TRIG_PIN, LOW); // Das Trig-Signal wird zunächst auf LOW gesetzt.
  delayMicroseconds(2); // Es wird 2 Mikrosekunden gewartet.
  digitalWrite(TRIG_PIN, HIGH); // Das Trig-Signal wird auf HIGH gesetzt...
  delayMicroseconds(10); // ...für 10 Mikrosekunden auf HIGH gehalten...
  digitalWrite(TRIG_PIN, LOW); // ...und dann wieder auf LOW gesetzt. Das sendet den Ultraschallimpuls aus.
  
  long duration = pulseIn(ECHO_PIN, HIGH); // Die Dauer, wie lange das Echo-Signal HIGH ist, wird gemessen. Das ist die Zeit, die der Ultraschallimpuls für die Hin- und Rückreise benötigt.
  
  int distance = (duration/2) / 29.1; // Die Entfernung in cm wird berechnet. Die Dauer wird durch 2 geteilt (weil die Zeit für Hin- und Rückreise gemessen wurde) und dann durch 29.1 geteilt, um die Einheit in Zentimeter zu konvertieren.
  
  Serial.print("Entfernung: "); // "Entfernung: " wird ausgegeben...
  Serial.print(distance); // ...gefolgt von der gemessenen Entfernung...
  Serial.println(" cm"); // ...und " cm" am Ende, um anzugeben, dass die Entfernung in Zentimetern ist.

  // Wenn die gemessene Entfernung kleiner als 30 cm ist und der Servomotor noch nicht gedreht wurde, wird der Servomotor gedreht.
  if (distance < 15 && !isServoTurned) {
    servoMotor.write(180); // Der Servomotor wird um 180 Grad gedreht.
    isServoTurned = true; // Die Variable 'isServoTurned' wird auf true gesetzt, da der Servomotor nun gedreht ist.
    delay(1000); // Es wird eine Sekunde gewartet, um sicherzustellen, dass der Servomotor genügend Zeit zum Drehen hat.
  }
  
  // Wenn die gemessene Entfernung größer oder gleich 22 cm ist und der Servomotor bereits gedreht wurde, wird er zurück auf 0 Grad gedreht.
  if (distance >= 15 && isServoTurned) {
    servoMotor.write(0); // Der Servomotor wird auf 0 Grad zurückgedreht.
    isServoTurned = false; // Die Variable 'isServoTurned' wird auf false gesetzt, da der Servomotor nun nicht mehr gedreht ist.
    delay(1000); // Es wird eine Sekunde gewartet, um sicherzustellen, dass der Servomotor genügend Zeit zum Drehen hat.
  }
  
  delay(500); // Es wird eine Sekunde gewartet, bevor die Schleife erneut gestartet wird.
}
