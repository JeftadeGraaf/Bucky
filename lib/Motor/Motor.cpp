#include <Arduino.h>
#include <math.h>
#include <Motor.h>

Motor::Motor(int in1, int pwm, float speeddiff) {
    Motor::in1 = in1;
    Motor::pwm = pwm;
    Motor::speeddiff = speeddiff;
}
Motor::Motor(int in1, int pwm) {
    Motor::in1 = in1;
    Motor::pwm = pwm;
    Motor::speeddiff = 0;
}


void Motor::setup() {
    pinMode(in1, OUTPUT);
    pinMode(pwm, OUTPUT);
}

void Motor::move(float speed, float offset) {
    if(speed < -255 || speed > 255) {
        return;
    }
    if(speed < 0) {
        digitalWrite(in1, LOW);
        analogWrite(pwm, abs(speed + 30 + offset));
    }
    else {
        digitalWrite(in1, HIGH);
        analogWrite(pwm, abs(speed+speeddiff + 30 + offset));
    }
}

