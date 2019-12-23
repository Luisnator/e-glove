#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H
#include <M5Stack.h>
#include <Arduino.h>
#include <MPU9250.h>
enum{NONE,LeftSwipe,RightSwipe,UpSwipe,DownSwipe,LeftRoll,RightRoll};
class GestureRecognition
{
    private:
    MPU9250 mpu;

    public:
    GestureRecognition();
    static GestureRecognition& getGestureRecognition();
    int getGesture();
    void updateMPU();
    void init();
};
#endif