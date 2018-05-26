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
      set_loopwork = 0;
      Serial.println("morning working");
    }
  }

  String eve = Firebase.getString("/control/Switch/sw_time/sw_evening");
  if(eve == "\"on\""){
    String y = Firebase.getString("/control/set_time/te");
    String sub_y = y.substring(1,y.length()-1);
    te = sub_y.toInt();
    if (te == t && set_loopwork == 1) {
      set_loopwork = 0;
      Serial.println("evening working");
    }
  }
  if ((tm != t) && (te != t)) {
    set_loopwork = 1;
  }
}
