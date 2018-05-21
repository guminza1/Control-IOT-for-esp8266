#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>

// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

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

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  //hello

}
