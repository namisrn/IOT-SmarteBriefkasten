# MailMate 
Ubiquitous Computing - Projektbericht. (Update: 06.07.2023)

## Einführung
Das Ziel dieses Projekts ist die Entwicklung eines intelligenten Briefkasten-Benachrichtigungssystems. Dieses System soll in der Lage sein, die Präsenz eines neuen Briefs oder Pakets in einem Briefkasten automatisch zu erkennen und den Benutzer entsprechend zu benachrichtigen. Angesichts der Herausforderungen, die sich aus der immerwährenden Prüfung unseres Briefkastens ergeben, schien die Entwicklung eines intelligenten Briefkasten-Benachrichtigungssystems eine geeignete und interessante Aufgabe zu sein.

## Problemstellung: 
Obwohl viele von uns in Mehrfamilienhäusern leben oder unser Briefkasten weit von unserem Wohnraum entfernt ist, bleibt das Überprüfen des Briefkastens auf Post eine lästige Aufgabe. Es wäre effizienter, eine Benachrichtigung zu erhalten, sobald die Post eingeworfen wird, damit wir nicht unnötig zum Briefkasten gehen müssen.

## Lösungsansatz: 
Um dieses Problem zu lösen, wurde ein System entwickelt, das aus einem Sensor- und einem Aktor-Modul besteht. Der Ultraschallsensor erkennt, wenn ein Objekt (z.B. ein Brief) in den Briefkasten geworfen wird, und sendet ein Signal an das Aktor-Modul. Das Aktor-Modul gibt dann eine visuelle und physische Reaktion: es leuchtet eine LED auf und der Servomotor/Stepper-Motor dreht sich. Diese Aktionen signalisieren dem Benutzer, dass Post eingeworfen wurde.

## Systemübersicht: 
Das System bzw. die Gründsätzliche Idee besteht aus zwei Hauptkomponenten:

* Einem Sensor-Modul (Sender): Dieses Modul ist dafür verantwortlich, das Vorhandensein eines neuen Briefs oder Pakets in den Briefkasten zu erkennen. Und basiert auf folgenden Module:
  - einem Arduino Nano RP2040 Connect,
  - einer roten LED,
  - ein LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz),
  - einem HC-SR04 Ultraschallsensor.
 
* Einem Aktor-Modul (Empfänger): Dieses Modul ist dafür verantwortlich, den Benutzer Im Wohsitz zu benachrichtigen, wenn ein neuer Brief oder ein Paket erkannt wurde. Und basiert auf folgenden Module:
  - einem Arduino Nano RP2040 Connect,
  - einer roten LED,
  - ein LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz),
  - ein Motor-Treiber H-Bridge L293DNE,
  - einem Stepper-Mottor. 

Die Kommunikation zwischen den beiden Modulen erfolgt über die integrierten WiFi der Arduino-Platinen **oder** LoRaWAN-Module. Der Zustand jedes Moduls wird über die rote LED angezeigt, und die Bewegung des Schrittmotors signalisiert das Vorhandensein eines neuen Briefs oder Pakets.

## Systemdesign und Implementierung: 
Die Implementierung des Systems erfolgte in mehreren Phasen. 

  - In der ersten Phase wurde nur ein Modul, das auf Arduino-Platine , ein LED und USS basiert, entwickelt und getestet und der sollte in der Serial Monitor der Arduino IDE ausgeben, das ein objekt erkannt wurde, sobald das Objekt unter 15 cm liegt. Ebenfalls wird bei diesem Aktoin das LED an bzw. ausgeschaltet. Der Schwerpunkt  lag auf der Erkennung eines Objekts durch den Ultraschallsensor. Hierfür wurde zunächst ein Testsystem aufgebaut, um verschiedene Entfernungen auszuprobieren. Es wurde festgestellt, dass ein Abstand von 15 cm am effektivsten war, um das Einlegen von Objekten in den Briefkasten zuverlässig zu erkennen.

![Screenshot von Arduino IDE Serial Monitor](/assets/Phase01.png)


  - Die zweite Phase des Projekts bestand darin, einen Servomotor hinzuzufügen. Der Motor wurde so programmiert, dass er sich dreht, wenn ein Objekt erkannt wurde, was als Signal für den Benutzer diente, dass ein neues Objekt in den Briefkasten eingeworfen wurde. 

    - [MailMate (Alte Version).ino](https://github.com/namisrn/MailMate/blob/main/MailMate%20(Alte%20Version).ino)
    - [Video zum Phase 02](https://youtu.be/ltNh2mRTkpc)


  - In der dritten Phase des Projekts wurden die Funktionen auf zwei separate Arduinos aufgeteilt, wobei einer als Sender (mit dem Ultraschallsensor) und der andere als Empfänger (mit dem Servomotor) fungierte. Dieser Schritt erforderte einige Anpassungen im Code, um sicherzustellen, dass die Kommunikation zwischen den beiden Geräten reibungslos funktionierte. Die Herausforderung bestand darin, sicherzustellen, dass die beiden Arduinos effektiv miteinander kommunizieren konnten. Nach einigen Recherchen wurde herausgefunden, dass die Eingabe der IP-Adresse des Empfängers in den Sendercode eine effektive Methode war, um eine stabile Verbindung herzustellen. Das Verbinden der beiden Geräte erforderte auch das Einrichten eines WiFi-Netzwerks, wobei das SSID und das Passwort manuell eingegeben wurden. Außerdem wurden ein rote LED zu beiden Arduinos hinzugefügt. Diese dienen als zusätzliche visuelle Indikatoren: Wenn der Sender ein Objekt erkennt, leuchtet seine LED auf, und wenn das Signal vom Empfänger empfangen wird, leuchtet dessen LED auch auf und der Servomotor dreht sich.

    - [MailMate-Sender(mit Wifi).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Sender(mit%20Wifi).ino)
    - [MailMate-Empfaenger(mit Wifi).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Empfaenger(mit%20Wifi).ino)
    - [Video zum Phase 03](https://youtu.be/s27I9-iAZ6E)

  - Die vierte Phase war die eigentlich durchbruch, weil die eingebauten WiFi für die kommunikation zwischen beiden Platinen wurde durch zwei LoRaWAN-Module ersetzt, damit sie in der größeren Abstaänden wie zum Beispiel von Haustür bis zum 2.Obergeschoß mit einander kommunizieren zu können. Außerdem  wurde servoMotor durch ein StepperMotor ersetzt, damit man die Drehung genauer programmieren kann. Servomotor könnte man nur bis zum 180 Grad drehen, aber bei dieser StepperMotor, die 200 Schritte bewegt, hat man meherere möglichkeiten beim Drehung und die Geschwendigkeit der Drehung. Dafür war auch ein 16-Pin Motor-Treiber nötig. Außerdem war auch eine 12V externe Stromquelle nötwendig. Das war die schwiegigste teil des Projekt und ich habe verschied Try&Fail durch gemacht und viele recherche gemacht. Das Problem bestand darin, dass das System nicht Stabil-gebung funktioniert hat. Manchmal  die Kommunikation zwischen beiden Platine und die Drehung des Motors reibungslos funktioniert und manchmal gar nicht,ohne das was zu ändern.  Durch mehere male iteration und neu Anfang hatte ich keine passende lösung gefunden. Am Ende habe ich leider Ausversehen einen Falschen PIN asugewähl und es hat dazu gefürt, das wenn ich die 12V externen Stromquelle an die Platin angeschloßen habe, wurde die Platine und Motor-Treiber gegrillt. und stieg rauch auch und die Leitung bisschen schmelz abbekommen.

    - [Video zum Phase 04](https://youtu.be/A9KNEbSvioM)

  - In der fünfte Phase wegen das was vorhin passiert ist,musste ich das Projekt deutlich zu reduzieren.
    
    - [Video zum Phase 05](https://youtu.be/JOyV6MIt7ds)

## Schaltpläne
Hier ist die Schaltpläne zu der Phase 04:

  - ![Phase04_Sender Schaltplan](/assets/Phase04_Sender.png)
  - ![Phase04_Empfänger Schaltplan](/assets/Phase04_Empfaenger.png)

## Ergebnisse und Diskussion: 
Obwohl das System grundsätzlich funktioniert, gab es einige Herausforderungen und Verbesserungsmöglichkeiten. Eines der Hauptprobleme war die Stabilität der WiFi-Verbindung, die besonders bei größeren Entfernungen ein Problem darstellte. Eine Möglichkeit, dieses Problem zu lösen, könnte die Verwendung von LoRaWAN-Modulen anstelle der WiFi-Kommunikation sein.

- Darüber hinaus könnte ein “Stepper Motor” anstelle des Servomotors für mehr Flexibilität in der Bewegung und genauerer Kontrolle eingesetzt werden.

- Trotz dieser Herausforderungen war das Projekt ein Erfolg und hat gezeigt, wie IoT-Technologien zur Lösung alltäglicher Probleme beitragen können. Es bot eine wertvolle Lernerfahrung und eröffnete Möglichkeiten für zukünftige Projekte und Verbesserungen.
