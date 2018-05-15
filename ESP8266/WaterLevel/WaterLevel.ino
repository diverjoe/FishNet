#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include <stdio.h>

#define DOUT D2
#define PD_SCK D1
#define factor 0.00959 //40Kg china

// Update these with values suitable for your network.

const char* ssid = "GottaBounce";
const char* password = "Asdf1234";
const char* mqtt_server = "192.168.0.28";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value2 = 0;
int myPin = 0;
String myTopic = "";
String myPayload = "";
char pin = '0';
unsigned long value;
long weight;

long get_weight()
{
  digitalWrite(PD_SCK, LOW);
  delayMicroseconds(1);
  // wait for the chip to become ready:
  while (digitalRead(DOUT) == HIGH);
  value = 0;
  for (int i = 23; i > -1; i--) { //bitWrite23 =bit24
    digitalWrite(PD_SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(PD_SCK, LOW);
    if (digitalRead(DOUT) == HIGH) {
      bitSet(value, i);
    }
  }

  digitalWrite(PD_SCK, HIGH);
  delayMicroseconds(1);
  digitalWrite(PD_SCK, LOW);
  delayMicroseconds(1);

  return value; // 100% = 1677215
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.hostname("ESP_WaterLevel");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);

  weight = get_weight();
  float calibratedweight;
  calibratedweight = round(weight * factor);


    char result[50] = "";
    //sprintf(result, "%.d", calibratedweight);
    //snprintf (result, 50, "Water Level #%f", calibratedweight);
    dtostrf(calibratedweight, 15, 2, result);
    client.publish("Sensor/WL2", result);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world2");
      // ... and resubscribe
      client.subscribe("Sensor/espWL");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.print(clientId);
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

  pinMode(DOUT, INPUT);
  pinMode(PD_SCK, OUTPUT);

  //  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  //   pinMode(12, OUTPUT);
  //   pinMode(13, OUTPUT);
  //   pinMode(14, OUTPUT);
  //   pinMode(16, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();



  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value2;

 //   snprintf (msg, 75, "hello world #%ld", value2);
 //   Serial.print("Publish message: ");
 //   Serial.println(msg);
    //Serial.print(result);
    // client.publish("Sensor/WL2", msg);

    weight = get_weight();
    float calibratedweight;
    calibratedweight = round(weight * factor);
  //  Serial.println(weight, 0);


    char result[50] = "";
    //sprintf(result, "%.d", calibratedweight);
  //  snprintf (result, 50, "Water Level #%f", calibratedweight);
    dtostrf(calibratedweight, 15, 0, result);
    client.publish("Sensor/WL2", result);


  }


}

