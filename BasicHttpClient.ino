/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Puppet Guest";
const char* password =  "argon4949";

void setup() {

     USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Puppet Guest", "argon4949");
    
}

void loop() {
  if((WiFiMulti.run() == WL_CONNECTED)) {
 
    HTTPClient http;
    
    http.begin("https://openwhisk.ng.bluemix.net/api/v1/web/jkl.lipton%40gmail.com_dev/hackathon/plant-sun.json?plant=origamiTree", "41 1E 4E 54 59 45 68 A7 AC E5 C5 AD BD 54 BA 71 BA C5 D0 A3"); //Specify the URL and certificate
    int httpCode = http.GET();

    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        StaticJsonBuffer<200> jsonBuffer; //ArduinoJson uses a memory pool, use Json buffer to create a 200-byte pool in the stack
        JsonObject& root = jsonBuffer.parseObject(payload);
        String sunlightValue = root["sun"];
        sunlightTime(sunlightValue);
      } else {
          USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

    http.end(); //Free the resources
  }
 
  delay(10000);
}

int sunlightTime(String sunlightValue) {
  if (sunlightValue == "full sun"){
    Serial.println("12");
    return 12;
  } else if (sunlightValue == "semi-shade"){
    Serial.println("6");
    return 6;
  } else {
    Serial.println("0");
    return 0;
  }
}
