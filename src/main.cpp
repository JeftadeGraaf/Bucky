// Slave

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>
#include <Wire.h>
#include <Serial_C.h>
#include <LSM9DS1.h>
#include <Ultrasonic.h>

Motor m1 (1, 2);
Motor m2 (22, 23);
Motor m3 (24, 25);

Lsm9ds1 gyro (300, -8.58);

Ultrasonic ultra_L (8, 9);
Ultrasonic ultra_R (39, 38);

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
  gyro.setup();
  gyro.magCalibrate();
  m1.setup();
  m2.setup();
  m3.setup();
}

int check_deg(int deg) { // last checks for degrees 
  if (deg == 90) {
   if (ultra_L.read() > ultra_R.read()) {
     deg *= -1;
   }
  }
  return deg;
}

void loop() {
  int deg = serial.receive().toInt();
  Serial.println(gyro.magCalculate());
  move(deg, 100);
}