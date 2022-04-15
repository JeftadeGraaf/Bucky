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

Compass compass(2.14);

Serial_C serial (false);

void move(float degrees, int basespeed, double offset) {
  float pi = 57.29577951; // 1: 240, 2: 120, 3: 0
  // float speedM1 = (cos((120-degrees) * pi)*basespeed);
  // Serial.print("motor 1: ");
  // Serial.println(speedM1);
  // float speedM2 = (cos((240-degrees) * pi)*basespeed);
  // Serial.print("motor 2: ");
  // Serial.println(speedM2);
  // float speedM3 = (cos((0-degrees) * pi)*basespeed);
  // Serial.print("motor 3: ");
  // Serial.println(speedM3);

  float speedM1 = -(basespeed) * sin((degrees + 180) / pi) + offset;
  float speedM2 = -(basespeed) * sin((degrees + 60) / pi) + offset;
  float speedM3 = -(basespeed) * sin((degrees - 60) / pi) + offset;

  m1.move(speedM1, offset);
  m2.move(speedM2, offset);
  m3.move(speedM3, offset);
}

void setup() {
  Serial.begin(115200);
  serial.setup();
  compass.setup();
  compass.compassCalibrate(1000);
  m1.setup();
  m2.setup();
  m3.setup();
}

void loop() {
  float IR_deg = serial.receive().toFloat();
  double deg = compass.compassRead();
  deg = compass.compassCalculate(deg);
  Serial.println(deg);
  move(IR_deg, 100, deg);
}
