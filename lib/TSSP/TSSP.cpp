#include <Arduino.h>
#include <TSSP.h>


TSSP::TSSP(int pins[14]) {
    for (int i =0; i < TSSP::ir_num; i++) {
        TSSP::pins[i] = pins[i];
    }
}

void TSSP::setAllSensorPinsInput() {
    for (int i = 0; i < 14; i++) {
        pinMode(pins[i], INPUT);
    }
}

bool TSSP::getSensorPin(int pin) {
    return digitalRead(pins[pin]);
}

void TSSP::getAllSensorPulseWidth(float pulseWidth[14], int timeLimit) {
    for (int i = 0; i < ir_num; i++) {
        pulseWidth[i] = 0;
    }

    int startTime_us = micros();
    do {
        for (int i = 0; i < ir_num; i++) {
            if (getSensorPin(i) == false) {
                pulseWidth[i] += deltaPulseWidth;
            }
        }
    } while ((int(micros()) - startTime_us) < timeLimit);

    maxPulseWidth = 0;
    maxSensorNumber = 0;
    for (int i = 0; i < ir_num; i++) {
        if (pulseWidth[i] > 0) {
            activeSensors += 1;
        }
        if (pulseWidth[i] > maxPulseWidth) {
            maxPulseWidth = pulseWidth[i];
            maxSensorNumber = i;
        }
    }
}


