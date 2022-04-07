// Master

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>
#include <Wire.h>
#include <TSSP.h>
#include <Serial_C.h>


unsigned long time_ms = 0;
#define T_MODEA 833


int pin[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
TSSP ir_sens (pin);


Serial_C serial (true);

const int degree_increase = 25.7142857143;

void setup() {
  Serial.begin(115200);
  ir_sens.setAllSensorPinsInput();
  serial.setup();
}

void loop () {
  float           pulseWidth[14]; // パルス幅を格納する変数

  ir_sens.getAllSensorPulseWidth(pulseWidth, T_MODEA);

  Serial.println(ir_sens.maxSensorNumber);
  
}
