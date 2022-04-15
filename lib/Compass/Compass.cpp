#include <Arduino.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_Sensor.h>
#include <Compass.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

Compass::Compass(float DECLINATION)
{
    Compass::DECLINATION = DECLINATION;
}

void Compass::setup()
{

    if (!mag.begin())
    {
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while (1)
            ;
    }
}

float Compass::compassRead()
{
    sensors_event_t event;
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);

    return heading * 180 / M_PI;
}

void Compass::compassCalibrate(int n)
{
    float sum = 0.00;
    for (int i = 0; i <= n; i++)
    {
        sum += compassRead();
    }

    calibration = sum / n;
}

float Compass::compassCalculate(double heading)
{
    heading += DECLINATION;
    heading = correctDegrees(heading);

    
    heading = heading - calibration;

    heading = correctDegrees(heading);

    return heading;


}


float Compass::correctDegrees(double heading) {
    if (heading < -180) heading += 360;
    if (heading > 180) heading -= 360;

    return heading;
}