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
  setup_wifi();
  client.setServer(MQTT_BROKER_IP, MQTT_BROKER_PORT);
}

void loop() {

  if (!client.connected()) {
    reconnectMqtt
  }
  client.loop();

  snprintf (msg, 50, "Alive since %ld milliseconds", millis());
  debug("Publish message: ");
  debugln(msg);
  client.publish("/home/data", "Hello World");
  delay(5000);
}

void setupWifi() {
  delay(10);
  debugln();
  debug("Connecting to ");
  debugln(SSID);

  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debug(".");
  }

  debugln("");
  debugln("WiFi connected");
  debugln("IP address: ");
  debugln(WiFi.localIP());
}

void reconnectMqtt() {
  while (!client.connected()) {
    debug("Reconnecting...");
    if (!client.connect("ESP8266Client")) {
      debug("failed, rc=");
      debug(client.state());
      debugln(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void debug(char* message) {
  if (debug) {
    Serial.print(message);
  }
}

void debugln(char* message) {
  if (debug) {
    Serial.println(message);
  }
}
