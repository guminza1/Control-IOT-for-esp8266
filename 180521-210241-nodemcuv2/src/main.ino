#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

#define FIREBASE_HOST "iot-control-switch.firebaseio.com"
#define FIREBASE_AUTH "Zk7iERYR8iC1kEAysVYzM6lDUeFFfCmyRimmZcYm"
// set temperrature & humidi
#define DHTTYPE DHT22
#define DHTPIN D1
DHT dht(DHTPIN, DHTTYPE);

//varaible
static int hu;                     //readHumidity
static int tem;                    //readTemperature

static int check_net=0;
int hour,minute,t;
int set_loopwork = 1;
String h_m;

//static int date;                  //Date of month
//static int even_date = 0;         //if date changed get substring day
unsigned long delay_w;            //timer work sl(pump)

struct pin {
  int pin_led = D4;               //led
  int pin_sl1 = D5;
  int pin_sl2 = D6;
  int pin_sl3 = D7;
  int pin_sl4 = D8;
};
struct pin pin;

const String data_switch = "/control/Switch/sw_sl";     //get firebase sw_sl

void setup() {
  pinMode(pin.pin_led,OUTPUT);    //led for chack status connect internet(blink = not connect , not blink = connect)
  pinMode(pin.pin_sl1,OUTPUT);    //pin output sl1
  pinMode(pin.pin_sl2,OUTPUT);    //pin output sl2
  pinMode(pin.pin_sl3,OUTPUT);    //pin output sl3
  pinMode(pin.pin_sl4,OUTPUT);    //pin output sl4

  Serial.begin(9600);
  dht.begin();                    //begin work dht22(tem & hu)

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
    delay(200);
    digitalWrite(pin.pin_led,HIGH);
    delay(200);
    check_net = 1;

  }
  if(check_net == 1){
    digitalWrite(pin.pin_led,LOW);
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    check_net = 0;
  }


  //____________________control_____________________//
  FirebaseObject data = Firebase.get(data_switch );
  String sw_sl1 = data.getString("sl1");    //call firebase sl1
  String sw_sl2 = data.getString("sl2");    //call firebase sl2
  String sw_sl3 = data.getString("sl3");    //call firebase sl3
  String sw_sl4 = data.getString("sl4");    //call firebase sl4

  sw_sl1 == "1"? digitalWrite(pin.pin_sl1,HIGH):digitalWrite(pin.pin_sl1,LOW);
  sw_sl2 == "1"? digitalWrite(pin.pin_sl2,HIGH):digitalWrite(pin.pin_sl2,LOW);
  sw_sl3 == "1"? digitalWrite(pin.pin_sl3,HIGH):digitalWrite(pin.pin_sl3,LOW);
  sw_sl4 == "1"? digitalWrite(pin.pin_sl4,HIGH):digitalWrite(pin.pin_sl4,LOW);

  //____________________Setting time & day for work____________________//
  Day();
  static String day;                                 //varaible use substring name day
  static int count_day = 0;                          //even changed day (check every minute)
  if(hour != count_day){
    day = Day().substring(0,3);                      //substring name day
    count_day = hour;
  }

  static unsigned long count_dht = 0;                  //timer  tem & hu
  if( millis()> count_dht ){                           //read tem & hu every 3 seconds
    tem_hu();
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

    count_dht = millis()+3000;
  }


}
