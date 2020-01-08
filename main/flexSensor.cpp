#include "flexsensor.h"
FlexSensor::FlexSensor(int pin, int accuracy)
{
    this->pin = pin;
    this->accuracy = accuracy;
    pinMode(pin,INPUT);
}
void FlexSensor::setAccuracy(int accuracy)
{
    this->accuracy = accuracy;
}
bool FlexSensor::isFlexed()
{
    if(analogRead(pin) < accuracy)
    {
        return true;
    }
    else
    {
        return false;
    }
}
FlexSensor &FlexSensor::getFlexSensor(int pin, int accuracy)
{
    static FlexSensor fs(pin,accuracy);
    return fs; 
}