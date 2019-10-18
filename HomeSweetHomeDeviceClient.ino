#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Secrets.h"

#define debug 1

const char* SSID = SECRET_SSID;
const char* PSK = SECRET_PSK;
const char* MQTT_BROKER_IP = SECRET_MQTTBROKER;
const int MQTT_BROKER_PORT = 1833;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  if (debug) {
    Serial.begin(115200);
  }
  setupWifi();
  client.setServer(MQTT_BROKER_IP, MQTT_BROKER_PORT);
}

void loop() {

  if (!client.connected()) {
    reconnectMqtt();
  }
  client.loop();

  snprintf (msg, 50, "Alive since %ld milliseconds", millis());
  debugPrint("Publish message: ");
  debugPrintln(msg);
  client.publish("/home/data", "Hello World");
  delay(5000);
}

void setupWifi() {
  delay(10);
  debugPrintln("");
  debugPrint("Connecting to ");
  debugPrintln(SSID);

  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debugPrint(".");
  }

  debugPrintln("");
  debugPrintln("WiFi connected");
  debugPrintln("IP address: ");
  debugPrintln("" + WiFi.localIP());
}

void reconnectMqtt() {
  while (!client.connected()) {
    debugPrint("Reconnecting...");
    if (!client.connect("ESP8266Client")) {
      debugPrint("failed, rc=");
      debugPrint("" + client.state());
      debugPrintln(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void debugPrint(char* message) {
  if (debug) {
    Serial.print(message);
  }
}

void debugPrint(const char* message) {
  if (debug) {
    Serial.print(message);
  }
}

void debugPrintln(char* message) {  
  if (debug) {
    Serial.println(message);
  }
}

void debugPrintln(const char* message) {
  if (debug) {
    Serial.println(message);
  }
}