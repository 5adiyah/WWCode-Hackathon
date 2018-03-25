#include <Servo.h>

Servo plantservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int sunlighttime = 5;
int passtime = 0;
int photocellPin = 17;     // the cell and 10K pulldown are connected to a0
int photocellReading = 0;     // the analog reading from the analog resistor divider


void setup()
{
  plantservo.attach(2);  // attaches the servo on GIO2 to the servo object
  Serial.begin(115200);
}

void loop()
{
  
  Serial.println("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
  
  while (passtime != sunlighttime)
  {
    photocellReading = analogRead(photocellPin);
    if (sunlighttime >= passtime) {
      plantrotation();
      passtime += 1;
    }
    if (photocellReading < 10) {
      Serial.println(" - Dark");
      passtime -= 3;
    }
    else if (photocellReading < 200) {
      Serial.println(" - Dim");
      passtime -= 2;
    }
    else if (photocellReading < 500) {
      Serial.println(" - Light");
      passtime -= 1;
    }
    Serial.println(passtime);
    if (passtime <= 0) {
      passtime = 1;
    }

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

