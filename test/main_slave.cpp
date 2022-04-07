// Slave

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>
#include <Wire.h>
#include <Serial_C.h>
#include <Compass.h>

Motor m1 (1, 2);
Motor m2 (22, 23);
Motor m3 (24, 25);

Compass compass (0.038920842);

Serial_C serial (false);

void move(float degrees, int basespeed) {
  float pi = 57.29577951;
  float speedM1 = -(basespeed) * sin((degrees + 180) / pi);
  float speedM2 = -(basespeed) * sin((degrees + 60) / pi);
  float speedM3 = -(basespeed) * sin((degrees - 60) / pi);

  m1.move(speedM1);
  m2.move(speedM2);
  m3.move(speedM3);
}

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  serial.setup();
  compass.setup();
  compass.compassCalibrate(1000);
  m1.setup();
  m2.setup();
  m3.setup();
}

void loop() {
  float deg = serial.receive().toFloat();
  float heading = compass.compassCalculate(compass.compassRead());
  move(deg, 0);
}
