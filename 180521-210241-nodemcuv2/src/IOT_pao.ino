#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>


// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

#define FIREBASE_HOST "iot-control-switch.firebaseio.com"
#define FIREBASE_AUTH "Zk7iERYR8iC1kEAysVYzM6lDUeFFfCmyRimmZcYm"

//varaible
String num_day;
int led=D4;

void setup() {
  //led status WiFi
  pinMode(led,OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("reconected setup");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);



}

void loop() {
  // String x = Day();
  // Serial.println(x);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("reconected loop");

  }
  Serial.println(WiFi.localIP());

  digitalWrite(led,LOW);
  delay(100);
  digitalWrite(led,HIGH);
  delay(100);



}
