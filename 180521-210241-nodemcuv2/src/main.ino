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
int check_net=0;
int hour,minute,t;
int set_loopwork = 1;
String h_m;

struct pin {
  int pin_led = D4;     // led
  int pin_sl1 = D5;
  int pin_sl2 = D6;
  int pin_sl3 = D7;
  int pin_sl4 = D8;
};
struct pin pin;

void setup() {
  //led status WiFi
  pinMode(pin.pin_led,OUTPUT);

  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //____________________Internet_____________________//
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("reconected setup");
    digitalWrite(pin.pin_led,LOW);
    delay(500);
    digitalWrite(pin.pin_led,HIGH);
    delay(500);
    check_net = 1;

  }
  if(check_net == 1){
    digitalWrite(pin.pin_led,LOW);
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    check_net = 0;
  }

  while(Firebase.failed()) {
    Serial.println("reconected firebase");
    Serial.println(Firebase.error());
    delay(500);
  }

  String day = Day().substring(0,3);


  if(day == "Mon"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_mon");
    if(sw_day == "\"on\""){
      work();
    }
  }

  if(day == "Tue"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_tue");
    if(sw_day == "\"on\""){
      work();
    }
  }

  if(day == "Wed"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_wed");
    if(sw_day == "\"on\""){
work();
    }
  }

  if(day == "Thu"){

    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_thu");
    if(sw_day == "\"on\""){
      work();
    }
  }

  if(day == "Fri"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_fri");
    if(sw_day == "\"on\""){
      work();
    }
  }

  if(day == "Sat"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_sat");
    if(sw_day == "\"on\""){
      work();
    }
  }

  if(day == "Sun"){
    String sw_day = Firebase.getString("/control/Switch/sw_day/sw_sun");
    if(sw_day == "\"on\""){
      work();
    }
  }
}
