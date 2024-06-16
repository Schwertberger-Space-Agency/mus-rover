# Problembeschreibung

Die Kommunikation im All ist durch die enormen Distanzen stark latenzbehaftet. Diese Verzögerung in der Antwort sorgt dafür, dass man einen Marsrover nicht in Echtzeit manuell fernsteuern kann. Die Verzögerung zwischen dem Command Center auf der Erde und dem Mars Rover liegt je nach Stand der Planeten zwischen 3:25 Minuten und 22 Minuten. Problematisch wird dieser Fakt, sobald es Hindernisse gibt, gegen welche der Rover fahren könnte. Dementsprechend gilt es, die Fernsteuerung so resilient wie möglich zu gestalten. Unser Projekt versucht anhand eines Lego-Rover-Prototypen unter Verwendung des Arduinos, Sensoren und eines Servomotors dieses Problem zu simulieren.

# Lösungsansatz



# Implementierung

## Kommunikation und Protokoll

## Command Center

## Mars Rover

# Ergebnisse

// Insert rover images here

// insert rover video here

// mqtt screenshots







Problemstellung

Die Kommunikation im All ist durch die enormen Distanzen stark latenzbehaftet. Diese Latenz sorgt dafür, dass man z.B. einen Marsrover nicht in Echtzeit manuell fernsteuern kann. Problematisch wird das, sobald es Hindernisse gibt, gegen welche dieser Rover fahren kann und wodurch dieses teure Gerät beschädigt wird. Unser Projekt versucht anhand eines Lego-Rover-Prototypen diese Problemlösung zu simulieren.

 

Lösungsansatz

Wir besitzen einen Rover zusammengebaut aus Klemmbausteinen der Marke Clementoni. Dieser kann zurzeit mit einem Zahnrad gelenkt werden. Ein Elektromotor erlaubt es dem Rover Vorwärts oder Rückwärts zu fahren. Der erste Schritt unserers Projektes ist es, diesen Rover mittels Arduino, Servomotoren und einer Desktop-App fernzusteuern. Im zweiten Schritt werden Ultraschallsensoren verwendet, um Hindernisse zu erkennen und den Rover anzuhalten, sollte dieser gegen das Hindernis gesteuert werden.

 

Erwartete Ergebnisse

Der Rover wird mittels eines Arduino und Servomotoren gesteuert. Die Steuerungsbefehle erhält der Arduino von einer Desktopanwendung, welche in Kotlin geschrieben ist. Die Kommunikation erfolgt dabei über Wlan mittels des MQTT-Protokolls. Ultraschallsensoren geben dem Arduino die nötigen Informationen, ob dieser die erhaltenen Steuerungsbefehle, ohne gegen ein Hindernis zu fahren, ausführen darf.