#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <M5Stack.h>
#include <Arduino.h>
#include "gestureRecognition.h"
#include "bleHandler.h"
#include "flexSensor.h"
#include "DisplayHandler.h"
enum{laserpointer,browser,multimedia,presentation};
enum{nextpage=1,previouspage,startpresentation,endpresentation,nexttrack,previoustrack,playpause,volumeup,volumedown,browsernextpage,browserpreviouspage,scrollup,scrolldown};
class StateMachine
{
    private:
    unsigned long previousMillis = 0;
    const int long_pause = 800;
    const int short_pause = 100;
    const int no_pause = 0; 
    int w_interval = 0;

    const int laserpointer_pin = 26;
    const int flexsensor_pin = 36;
    const int scrollrepeat = 12; 
    int state = 0;
    GestureRecognition &gr = GestureRecognition::getGestureRecognition();
    BleHandler &bh = BleHandler::getBleHandler();
    DisplayHandler &dh = DisplayHandler::getDisplayHandler();
    FlexSensor &fs = FlexSensor::getFlexSensor();

    public:
    StateMachine();
    void changeState(int state);
    void work();
    void init();
};
#endif