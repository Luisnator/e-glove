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
    if (mpu.getGyro(z) < -vertical_threshold)
    {
        int time = millis();
        while (millis() - time < confirmtime)
        {
        }
        if (mpu.getGyro(z) < -vertical_threshold)
        {
            return DownSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(z) > vertical_threshold)
    {
        int time = millis();
        while (millis() - time < confirmtime)
        {
        }
        if (mpu.getGyro(z) > vertical_threshold)
        {
            return UpSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(x) < -horizontal_threshold)
    {
        int time = millis();
        while (millis() - time < confirmtime)
        {
        }
        if (mpu.getGyro(x) < -horizontal_threshold)
        {
            return RightSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getGyro(x) > horizontal_threshold)
    {
        int time = millis();
        while (millis() - time < confirmtime)
        {
        }
        if (mpu.getGyro(x) > horizontal_threshold)
        {
            return LeftSwipe;
        }
        else
        {
            return getGesture();
        }
    }
    else if (mpu.getPitch() > leftpitch_threshold)
    {
        return LeftRoll;
    }
    else if (mpu.getPitch() < -rightpitch_threshold)
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