# MailMate 
Ubiquitous Computing - Projektbericht. (Update Stand: 17.06.2023)
01. Einführung:
Das Ziel dieses Projekts war es, einen tieferen Einblick in die IoT-Technologien zu gewinnen und ein praktisches System zu entwickeln, das unser alltägliches Leben bereichern könnte. Angesichts der Herausforderungen, die sich aus der immerwährenden Prüfung unseres Briefkastens ergeben, schien die Entwicklung eines intelligenten Briefkasten-Benachrichtigungssystems eine geeignete und interessante Aufgabe zu sein.
02. Überblick über das Projekt: 
Das entwickelte Projekt zielt darauf ab, den Benutzer zu entlasten, indem es automatisch eine Benachrichtigung auslöst, sobald ein Postbote einen Brief in den Briefkasten einwirft. Das System besteht aus zwei Hauptkomponenten: einem Sensor-Modul, das auf dem Arduino Nano RP2040 und einem HC-SR04 Ultraschallsensor basiert, und einem Aktor-Modul, das ebenfalls auf dem Arduino Nano RP2040 und einem Servomotor basiert. Beide Module kommunizieren drahtlos über die integrierten WiFi-Module der Arduinos, und ihre Status werden über rote LEDs angezeigt.

03. Problemstellung: 
Obwohl viele von uns in Mehrfamilienhäusern leben oder unser Briefkasten weit von unserem Wohnraum entfernt ist, bleibt das Überprüfen des Briefkastens auf Post eine lästige Aufgabe. Es wäre effizienter, eine Benachrichtigung zu erhalten, sobald die Post eingeworfen wird, damit wir nicht unnötig zum Briefkasten gehen müssen.
04. Lösungsansatz: 
Um dieses Problem zu lösen, wurde ein System entwickelt, das aus einem Sensor- und einem Aktor-Modul besteht. Der Ultraschallsensor erkennt, wenn ein Objekt (z.B. ein Brief) in den Briefkasten geworfen wird, und sendet ein Signal an das Aktor-Modul. Das Aktor-Modul gibt dann eine visuelle und physische Reaktion: es leuchtet eine LED auf und der Servomotor dreht sich. Diese Aktionen signalisieren dem Benutzer, dass Post eingeworfen wurde.

05. Technische Details und Implementierung: 
Der technische Kern des Systems besteht aus diese Hauptkomponenten: zwei Arduino Nano RP 2040 Boards, die jeweils mit einem HC-SR04 Ultraschallsensor und einem Servomotor ausgestattet sind. Für die Kommunikation zwischen den beiden Arduinos ist die integrierte WiFiNINA-Bibliothek verwendet worden, die eine einfache und effektive Möglichkeit bietet, WiFi-Kommunikation zu implementieren.

- In der ersten Phase des Projekts lag der Schwerpunkt auf der Erkennung eines Objekts durch den Ultraschallsensor. Hierfür wurde zunächst ein Testsystem aufgebaut, um verschiedene Entfernungen auszuprobieren. Es wurde festgestellt, dass ein Abstand von 15 cm am effektivsten war, um das Einlegen von Objekten in den Briefkasten zuverlässig zu erkennen.

- Um die Realität des Gebrauchs zu simulieren, wurde ein Prototyp aus Pappe erstellt, der als Briefkasten diente. Dieser Schritt war entscheidend, um die Effektivität und Zuverlässigkeit des Sensors in einer realistischeren Umgebung zu testen. Das Endprodukt war ein System, das in der Lage war, Objekte zuverlässig zu erkennen, wenn sie in den Briefkasten eingeworfen wurden.

- Die zweite Phase des Projekts bestand darin, einen Servomotor hinzuzufügen. Der Motor wurde so programmiert, dass er sich dreht, wenn ein Objekt erkannt wurde, was als Signal für den Benutzer diente, dass ein neues Objekt in den Briefkasten eingeworfen wurde.

- In der dritten Phase des Projekts wurden die Funktionen auf zwei separate Arduinos aufgeteilt, wobei einer als Sender (mit dem Ultraschallsensor) und der andere als Empfänger (mit dem Servomotor) fungierte. Dieser Schritt erforderte einige Anpassungen im Code, um sicherzustellen, dass die Kommunikation zwischen den beiden Geräten reibungslos funktionierte.

- Die Herausforderung bestand darin, sicherzustellen, dass die beiden Arduinos effektiv miteinander kommunizieren konnten. Nach einigen Recherchen wurde herausgefunden, dass die Eingabe der IP-Adresse des Empfängers in den Sendercode eine effektive Methode war, um eine stabile Verbindung herzustellen. Das Verbinden der beiden Geräte erforderte auch das Einrichten eines WiFi-Netzwerks, wobei das SSID und das Passwort manuell eingegeben wurden.

- In der vierten Phase wurden rote LEDs zu beiden Arduinos hinzugefügt. Diese dienen als zusätzliche visuelle Indikatoren: Wenn der Sender ein Objekt erkennt, leuchtet seine LED auf, und wenn das Signal vom Empfänger empfangen wird, leuchtet dessen LED auch auf und der Servomotor dreht sich.

- Durch diese iterativen Phasen der technischen Entwicklung und Optimierung konnte ich ein System schaffen, das nicht nur funktional, sondern auch intuitiv zu bedienen ist. Durch die Kombination von Sensortechnik, Mechanik und drahtloser Kommunikation konnte ich ein Produkt schaffen, das den Benutzer effektiv darüber informiert, wenn Post in den Briefkasten eingeworfen wird.

04. Ergebnisse und Diskussion: 
Obwohl das System grundsätzlich funktioniert, gab es einige Herausforderungen und Verbesserungsmöglichkeiten. Eines der Hauptprobleme war die Stabilität der WiFi-Verbindung, die besonders bei größeren Entfernungen ein Problem darstellte. Eine Möglichkeit, dieses Problem zu lösen, könnte die Verwendung von LoRaWAN-Modulen anstelle der WiFi-Kommunikation sein.

- Darüber hinaus könnte ein “Stepper Motor” anstelle des Servomotors für mehr Flexibilität in der Bewegung und genauerer Kontrolle eingesetzt werden.

- Trotz dieser Herausforderungen war das Projekt ein Erfolg und hat gezeigt, wie IoT-Technologien zur Lösung alltäglicher Probleme beitragen können. Es bot eine wertvolle Lernerfahrung und eröffnete Möglichkeiten für zukünftige Projekte und Verbesserungen.
