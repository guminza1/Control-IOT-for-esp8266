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
static String even_sl1 = "0";      //check switch sl1
static String even_sl2 = "0";      //check switch sl2
static String even_sl3 = "0";      //check switch sl3
static String even_sl4 = "0";      //check switch sl4

static int hu;                     //readHumidity
static int tem;                    //readTemperature

int check_net=0;
int hour,minute,t;
int set_loopwork = 1;
String h_m;

static int date;                  //Date of month
static int even_date = 0;         //if date changed get substring day

struct pin {
  int pin_led = D4;               //led
  int pin_sl1 = D5;
  int pin_sl2 = D6;
  int pin_sl3 = D7;
  int pin_sl4 = D8;
};
struct pin pin;


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
  while(Firebase.failed()) {
    digitalWrite(pin.pin_led,LOW);
    delay(1000);
    digitalWrite(pin.pin_led,HIGH);
    delay(1000);
    Serial.println(Firebase.error());
  }

  static unsigned long count_dht = 0;                  //timer  tem & hu
  if( millis()> count_dht ){                           //read tem & hu every 3 seconds
    tem_hu() ;
    count_dht = millis()+3000;
    Serial.println(count_dht);
  }

  //____________________control_____________________//
  String sw_sl1 = Firebase.getString("/control/Switch/sw_sl/sl1");    //call firebase sl1
  String sw_sl2 = Firebase.getString("/control/Switch/sw_sl/sl2");    //call firebase sl2
  String sw_sl3 = Firebase.getString("/control/Switch/sw_sl/sl3");    //call firebase sl3
  String sw_sl4 = Firebase.getString("/control/Switch/sw_sl/sl4");    //call firebase sl4

  if(sw_sl1 != even_sl1){                 //chech switch_sl1 on/off
    if(sw_sl1 == "1"){
      digitalWrite(pin.pin_sl1,HIGH);
    }
    else{
      digitalWrite(pin.pin_sl1,LOW);
    }
    even_sl1 = sw_sl1;
  }


  if(sw_sl2 != even_sl2){                 //chech switch_sl2 on/off
    if(sw_sl2 == "1"){
      digitalWrite(pin.pin_sl2,HIGH);
    }
    else{
      digitalWrite(pin.pin_sl2,LOW);
    }
    even_sl2 = sw_sl2;
  }


  if(sw_sl3 != even_sl3){                 //chech switch_sl3 on/off
    if(sw_sl3 == "1"){
      digitalWrite(pin.pin_sl3,HIGH);
    }
    else{
      digitalWrite(pin.pin_sl3,LOW);
    }
    even_sl3 = sw_sl3;
  }

  if(sw_sl4 != even_sl4){                 //chech switch_sl4 on/off
    if(sw_sl4 == "1"){
      digitalWrite(pin.pin_sl4,HIGH);
    }
    else{
      digitalWrite(pin.pin_sl4,LOW);
    }
    even_sl4 = sw_sl4;
  }

  //____________________Setting time & day for work____________________//

  Day();
  static String day;                                 //varaible use substring name day
  static int count_day = 0;                          //even changed day (check every minute)
  if(minute != count_day){
    day = Day().substring(0,3);                      //substring name day
    count_day = minute;
    Serial.println("check day");
  }


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
