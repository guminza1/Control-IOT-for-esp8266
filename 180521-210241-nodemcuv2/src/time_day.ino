
#include <time.h>
String Day() {
  int timezone = 7 * 3600;                    //Time zone Thailand
  int dst = 0;                                // Date Swing Time
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(100);
  }
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  ctime(&now);
  char *a[] = {ctime(&now)};
  String j = String(j + *a);
  hour   = p_tm -> tm_hour;
  minute = p_tm -> tm_min;
  date   = p_tm -> tm_mday;
  return j;
}
