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
    const int confirmtime = 300;
    const int vertical_threshold = 100;
    const int horizontal_threshold = 100;
    const int leftpitch_threshold = 60;
    const int rightpitch_threshold = 60;
    const int z = 0;
    const int x = 2;

    public:
    GestureRecognition();
    static GestureRecognition& getGestureRecognition();
    int getGesture();
    void updateMPU();
    void init();
};
#endif