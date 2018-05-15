#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
 
const char* ssid = "GottaBounce";
const char* password = "Asdf1234";
const char* mqtt_server = "192.168.0.28";

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
    Serial.println("Setting up WiFi.");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
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
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    myPayload += ((char)payload[i]);
  }
 Serial.println();
  for (int i = 0; i < 12; i++) {
   Serial.print((char)topic[i]);
    myTopic += ((char)payload[i]);
    pin = ((char)topic[i]);
  }
  Serial.println();
 pin = '0';
  pin = ((char)topic[strlen(topic)-1]);
  Serial.print(pin);
  Serial.println();



//pin = topic[myTopic.length()];
//myPin = pin.toInt();
//Serial.println(topic[topic.length()-1]);
switch(pin) {
    case '1' :
        myPin = 3;
      //   client.publish("ESP_socket8", "Pin:1 MyPin:3 ");
        break;
    case '2':
        myPin = 1;
        // client.publish("ESP_socket8", "Pin:2 MyPin:1 ");
        break;
    case '3':
        myPin = 13;
         //client.publish("ESP_socket8", "Pin:3 MyPin:13");
        break;
    case '4':
        myPin = 15;
         //client.publish("ESP_socket8", "Pin:4 MyPin:15");
        break;                
    case '5':
        myPin = 14;
         //client.publish("ESP_socket8", "Pin:5 MyPin:14");
        break;   
    case '6':
        myPin = 12;
        // client.publish("ESP_socket8", "Pin:6 MyPin:12");
        break;   
    case '7':
        myPin = 5;
         //client.publish("ESP_socket8", "Pin:7 MyPin:5 ");
        break;   
    case '8':
        myPin = 4;
         //client.publish("ESP_socket8", "Pin:8 MyPin:4 ");
        break;                                   
    default:
        myPin = BUILTIN_LED;
}

Serial.println(myPin);
  // Switch on the LED if an 1 was received as first character
  if (myPin != BUILTIN_LED){
  if ((char)payload[0] == '0' && pin != '0') {
    digitalWrite(myPin, LOW);   
  } else {
    digitalWrite(myPin, HIGH); 
  }

  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    
    //Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
   //   Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("ESP_socket8", "ESP socket 8.2 Online!");
      // ... and resubscribe
      
      client.subscribe("ESP/socket8/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  setup_wifi();
 // pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(1, OUTPUT);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("ESP_socket8");

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


