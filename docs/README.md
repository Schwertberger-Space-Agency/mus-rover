# MUS2 Projekt: Mars Rover

## Problembeschreibung

Die Kommunikation im All ist durch die enormen Distanzen stark latenzbehaftet. Diese Verzögerung in der Antwort sorgt dafür, dass man einen Marsrover nicht in Echtzeit manuell fernsteuern kann. Die Verzögerung zwischen dem Command Center auf der Erde und dem Mars Rover liegt je nach Stand der Planeten zwischen 3:25 Minuten und 22 Minuten. Problematisch wird dieser Fakt, sobald es Hindernisse gibt, gegen welche der Rover fahren könnte. Dementsprechend gilt es, die Fernsteuerung so resilient wie möglich zu gestalten.

Das Projekt versucht anhand eines Lego-Rover-Prototypen unter Verwendung des Arduinos, Sensoren und eines Servomotors dieses Problem zu simulieren. Desweiteren soll unter Verwendung von Ultraschallsensoren eine einfache Form der Kollisionsvermeidung erreicht werden.

## Lösungsansatz

Die Basis des Projekts stellt ein Rover zusammengebaut aus Klemmbausteinen der Marke Clementoni. Dessen Grundgerüst besteht aus drei Radachsen, einer Lenkanlage zur manuellen Richtungssteuerung und einem Elektromotor welcher den Rover vor- oder rückwärts treibt. Der Elektromotor wird durch eine Batterie gespeist.

Im ersten Teil des Projekts soll die Steuerung des Rovers durch ein "Command Center" ermöglicht werden. Dies soll ermöglicht werden, indem die Lenkanlage mithilfe mittels eines Servomotors gesteuert kontrolliert wird. Dieser Servomotor ist wiederum mit einem Arduino verbunden, der dessen Steuerung übernimmt. Mittels MQTT empfängt der Arduino vom Command Center Commands, in welche Richtung dieser sich zu bewegen hat. Dieser Kommunikationsansatz ist deklarativ zu betrachten, da der Rover die Möglichkeit hat, aufgrund von Hindernissen zum Beispiel Commands außer Kraft zu setzen. Schlussendlich liegt es im Interesse der Menschheit, die Zerstörung eines Mars Rovers zu vermeiden.

Sobald die Steuerung des Rovers funktioniert, sollen Ultraschallsensoren installiert werden, die zur Obstacle Detection und Avoidance dienen sollen. Erkennen die Ultraschallsensoren einen Gegenstand, der in einer Entfernung unter dem Schwellwert liegen, soll die weitere Annäherung an dieses Objekt verhindert werden. In anderen Worten blockiert der Motor, wenn ein gefährliches Objekt erkannt wird.

## Implementierung

Die Implementierung des Rovers kann in drei Teile aufgespalten werden: Kommunikation, Command Center und der eigentliche Mars Rover. Die Implementierung dieser drei Teilbereiche erklärt diese Sektion näher.

### Kommunikation und Protokoll

Zur Verwendung wird wie bereits verwendet MQTT verwendet. Das Steuerungsprotokoll ist so unkompliziert wird möglich gehalten. Jede Nachricht des Command Centers and den Rover besteht aus zwei Teilen: Direction und Velocity. Jeder dieser Teil wird durch jeweils einen Charakter repräsentiert.

Die Sektion Direction erlaubt vier verschiedene Richtungen F (Forward), B (Backwards), L (Left) und R (Right). Die Sektion Velocity ist als "Toggle" zu verstehen, denn es besteht aus den Commands B (Begin) und E (End).

Die Repräsentierung dieser Commands erfolgt im Command Center als Enum:
```kt
enum class Direction(val value: String) {
    F("F"),
    B("B"),
    L("L"),
    R("R")
}

enum class Velocity(val value: String) {
    B("B"),
    E("E")
}
```

Um das Protokoll besser zu verstehen ein Beispiel: Will ein User die Räder nach links stellen, so sendet dieser als erstes den Command `LB`. Daraufhin beginnt der Servomotor zu arbeiten und das Rad dreht sich. Soll das Wendemanöver beendet werden, sendet der User das Kommando `LE`, um die Lenkung nach links zu beenden.

Als Broker dient derselbe, der bereits aus der Übung bekannt ist: `broker.mqttdashboard.com` mit dem Topic `mus-rover/in-controls`.

### Command Center

### Mars Rover

## Ergebnisse

// Insert rover images here

// insert rover video here

// mqtt screenshots







Problemstellung

Die Kommunikation im All ist durch die enormen Distanzen stark latenzbehaftet. Diese Latenz sorgt dafür, dass man z.B. einen Marsrover nicht in Echtzeit manuell fernsteuern kann. Problematisch wird das, sobald es Hindernisse gibt, gegen welche dieser Rover fahren kann und wodurch dieses teure Gerät beschädigt wird. Unser Projekt versucht anhand eines Lego-Rover-Prototypen diese Problemlösung zu simulieren.

 

Lösungsansatz

Wir besitzen einen Rover zusammengebaut aus Klemmbausteinen der Marke Clementoni. Dieser kann zurzeit mit einem Zahnrad gelenkt werden. Ein Elektromotor erlaubt es dem Rover Vorwärts oder Rückwärts zu fahren. Der erste Schritt unserers Projektes ist es, diesen Rover mittels Arduino, Servomotoren und einer Desktop-App fernzusteuern. Im zweiten Schritt werden Ultraschallsensoren verwendet, um Hindernisse zu erkennen und den Rover anzuhalten, sollte dieser gegen das Hindernis gesteuert werden.

 

Erwartete Ergebnisse

Der Rover wird mittels eines Arduino und Servomotoren gesteuert. Die Steuerungsbefehle erhält der Arduino von einer Desktopanwendung, welche in Kotlin geschrieben ist. Die Kommunikation erfolgt dabei über Wlan mittels des MQTT-Protokolls. Ultraschallsensoren geben dem Arduino die nötigen Informationen, ob dieser die erhaltenen Steuerungsbefehle, ohne gegen ein Hindernis zu fahren, ausführen darf.