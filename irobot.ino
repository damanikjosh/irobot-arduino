#include <SoftwareSerial.h>
#include "roomba.h"

#define CH2_PIN 10
#define CH2_MIN 1900
#define CH2_MAX 1100

#define CH4_PIN 9
#define CH4_MIN 1900
#define CH4_MAX 1100

#define WHEEL_BASE 0.26

#define SPEED_LINEAR_MIN -1000
#define SPEED_LINEAR_MAX 1000

#define SPEED_ANGULAR_MIN -1000 / WHEEL_BASE
#define SPEED_ANGULAR_MAX 1000 / WHEEL_BASE

int inByte = 0;

int speed_linear = 0;
int speed_angular = 0;
int track_right = 0;
int track_left = 0;

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {
  // put your setup code here, to run once:
  Roomba.begin(57600);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CH2_PIN, INPUT);
  pinMode(CH4_PIN, INPUT);

  delay(2000);

  startSafe();
}

void loop() {

  speed_linear = map(pulseIn(CH2_PIN, HIGH), CH2_MIN, CH2_MAX, SPEED_LINEAR_MIN, SPEED_LINEAR_MAX);
  speed_angular = map(pulseIn(CH4_PIN, HIGH), CH4_MIN, CH4_MAX, SPEED_ANGULAR_MIN, SPEED_ANGULAR_MAX);
  track_right = speed_linear - speed_angular * WHEEL_BASE / 2;
  track_left = speed_linear + speed_angular * WHEEL_BASE / 2;

  Serial.print(speed_linear);
  Serial.print(", ");
  Serial.print(speed_angular);
  Serial.print(", ");
  Serial.print(track_right);
  Serial.print(", ");
  Serial.println(track_left);
  drive(track_right, track_left);

}
