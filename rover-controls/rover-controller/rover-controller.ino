#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

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
const int forwardDistancePin = 2;
int pos = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  // check firmware version. 1.1.0 is mandatory
  // wifi shield is usually delivered with 1.0.0
  // and an upgrade to 1.1.0 is necessary!
  String fv = WiFi.firmwareVersion();
  Serial.print("firmwareVersion: ");
  Serial.println(fv);
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware"); 

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  Serial.println("Connected to wifi");

  Serial.print("\nConnect to MQTT broker: ");
  Serial.println(mqttServerAddress);
 
  mqttClient.setServer(mqttServerAddress, mqttServerPort);
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
  delay(1000);
}

void moveServo(Servo &servoRef, bool forward) {
  int limit, stepsize;
  if(forward) {
    limit = 90; // pos is either 0 or -90
    stepsize = 1;
  } else {
    limit = -90; // pos is either 0 or 90
    stepsize = -1;
  }

  for(; pos != limit; pos += stepsize)
  {
    servoRef.write(pos);
    delay(20); // wait for servo to reach its position
  }
}

int getDistance(int distanceScannerPin) {
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
    command.concat(payload[i]);
  }

  if(command.length() != 2) { return; } // invalid command

  if(command == "fl") // forward left
  {
    // TODO
  }
  else if(command == "fr") // forward right
  {
    // TODO
  }
  else if(command == "bl") // backward left
  {
    // TODO
  }
  else if(command == "br") // backward right
  {
    // TODO
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
