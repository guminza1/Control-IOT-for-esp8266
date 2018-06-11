void work(){
  int te,tm;
  String unit_water = Firebase.getString("/control/unit_water"); // get firebase  unit water (sec,minute,hour)
  String t_water = Firebase.getString("/control/water");  // get firebase time working
  String t_water1 = t_water.substring(1,t_water1.length()-1); //sub string time working
  unsigned long delay_w = t_water1.toInt();
  if (unit_water == "\"s\"") {
    delay_w *= 1000;
  }
  if(unit_water == "\"m\""){
    delay_w *= 60000;
  }
  if(unit_water == "\"h\""){
    delay_w *= 3600000;
  }

  h_m = String(hour)+String(minute);
  t = h_m.toInt();

  String mor = Firebase.getString("/control/Switch/sw_time/sw_morning");
  if(mor == "\"on\""){
    String x = Firebase.getString("/control/set_time/tm");
    String sub_x = x.substring(1,x.length()-1);
    tm = sub_x.toInt();
    if (tm == t && set_loopwork == 1) {
      set_loopwork = 0;
      digitalWrite(pin.pin_sl1,HIGH);
      digitalWrite(pin.pin_sl2,HIGH);
      digitalWrite(pin.pin_sl3,HIGH);
      digitalWrite(pin.pin_sl4,HIGH);
      delay(delay_w);
      digitalWrite(pin.pin_sl1,LOW);
      digitalWrite(pin.pin_sl2,LOW);
      digitalWrite(pin.pin_sl3,LOW);
      digitalWrite(pin.pin_sl4,LOW);

    }
  }

  String eve = Firebase.getString("/control/Switch/sw_time/sw_evening");
  if(eve == "\"on\""){
    String y = Firebase.getString("/control/set_time/te");
    String sub_y = y.substring(1,y.length()-1);
    te = sub_y.toInt();
    if (te == t && set_loopwork == 1) {
      set_loopwork = 0;
      digitalWrite(pin.pin_sl1,HIGH);
      digitalWrite(pin.pin_sl2,HIGH);
      digitalWrite(pin.pin_sl3,HIGH);
      digitalWrite(pin.pin_sl4,HIGH);
      delay(delay_w);
      digitalWrite(pin.pin_sl1,LOW);
      digitalWrite(pin.pin_sl2,LOW);
      digitalWrite(pin.pin_sl3,LOW);
      digitalWrite(pin.pin_sl4,LOW);
    }
  }
  if ((tm != t) && (te != t)) {
    set_loopwork = 1;
  }
}

void tem_hu() {                     //fuction temperrature & humidity
  tem = dht.readTemperature();
  hu  = dht.readHumidity();
  if (isnan(tem)) {
    tem = 0;
  }
  if(isnan(hu)){
    hu = 0;
  }
  static int x = 0 ,y = 0;
  if(hu != x ){
    Firebase.setInt("control/Tem_Hu/hu",hu);
    x = hu;
    Serial.println("set hu");
  }
  if(tem != y){
    Firebase.setInt("control/Tem_Hu/tem",tem);
    y = tem;
    Serial.println("set tem");
  }
}
