#include "gestureRecognition.h"

GestureRecognition &GestureRecognition::getGestureRecognition()
{
    static GestureRecognition gr;
    return gr;
}

GestureRecognition::GestureRecognition()
{

}
void GestureRecognition::init()
{
    Wire.begin();
    mpu.setup();
}
int GestureRecognition::getGesture()
{
    if (mpu.getGyro(0) < -100)
    {
        int time = millis();
        while(millis()-time < confirmtime)
        {}
        if(mpu.getGyro(0) < -100)
        {
            return UpSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(0) > 100)
    {
        int time = millis();
        while(millis()-time < confirmtime)
        {}
        if(mpu.getGyro(0) > 100)
        {
            return DownSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(2) < -100)
    {
        int time = millis();
        while(millis()-time < confirmtime)
        {}
        if(mpu.getGyro(2) < -100)
        {
            return LeftSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(2) > 100)
    {
        int time = millis();
        while(millis()-time < confirmtime)
        {}
        if(mpu.getGyro(2) > 100)
        {
            return RightSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getPitch() > 60)
    {
        return LeftRoll;
    }
    else if (mpu.getPitch() < -60)
    {
        return RightRoll;
    }
    else
    {
        return NONE;
    }
}

void GestureRecognition::updateMPU()
{
   mpu.update();
}