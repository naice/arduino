#define DEBUG

#include <SonarSwitch.h>
#include <NewPing.h>
#include <RelaisSwitch.h>

//#define DEBUG 1
#define PIN_TRIG 3
#define PIN_ECHO 2
#define PIN_RELAIS 4
#define MAX_DIST 400 // maximum of 400 meters supported by sensor.

#define MEASUREMENT_THRESHOLD 7
#define MIN_DISTANCE 5
#define MAX_DISTANCE 20
#define SWITCH_DELAY 500


NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DIST); // NewPing
SonarSwitch sonarSwitch(MEASUREMENT_THRESHOLD, MIN_DISTANCE, MAX_DISTANCE);
RelaisSwitch relaisSwitch(PIN_RELAIS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned int distanceCM = sonar.ping_cm();
  bool isSwitched = sonarSwitch.Switch(distanceCM);

  if (millis() < 5000)
    return;

  if (isSwitched)
  {
    relaisSwitch.Toggle();
    delay(SWITCH_DELAY);
  }

  delay(5);
}