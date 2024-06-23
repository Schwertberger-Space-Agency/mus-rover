#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

enum class Direction {Forward, Backward, Left, Right};

char mqttServerAddress[] = "broker.mqttdashboard.com";
int mqttServerPort = 1883;
int msgCounter = 0;
int status = WL_IDLE_STATUS;

char ssid[] = "Elosia"; // network SSID
char pass[] = "defosamowi!2023"; // network passphrase

WiFiClient client;
PubSubClient mqttClient(client);

Servo steeringServo;
const int servoPin = 9;
const int forwardDistancePin = 3;
const float minDistance = 5;
int pos = 0;

bool shouldMove = false;
Direction moveDirection = Direction::Forward;

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  Serial.print("firmwareVersion: ");
  Serial.println(fv);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  Serial.println("Connected to wifi");

  mqttClient.setServer(mqttServerAddress, mqttServerPort);
  Serial.print("Connected to MQTT broker");
  mqttClient.setCallback(onMessageReceive);

  Serial.println("Attaching servo");
  steeringServo.attach(servoPin);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  // receive message
  mqttClient.loop();

  if(shouldMove)
  {
    // Because we cannot move forward/backward we simplified the condition, that if something is in the way, the rover cannot move
    // of course in reality if the forward sensor detects something, we should be able to move backward still
    if(getDistanceCM(forwardDistancePin) < minDistance)
    {
      Serial.println("Obstacle detected. Cannot move");
      delay(20);
      return;
    }

    if (moveDirection == Direction::Right)
    {
      moveServo(steeringServo, true);
    }
    else if(moveDirection == Direction::Left)
    {
      moveServo(steeringServo, false);
    }
  }

  delay(20);
}

void moveServo(Servo &servoRef, bool forward) {
  int limit, stepsize;
  if(forward) {
    limit = 120; // pos is either 0 or -45
    stepsize = 1;
  } else {
    limit = -120; // pos is either 0 or 45
    stepsize = -1;
  }

  pos += stepsize;
  if((forward && pos > limit) || (!forward && pos < limit)) {
    pos = limit;
  }
  Serial.print("Moving Servo to position...");
  Serial.println(pos);
  servoRef.write(pos);
  delay(100); // wait for servo to reach its position
}

int getDistanceCM(int distanceScannerPin) {
  long durationMs, cm;

  // Write to ultrasound sensor
  pinMode(distanceScannerPin, OUTPUT); // pin is now set to write mode
  digitalWrite(distanceScannerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(distanceScannerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(distanceScannerPin, LOW);

  // Read from ultrasound sensor
  pinMode(distanceScannerPin, INPUT); // pin is now set to read mode
  durationMs = pulseIn(distanceScannerPin, HIGH);

  cm = microsecondsToCentimeter(durationMs);
  return cm;
}

long microsecondsToCentimeter(long microseconds) {
  // 340m/s or 29 microseconds per centimeter
  return microseconds / 29 / 2; // divided by 2 because sound also needs to travel back to us
}

void onMessageReceive(char* topic, byte* payload, unsigned int length) {
  String command;
  for (int i=0;i<length;i++) {
    command.concat((char)payload[i]);
  }

  if(command.length() != 2) 
  { 
    // invalid command
    Serial.print("invalid command received. Command was: ");
    Serial.println(command);
    return; 
  } 

  Serial.print("Received command...");
  Serial.println(command);

  switch (command[0]) {
    case 'F':
      moveDirection = Direction::Forward;
      break;
    case 'B':
      moveDirection = Direction::Backward;
      break;
    case 'L':
      moveDirection = Direction::Left;
      break;
    case 'R':
      moveDirection = Direction::Right;
      break;
    default:
      Serial.println("Received invalid direction");
  }
  switch (command[1]) {
    case 'B':
      shouldMove = true;
      break;
    case 'E':
      shouldMove = false;
      break;
    default:
      Serial.println("Received invalid start stop notification");
  }
}

// reconnect logic for MQTT
void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
	  // this must be a unique ID for every client
    if (mqttClient.connect("S2310454018-Arduino")) {
      Serial.println("connected");
      mqttClient.subscribe("mus-rover/in-controls");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
