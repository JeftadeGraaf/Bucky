// Master

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>
#include <Wire.h>
#include <TSSP2.h>
#include <Serial_C.h>
#include <Compass.h>

int IR_pins[14] = {17, 16, 14, 40, 38, 39, 41, 15, 18, 24, 26, 27, 25, 19};

TSSP2 IR(IR_pins);

Serial_C serial (true);

const int degree_increase = 25.7142857143;

void setup() {
  Serial.begin(115200);
  serial.setup();
  IR.setAllSensorPinsInput();
}

void loop () {
  IR.getAllSensorPulseWidth(833);
  IR.calcVector();
  IR.calcRTfromXY();
  Serial.println(IR.IRInfo_theta);
  serial.send(IR.IRInfo_theta);
}
