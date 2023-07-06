# MailMate 
Ubiquitous Computing - Projektbericht. (Update Stand: 17.06.2023)

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

  - In den zweite Phase wurde das System erweitert, in dem man , einem weiteren Arduino-Platine verwendet. Es wurde ein SensoModul (Sender) basiert auf Arduino-Platine, USS und LED und Aktor-Modul (Empfänger) basiert auf Arduino-Platine, ServoMotor und LED entwicklet, die mit intergriertem WiFi-Modul und WiFiNINA-Bibliothek miteinander kommuinizieren.


Der technische Kern des Systems besteht aus diese Hauptkomponenten: zwei Arduino Nano RP 2040 Boards, die jeweils mit einem HC-SR04 Ultraschallsensor und einem Servomotor ausgestattet sind. Für die Kommunikation zwischen den beiden Arduinos ist die integrierte WiFiNINA-Bibliothek verwendet worden, die eine einfache und effektive Möglichkeit bietet, WiFi-Kommunikation zu implementieren.

- In der ersten Phase des Projekts lag der Schwerpunkt auf der Erkennung eines Objekts durch den Ultraschallsensor. Hierfür wurde zunächst ein Testsystem aufgebaut, um verschiedene Entfernungen auszuprobieren. Es wurde festgestellt, dass ein Abstand von 15 cm am effektivsten war, um das Einlegen von Objekten in den Briefkasten zuverlässig zu erkennen.

- Um die Realität des Gebrauchs zu simulieren, wurde ein Prototyp aus Pappe erstellt, der als Briefkasten diente. Dieser Schritt war entscheidend, um die Effektivität und Zuverlässigkeit des Sensors in einer realistischeren Umgebung zu testen. Das Endprodukt war ein System, das in der Lage war, Objekte zuverlässig zu erkennen, wenn sie in den Briefkasten eingeworfen wurden.

- Die zweite Phase des Projekts bestand darin, einen Servomotor hinzuzufügen. Der Motor wurde so programmiert, dass er sich dreht, wenn ein Objekt erkannt wurde, was als Signal für den Benutzer diente, dass ein neues Objekt in den Briefkasten eingeworfen wurde.

- In der dritten Phase des Projekts wurden die Funktionen auf zwei separate Arduinos aufgeteilt, wobei einer als Sender (mit dem Ultraschallsensor) und der andere als Empfänger (mit dem Servomotor) fungierte. Dieser Schritt erforderte einige Anpassungen im Code, um sicherzustellen, dass die Kommunikation zwischen den beiden Geräten reibungslos funktionierte.

- Die Herausforderung bestand darin, sicherzustellen, dass die beiden Arduinos effektiv miteinander kommunizieren konnten. Nach einigen Recherchen wurde herausgefunden, dass die Eingabe der IP-Adresse des Empfängers in den Sendercode eine effektive Methode war, um eine stabile Verbindung herzustellen. Das Verbinden der beiden Geräte erforderte auch das Einrichten eines WiFi-Netzwerks, wobei das SSID und das Passwort manuell eingegeben wurden.

- In der vierten Phase wurden rote LEDs zu beiden Arduinos hinzugefügt. Diese dienen als zusätzliche visuelle Indikatoren: Wenn der Sender ein Objekt erkennt, leuchtet seine LED auf, und wenn das Signal vom Empfänger empfangen wird, leuchtet dessen LED auch auf und der Servomotor dreht sich.

- Durch diese iterativen Phasen der technischen Entwicklung und Optimierung konnte ich ein System schaffen, das nicht nur funktional, sondern auch intuitiv zu bedienen ist. Durch die Kombination von Sensortechnik, Mechanik und drahtloser Kommunikation konnte ich ein Produkt schaffen, das den Benutzer effektiv darüber informiert, wenn Post in den Briefkasten eingeworfen wird.

## Ergebnisse und Diskussion: 
Obwohl das System grundsätzlich funktioniert, gab es einige Herausforderungen und Verbesserungsmöglichkeiten. Eines der Hauptprobleme war die Stabilität der WiFi-Verbindung, die besonders bei größeren Entfernungen ein Problem darstellte. Eine Möglichkeit, dieses Problem zu lösen, könnte die Verwendung von LoRaWAN-Modulen anstelle der WiFi-Kommunikation sein.

- Darüber hinaus könnte ein “Stepper Motor” anstelle des Servomotors für mehr Flexibilität in der Bewegung und genauerer Kontrolle eingesetzt werden.

- Trotz dieser Herausforderungen war das Projekt ein Erfolg und hat gezeigt, wie IoT-Technologien zur Lösung alltäglicher Probleme beitragen können. Es bot eine wertvolle Lernerfahrung und eröffnete Möglichkeiten für zukünftige Projekte und Verbesserungen.
