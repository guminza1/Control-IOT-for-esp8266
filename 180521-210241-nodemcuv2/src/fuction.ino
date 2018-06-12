void work(){
  int te,tm;
  h_m = String(hour)+String(minute);
  t = h_m.toInt();

  String mor = Firebase.getString("/control/Switch/sw_time/sw_morning");
  if(mor == "\"on\""){
    String x = Firebase.getString("/control/set_time/tm");
    String sub_x = x.substring(1,x.length()-1);
    tm = sub_x.toInt();
    if (tm == t && set_loopwork == 1) {
      unit_Water();
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
      Firebase.setString("/control/Last_work/morning",Day());
    }
  }
  String eve = Firebase.getString("/control/Switch/sw_time/sw_evening");
  if(eve == "\"on\""){
    String y = Firebase.getString("/control/set_time/te");
    String sub_y = y.substring(1,y.length()-1);
    te = sub_y.toInt();
    if (te == t && set_loopwork == 1) {
      unit_Water();
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
      Firebase.setString("/control/Last_work/evening",Day());
    }
  }
  if ((tm != t) && (te != t)) {
    set_loopwork = 1;
  }
}

void tem_hu() {                     //fuction temperrature & humidity
  tem = dht.readTemperature();
  hu  = dht.readHumidity();
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["tem"] = tem;
  root["hu"] = hu;
  Firebase.set("control/Tem_Hu/",root);
}

void unit_Water(){
  String unit_water = Firebase.getString("/control/unit_water"); // get firebase  unit water (sec,minute,hour)
  String t_water = Firebase.getString("/control/water");         // get firebase time working
  String t_water1 = t_water.substring(1,t_water1.length()-1);    // sub string time working
  delay_w = t_water1.toInt();                                    // timer work sl(pump)
  if (unit_water == "\"s\"") {
    delay_w *= 1000;
  }
  if(unit_water == "\"m\""){
    delay_w *= 60000;
  }
  if(unit_water == "\"h\""){
    delay_w *= 3600000;
  }
}
