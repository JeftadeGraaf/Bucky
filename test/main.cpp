// Master

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>
#include <Wire.h>
#include <TSSP.h>
#include <Serial_C.h>
#include <LSM9DS1.h>

unsigned long time_ms = 0;
#define T_MODEA 833

int serialPrintAllPusleWidth(float *pulseWidth, sensorInfo_t *infop) {
  return infop->maxSensorNumber;
}

Serial_C serial (true);

const int degree_increase = 25.7142857143;

void setup() {
  Serial.begin(115200);
  setAllSensorPinsInput();
  serial.setup();
}

void loop () {
  float           pulseWidth[IR_NUM]; // パルス幅を格納する変数
  sensorInfo_t    sensorInfo; 

  sensorInfo = getAllSensorPulseWidth(pulseWidth, T_MODEA);

  if (millis() - time_ms > 50) {
    time_ms = millis();
    
    int value = serialPrintAllPusleWidth(pulseWidth, &sensorInfo);
    if (value == 1 or value == 13) {
      value = 0;
    }
    serial.send(String(get_motor_angle(value)));

    Serial.print(value);
    Serial.print("\n");
    }
}

/* 
0: ball is infront (drive forawrds)
1: ball is to the right (drivce to the right until 1)
2: ball is to the right, but under (drive down, until case 2)
3: ball is excactly behind the robot (drive to the left, or to the right depending on the ultrasone)
4: ball is to the left (drive to the left until 1)
5: ball is to the left, but under (drive down, until case 5)

*/



int get_motor_angle(int deg_ball) {
  int motor_deg;

  switch (deg_ball)
  {
  case -20 ... 20:
    motor_deg = (deg_ball + 180);
  case 21 ... 70:
    motor_deg = 90;
  case 71 ... 160:
    motor_deg = 180;
  case -160 ... -71:
    motor_deg = 180; 
  default: 
    motor_deg = 90;
  }
  return motor_deg;
}