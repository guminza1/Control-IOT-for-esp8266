#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>

// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

#define FIREBASE_HOST "iot-control-switch.firebaseio.com"
#define FIREBASE_AUTH "Zk7iERYR8iC1kEAysVYzM6lDUeFFfCmyRimmZcYm"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


}

void loop() {
  // String a = Firebase.getString("a/");
  // Serial.println(a);
  for (size_t i = 0; i < 1000; i++) {
  Serial.println(i);
  delay(10);
}
}
