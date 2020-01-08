#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <M5Stack.h>
#include <Arduino.h>
class FlexSensor
{
    private:
    int pin;
    int accuracy = 3000;
    FlexSensor(int pin,int accuracy);

    public:
    static FlexSensor& getFlexSensor(int pin=36,int accuracy=2850);
    void setAccuracy(int accuracy = 2850);
    bool isFlexed();
};
#endif