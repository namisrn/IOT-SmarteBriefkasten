# MailMate 
<sub> Ubiquitous Computing - Projektbericht - Sasan Rafat Nami - (Update: 07.07.2023) </sub>


## Einführung
Das Ziel dieses Projektes besteht darin, ein intelligentes Briefkastenbenachrichtigungssystem zu entwickeln. Dieses System soll in der Lage sein, die Anwesenheit eines neuen Briefes oder Pakets im Briefkasten automatisch zu erkennen und den Benutzer entsprechend zu benachrichtigen. Aufgrund der Herausforderungen, die sich aus der regelmäßigen Überprüfung unseres Briefkastens ergeben, stellte die Entwicklung eines solchen intelligenten Benachrichtigungssystems eine interessante und relevante Aufgabe dar.

## Problemstellung: 
Obwohl viele von uns in Mehrfamilienhäusern leben oder unser Briefkasten weit von unserem Wohnraum entfernt ist, bleibt das Überprüfen des Briefkastens auf Post eine lästige Aufgabe. Es wäre effizienter, eine Benachrichtigung zu erhalten, sobald die Post eingeworfen wird, damit wir nicht unnötig zum Briefkasten gehen müssen.

## Lösungsansatz: 
Um dieses Problem zu lösen, wurde ein System entwickelt, das aus einem Sensor- und einem Aktor-Modul besteht. Der Ultraschallsensor erkennt, wenn ein Objekt (z.B. ein Brief) in den Briefkasten geworfen wird, und sendet ein Signal an das Aktor-Modul. Das Aktor-Modul gibt dann eine visuelle und physische Reaktion: es leuchtet eine LED auf und der Servomotor/Stepper-Motor dreht sich. Diese Aktionen signalisieren dem Benutzer, dass Post eingeworfen wurde.

## Ursprügliche Idee + Skizze:

![Ursprügliche Idee](/assets/Idee.JPG)

* Das Sensor-Modul (Sender): Dieses Modul hat die Aufgabe, das Vorhandensein neuer Briefe oder Pakete im Briefkasten zu erkennen und diese Information weiterzuleiten. Es besteht aus folgenden Bauteilen:
  - Einem Arduino Nano RP2040 Connect als zentralem Steuerungsmodul,
  - Thermochromatischer Folie,
  - Einem LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz) zur drahtlosen Kommunikation,
  - Einem HC-SR04 Ultraschallsensor zur Objekterkennung,
  - Zwei hochpräzisen Wägezellen zur Gewichtsmessung,
  - Einem Hitzesensor zur Erzeugung von Temperaturveränderungen.

  Die Funktion des Sensor-Moduls ist es, eingeworfene Briefe oder Pakete sowohl durch den Ultraschallsensor als auch die Wägezellen zu erkennen. Die kombinierte Nutzung dieser beiden Sensoren reduziert die Wahrscheinlichkeit, dass eingeworfene Objekte nicht erkannt werden. Wenn ein Objekt erkannt wird, erhitzt der Hitzesensor die thermochromatische Folie, die eine Farbänderung auf der Vorderseite des Briefkastens bewirkt. Diese Farbänderung signalisiert dem Bewohner auf einen Blick, ob neue Post im Briefkasten ist oder nicht. Die Farbe könnte beispielsweise schwarz für einen leeren und rot für einen gefüllten Briefkasten sein. Darüber hinaus kann die Intensität der Farbe durch die Wägezellen beeinflusst werden - je schwerer das eingeworfene Paket ist, desto höher ist die vom Sensor erzeugte Temperatur, wodurch die Farbintensität verändert wird.

* Das Aktor-Modul (Empfänger): Dieses Modul ist dafür verantwortlich, den Bewohner im Haus darüber zu informieren, wenn neue Post erkannt wurde. Es besteht aus:
  - Einem Arduino Nano RP2040 Connect,
  - Einem LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz),
  - Einem Motortreiber H-Bridge L293DNE,
  - Einem Schrittmotor.

  Die Kommunikation zwischen den beiden Modulen erfolgt über die LoRaWAN-Module. Der Zustand des Moduls wird durch gerolltes Papier visualisiert. Die Bewegung des Schrittmotors zeigt das Vorhandensein neuer Post an. Wenn beispielsweise der Schrittmotor sich dreht, bedeutet dies, dass neuer Brief eingetroffen ist.


## Systemübersicht: 

Aufgrund von Zeitbeschränkungen musste das System vereinfacht und auf die folgenden Hauptmodule reduziert werden.

* Einem Sensor-Modul (Sender): Dieses Modul ist dafür verantwortlich, das Vorhandensein eines neuen Briefes oder Pakets im Briefkasten zu erkennen. Es setzt sich aus folgenden Bauteilen zusammen:
  - Einem Arduino Nano RP2040 Connect,
  - Einer roten LED,
  - Einem LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz),
  - Einem HC-SR04 Ultraschallsensor.
 
* Einem Aktor-Modul (Empfänger): Dieses Modul ist dafür verantwortlich, den Benutzer Im Wohsitz zu benachrichtigen, wenn ein neuer Brief oder ein Paket erkannt wurde. Und basiert auf folgenden Module:
  - Einem Arduino Nano RP2040 Connect,
  - Einer roten LED,
  - Einem LoRaWAN-Modul (LoRaWAN SX1278 LoRa 433MHz),
  - Einem Motor-Treiber H-Bridge L293DNE,
  - Einem Stepper-Mottor. 

Die Kommunikation zwischen den beiden Modulen erfolgt entweder über das eingebaute WLAN der Arduino-Platinen oder über die LoRaWAN-Module. Der Zustand jedes Moduls wird durch die rote LED signalisiert, während die Bewegung des Schrittmotors das Vorhandensein eines neuen Briefes oder Pakets anzeigt.

## Systemdesign und Implementierung: 
Die Implementierung des Systems erfolgte in mehreren Phasen. 

  - In der ersten Phase wurde nur ein Modul, das auf Arduino-Platine , ein LED und USS basiert, entwickelt und getestet und der sollte in der Serial Monitor der Arduino IDE ausgeben, das ein objekt erkannt wurde, sobald das Objekt unter bestimmte Abstand liegt. Dabei wurde festgestellt, dass ein Abstand von 15 cm am effektivsten war, um das Einlegen von Objekten in den Briefkasten zuverlässig zu erkennen. Zusätzlich wird bei dieser Aktion die LED ein- bzw. ausgeschaltet.

![Screenshot von Arduino IDE Serial Monitor](/assets/Phase01.png)


  - Die zweite Phase des Projekts bestand darin, einen Servomotor hinzuzufügen. Der Motor wurde so programmiert, dass er sich dreht, wenn ein Objekt erkannt wurde, was als Signal für den Benutzer diente, dass ein neues Objekt in den Briefkasten eingeworfen wurde. 

    - [MailMate (Alte Version).ino](https://github.com/namisrn/MailMate/blob/main/MailMate%20(Alte%20Version).ino)
    - [Video zu der Phase 02](https://youtu.be/ltNh2mRTkpc)


  - In der dritten Phase des Projekts wurden die Funktionen auf zwei separate Arduino-Platinen aufgeteilt. Eine fungiert als Sender (mit dem Ultraschallsensor), die andere als Empfänger (mit dem Servomotor). Dies erforderte einige Anpassungen im Code, um eine reibungslose Kommunikation zwischen den beiden Geräten durch intergrierten Wifi und WifiNINABibliothek zu gewährleisten. Die Herausforderung bestand darin, eine effektive Kommunikation zwischen den beiden Arduinos zu ermöglichen. Nach einigen Recherchen stellte sich heraus, dass die Eingabe der IP-Adresse des Empfängers in den Sendercode eine effektive Methode zur Herstellung einer stabilen Verbindung darstellte. Für die Verbindung der beiden Geräte war auch das Einrichten eines WLAN-Netzwerks notwendig, wobei die SSID und das Passwort manuell eingegeben wurden. Außerdem wurden rote LEDs zu beiden Arduinos hinzugefügt, die als zusätzliche visuelle Indikatoren dienen: Wenn der Sender ein Objekt erkennt, leuchtet seine LED auf. Empfängt der Empfänger das Signal, leuchtet dessen LED ebenfalls auf und der Servomotor dreht sich.

    - [MailMate-Sender(mit Wifi).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Sender(mit%20Wifi).ino)
    - [MailMate-Empfaenger(mit Wifi).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Empfaenger(mit%20Wifi).ino)
    - [Video zu der Phase 03](https://youtu.be/s27I9-iAZ6E)

  - In der vierten Phase des Projekts wurden die eingebauten WLAN-Komponenten durch zwei LoRaWAN-Module ersetzt, um eine Kommunikation zwischen beiden Platinen auch über größere Entfernungen (z.B. von der Haustür bis zum 2. Obergeschoss) zu ermöglichen.
    LoRaWAN (Long Range Wide Area Network) ist eine Netzwerkarchitektur, die speziell für das Internet der Dinge (IoT) entwickelt wurde. Es verwendet das LoRa (Long Range) Funkmodul, um eine Verbindung zwischen den Sensoren (Sender) und den Aktoren (Empfänger) herzustellen.

    Der Vorteil der Verwendung von LoRaWAN gegenüber dem eingebauten WLAN ist die größere Reichweite und die Fähigkeit, Gebäude und andere Hindernisse zu durchdringen, was es ideal für unser Szenario macht. Es erlaubt auch eine größere Anzahl von Geräten in seinem Netzwerk.

    Die Programmierung und Einrichtung der LoRaWAN-Module erforderte einen zusätzlichen Code, um die Kommunikation zu ermöglichen. Das Signal wird vom Sender-Modul gesendet, sobald ein Objekt vom Ultraschallsensor erkannt wird. Das Empfänger-Modul empfängt dann das Signal und führt die entsprechenden Aktionen aus.

    Außerdem wurde der Servomotor durch einen Schrittmotor ersetzt. Im Vergleich zum Servomotor, der nur eine begrenzte Drehbewegung ermöglicht, kann der Schrittmotor sich um 360 Grad drehen und bietet daher mehr Flexibilität in Bezug auf die Bewegung und Positionierung. Mit dem Einsatz des Schrittmotors konnte eine deutlich präzisere Steuerung der Drehbewegung erzielt werden.
Das Kernproblem bestand darin, dass das System nicht konstant stabil funktionierte. Es gab Zeiten, in denen die Kommunikation zwischen beiden Platinen und die Motorbewegung einwandfrei funktionierte, aber dann gab es auch Zeiten, in denen diese überhaupt nicht funktionierte - und das ohne irgendeine erkennbare Änderung.

    Trotz mehrfacher Iterationen und Versuche, das Problem von Grund auf neu zu lösen, konnte ich leider keine passende Lösung finden. Schließlich wählte ich versehentlich einen falschen PIN aus, was dazu führte, dass die Platine und der Motortreiber stark überhitzten, als ich die externe 12V-Stromquelle anschloss. Rauch begann aufzusteigen und die Leitungen nahmen leichten Schmelzschaden.

    - [MailMate-Sender(mit LoRaWAN).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Sender(mit%20LoRaWAN).ino)
    - [MailMate-Empfaenger(mit LoRaWAN)).ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Empfaenger(mit%20LoRaWAN).ino)
    - [Video zu der Phase 04](https://youtu.be/A9KNEbSvioM)

  - In der fünften Phase musste ich aufgrund der vorherigen Probleme das Projekt erheblich reduzieren. Um einen grundlegenden Prototyp darzustellen, der die zentrale Idee des Projekts veranschaulicht, verwendete ich ein Breadboard, um eine Arduino-Platine, einen Motortreiber, eine LED, einen Ultraschallsensor (USS) und einen Schrittmotor zu verbinden.

    Das Ziel dieser Phase war es, ein minimales, aber funktionierendes System zu schaffen. Mit den begrenzten Ressourcen und der verringerten Komplexität konnte ich mich auf die Grundfunktionen konzentrieren und eine stabile Basis für die Kommunikation und Interaktion zwischen den Komponenten herstellen.

    Die Arduino-Platine diente dabei als zentrale Einheit, die sowohl die Signale vom Ultraschallsensor verarbeitet als auch den Schrittmotor über den Motortreiber ansteuert. Der Ultraschallsensor erkennt ein Objekt in seiner Reichweite und sendet ein Signal an die Arduino-Platine. Diese verarbeitet das Signal und sendet entsprechende Anweisungen an den Schrittmotor. Der Motortreiber wandelt diese Anweisungen in mechanische Bewegungen des Schrittmotors um, wodurch die physische Interaktion mit der Umwelt ermöglicht wird. Die LED dient dabei als visuelles Feedback für den Benutzer, um zu signalisieren, dass das System ordnungsgemäß funktioniert.

    - [Video zu der Phase 05](https://youtu.be/JOyV6MIt7ds)
  
  - In der sechsten und finalen Phase des Projekts habe ich den Schritt der Realisierung unternommen und eine Modell-Briefkasten aus Pappe erstellt. Ziel war es, eine praktische Umsetzung des vorherigen Designs zu erarbeiten, indem die Komponenten - insbesondere der Ultraschallsensor - in den Briefkasten integriert wurden.

    Als ich jedoch anfing, den Ultraschallsensor seitlich in den Briefkasten einzubauen, stellte ich fest, dass die Wahrscheinlichkeit, dass der Sensor einen eingeworfenen Brief nicht erkennt, zu hoch war. Diese Erkenntnis führte mich dazu, die Position des Sensors zu überdenken.

    Schließlich entschied ich mich, den Ultraschallsensor auf der Rückseite des Briefkastens zu montieren. Dies würde eine bessere Erfassung der eingeworfenen Post ermöglichen, indem der Sensor die Entfernung zwischen sich und der vorderen Wand des Briefkastens misst.

    Diese Änderung erforderte eine Anpassung des Codes, insbesondere eine Verringerung der Erkennungsdistanz des Sensors. Nach mehreren Tests entschied ich mich für eine Distanz von 11 cm, da dieser Wert eine optimale Erkennung der Briefe ermöglichte.

    Schließlich installierte ich die Arduino-Platine und die Stromversorgung, eine kompakte Powerbank, auf der Rückseite des Briefkastens. Bei dem Schrittmotor fügte ich zwei Zeichen hinzu. Diese dienen dazu, den Benutzer visuell darüber zu informieren, ob der Briefkasten gerade voll oder leer ist. Die Position des Schrittmotors weist auf den aktuellen Füllstand des Briefkastens hin, was dem Benutzer einen schnellen und intuitiven Einblick in den Zustand des Briefkastens ermöglicht.

    Somit war die endgültige Implementierung des Projekts abgeschlossen - ein intelligenter Briefkasten, der Benutzer über seinen Füllstand informiert. Dieser Briefkasten stellt einen ersten Prototyp dar und bietet zahlreiche Möglichkeiten für zukünftige Verbesserungen und Erweiterungen.
    - [MailMate-Final-OhneLoRa-MitStepper.ino](https://github.com/namisrn/MailMate/blob/main/MailMate-Final-OhneLoRa-MitStepper.ino)
    - [Video zu der Phase 06](https://youtu.be/44W68I5Qc0Q)

## Schaltpläne und Verdrahtung:
### Hier sind die Schaltpläne und Verdrahtung zu der Phase 04:

  ### Verdrahtungsanweisungen:
   - Arduino Nano RP2040 Connect (Sender):
      01. VCC des HC-SR04 Ultraschallsensors mit dem 5V-Pin des Arduino verbinden.
      02. GND (Masse) des HC-SR04 Ultraschallsensors mit einem der GND-Pins des Arduino verbinden.
      03. Trig des HC-SR04 Ultraschallsensors mit dem digitalen Pin D7 des Arduino verbinden.
      04. Echo des HC-SR04 Ultraschallsensors mit dem digitalen Pin D8 des Arduino verbinden.
      05. Anode (langer Pin) der LED mit dem digitalen Pin D4 des Arduino sowie den Kathodenpin (kürzerer Pin) der LED mit einem der GND-Pins des Arduino verbinden.
  - Arduino Nano RP2040 Connect (Empfänger):
      01. VCC des L293DNE-Treibers mit dem 5V-Pin des Arduino verbinden und Stelle sicher, dass das Enable 1-Pin (Pin 1 auf dem L293DNE) mit 5V verbunden ist.
      02. GND (Masse) des L293DNE-Treibers mit einem der GND-Pins des Arduino verbinden.
      03. Input 1 und Input 2 des L293DNE-Treibers (Pin 2 und Pin 7 auf dem L293DNE) mit den digitalen Pins D5 und D6 des Arduino verbinden.
      04. Output 1 und Output 2 des L293DNE-Treibers (Pin 3 und Pin 6 auf dem L293DNE) mit den Pins des Schrittmotors verbinden.
      05. Versorgungsspannung (VCC2) für den Motor (Pin 8 auf dem L293DNE) mit einer geeigneten Spannungsquelle für Ihren spezifischen Schrittmotor, in der Regel 12V oder 24V verbinden.
      06. Anode (langer Pin) der LED mit dem digitalen Pin D4 des Arduino verbinden und den Kathodenpin (kürzerer Pin) der LED mit einem der GND-Pins des Arduino.


  - ![Phase04_Sender Schaltplan](/assets/Phase04_Sender.PNG)
  - ![Phase04_Empfänger Schaltplan](/assets/Phase04_Empfaenger.PNG)

### Hier sind die Finale Schaltpläne und Verdrahtung (Phase 05 und 06):

### Verdrahtungsanweisungen:
  - **Ultraschallsensor HC-SR04**: verbinde die Pins Ihres HC-SR04 Ultraschallsensors mit Ihrem Arduino wie folgt:
    01. Verbinde den VCC Pin des Sensors mit dem 5V Pin des Arduino.
    02. Verbinde den GND Pin des Sensors mit einem der GND Pins des Arduino.
    03. Verbinde den TRIG Pin des Sensors mit dem digitalen Pin 7 des Arduino.
    04. Verbinde den ECHO Pin des Sensors mit dem digitalen Pin 6 des Arduino.
  - **LED**: Verbinde die LED mit dem Arduino:

    01. Verbinde den Anodenpin (längerer Pin) der LED mit dem digitalen Pin 13 des Arduino.
    02. Verbinde den Kathodenpin (kürzerer Pin) der LED mit einem der GND Pins des Arduino über einen 220 Ohm Widerstand.

  - **Stepper Motor mit L293DNE Treiber:** Verbinde die Pins Ihres L293DNE Treibers und des Schrittmotors mit Ihrem Arduino wie folgt:
    01. Verbinde die VCC1 (Pin 16) und VCC2 (Pin 8) Pins des L293DNE mit dem 5V Pin des Arduino.
    02. Verbinde den GND Pin (Pins 4, 5, 12, 13 des L293DNE) mit einem der GND Pins des Arduino.
    03. Verbinde die Input Pins (Pins 2, 7, 10 und 15) des L293DNE mit den digitalen Pins 8, 9, 10 und 11 des Arduino.
    04. Verbinde die Output Pins (Pins 3, 6, 11 und 14) des L293DNE mit den Pins Ihres Schrittmotors. Je nachdem, wie Ihr spezifischer Schrittmotor gepinnt ist, können Sie die Reihenfolge der Verbindungen anpassen, um die Drehrichtung zu ändern.


  - ![Phase06_Schaltplan](/assets/Phase06.png)



## Fazit

  Als Fazit lässt sich sagen, dass dieses Projekt meine erste Begegnung mit dem Bereich des Internet der Dinge (IoT) darstellte und eine bedeutende Herausforderung mit sich brachte. Dieses Projekt war keine einfache Aufgabe, sondern erforderte viele Stunden an Recherche und kontinuierlicher Entwicklung. Ich musste mich mit zahlreichen Iterationen und Fehlern auseinandersetzen, um das Ziel zu erreichen.

  Dieses Unterfangen war ein intensiver Lernprozess, bei dem ich nicht nur mein technisches Wissen erweitert, sondern auch wertvolle Erfahrungen im Problemlösungsprozess gesammelt habe. Es hat mich gelehrt, dass Ausdauer und Kreativität wesentliche Bestandteile des Entwicklungsprozesses sind. Selbst wenn ich mit Rückschlägen konfrontiert wurde, wie beispielsweise dem Überhitzen der Platine, ließ ich mich nicht entmutigen, sondern nutzte diese Erfahrungen als Gelegenheit zum Lernen und Verbessern.

  Obwohl das resultierende System reduziert wurde, habe ich dennoch ein grundsätzliches Verständnis für die wesentlichen Aspekte des Projekts gewonnen. Es hat mir eine solide Grundlage für zukünftige Verbesserungen und Erweiterungen geboten. Die wichtigste Erkenntnis aus diesem Projekt ist, dass der Lernprozess und die Fähigkeit, sich anzupassen und voranzukommen, trotz unerwarteter Schwierigkeiten, genauso wertvoll sind wie das endgültige Produkt selbst.

  Abschließend bin ich froh darauf, was ich erreicht habe und freue mich auf zukünftige IoT-Projekte, bei denen ich meine neu erworbenen Fähigkeiten und Kenntnisse anwenden und erweitern kann. Dieses Projekt war ein wichtiger Schritt auf meinem Weg, die vielschichtige und spannende Welt des Internet der Dinge besser zu verstehen und darin aktiv zu werden.


## Quelle:

  - [instructables](https://www.instructables.com/)
  - [electroschematics](https://www.electroschematics.com/hc-sr04-datasheet/)
  - [arduino Nano RP2040 Docs](https://docs.arduino.cc/hardware/nano-rp2040-connect)
  - [lora-alliance](https://lora-alliance.org/)
  - [chatGPT](https://chat.openai.com/)
