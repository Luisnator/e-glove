#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <M5Stack.h>
#include <Arduino.h>
class FlexSensor
{
    private:
    int pin;
    int accuracy = 3000;

    public:
    FlexSensor(int pin,int accuracy = 3000);
    void setAccuracy(int accuracy = 3000);
    bool isFlexed();
};
#endif