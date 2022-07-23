#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include <stdio.h>
#include <Shifty.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Declare the shift register
Shifty shift; 


int SER_Pin = 14;   //pin 14 on the 75HC595 data
int RCLK_Pin = 12;  //pin 12 on the 75HC595 latch
int SRCLK_Pin = 13; //pin 11 on the 75HC595 clk
// Update these with values suitable for your network.

const char* ssid = "GottaBounce";
const char* password = "Asdf1234";
const char* mqtt_server = "192.168.0.104";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int myPin = 0;
String myTopic = "";
String myPayload = "";
char pin = '0';



void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.hostname("ESP_JebaoDP4");

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
   Serial.print("]");
  String pinStr = "0";
  pinStr = ((String)((char)topic[strlen(topic)-1]));
  int myPin = pinStr.toInt();
  Serial.println();

  Serial.println((char)payload[0]);
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0' ) {
        shift.writeBit(myPin, LOW);   
  } else {
        shift.writeBit(myPin, HIGH); 
  }

  client.publish("Sensor/DP4", topic );
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP_JebaoDP4-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("dosing/DP4", "dosing/DP4 is Online");
      // ... and resubscribe
      client.subscribe("dosing/DP4/+");
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

  Serial.begin(115200);
   // Set the number of bits you have (multiples of 8)
  shift.setBitCount(8);

  // Set the clock, data, and latch pins you are using
  // This also sets the pinMode for these pins
  //int SER_Pin = 14;   //pin 14 on the 75HC595 data
  //int RCLK_Pin = 12;  //pin 12 on the 75HC595 latch
  //int SRCLK_Pin = 13; //pin 11 on the 75HC595 clk
  
  shift.setPins(SER_Pin, SRCLK_Pin, RCLK_Pin); 
  
  setup_wifi();

  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  
 // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("ESP_JebaoDP4");

  // No authentication by default
  ArduinoOTA.setPassword((const char *)"333");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(0);
  ArduinoOTA.handle();

}
