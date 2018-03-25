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
#include <Servo.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Puppet Guest";
const char* password =  "argon4949";
Servo plantservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo mirrorServo;  

int sunlighttime = 0;
int passtime = 0;
int photocellPin = 17;     // the cell and 10K pulldown are connected to a0
int photocellReading = 0;     // the analog reading from the analog resistor divider


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

    plantservo.attach(2);  // attaches the servo on GIO2 to the servo object
    mirrorServo.attach(15);

    if((WiFiMulti.run() == WL_CONNECTED)) {
 
    HTTPClient http;
    
    http.begin("https://openwhisk.ng.bluemix.net/api/v1/web/jkl.lipton%40gmail.com_dev/hackathon/plant-sun.json?plant=origamiTree", "41 1E 4E 54 59 45 68 A7 AC E5 C5 AD BD 54 BA 71 BA C5 D0 A3"); //Specify the URL and certificate
    int httpCode = http.GET();

    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        StaticJsonBuffer<200> jsonBuffer; //ArduinoJson uses a memory pool, use Json buffer to create a 200-byte pool in the stack
        JsonObject& root = jsonBuffer.parseObject(payload);
        String sunlightValue = root["sun"];
        sunlighttime = sunlightTime(sunlightValue);
      } else {
          USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

    http.end(); //Free the resources
  }
    
}

void loop() {
  while (passtime != sunlighttime)
  {
    photocellReading = analogRead(photocellPin);

    if (passtime == 0) {
      mirrorRotationOne();
    }
    
    if (sunlighttime >= passtime) {
      plantrotation();
      passtime += 1;
    }
    
    if (photocellReading < 10) {
      passtime -= 3;
    }
    
    else if (photocellReading < 200) {
      passtime -= 2;
    }
    
    else if (photocellReading < 500) {
      passtime -= 1;
    }
    
    if (passtime <= 0) {
      passtime = 1;
    }

    if (passtime == sunlighttime) {
      mirrorRotationTwo();
    }

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

void mirrorRotationOne()
{
  int pos;

  for (pos = 0; pos <= 180; pos += 1) // goes from 180 degrees to 0 degrees
  {
    mirrorServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}

void mirrorRotationTwo()
{
  int pos;

  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    mirrorServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}

void plantrotation()
{
  int pos;

  for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    plantservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    plantservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
}
