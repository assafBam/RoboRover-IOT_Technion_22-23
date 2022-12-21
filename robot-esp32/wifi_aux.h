#ifndef WIFI_AUX__H__
#define WIFI_AUX__H__

#include <WiFi.h>

extern int gpLed;

namespace wifi{
 void init(const char* ssid, const char* password){
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(gpLed, HIGH);
    delay(500);
    Serial.print(".");
    digitalWrite(gpLed, LOW);
    delay(500);
      }
  Serial.println("");
  Serial.print("WiFi: connected to network ");
  Serial.println(ssid);
 }

}

#endif