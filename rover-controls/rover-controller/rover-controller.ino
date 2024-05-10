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
  mqttClient.setCallback(callback);

  Serial.println("Attaching servo to pin 9");
  steeringServo.attach(9);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }

  Serial.println("Moving Servo forward...");
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    steeringServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  Serial.println("Moving Servo backward...");
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    steeringServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  // receive message
  mqttClient.loop();
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
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
