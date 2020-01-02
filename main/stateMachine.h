#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <M5Stack.h>
#include <Arduino.h>
#include "gestureRecognition.h"
#include "bluetooth.h"
#include "flexSensor.h"
enum{laserpointer,browser,multimedia,presentation};
enum{nextpage=1,previouspage,startpresentation,endpresentation,nexttrack,previoustrack,playpause,volumeup,volumedown,browsernextpage,browserpreviouspage,scrollup,scrolldown};
class StateMachine
{
    private:
    unsigned long previousMillis = 0;
    const long interval = 500;
    int w_interval = 0;
    const int laserpointer_pin = 26; 
    int state = 0;
    GestureRecognition &gr = GestureRecognition::getGestureRecognition();
    BleHandler &bh = BleHandler::getBleHandler();
    FlexSensor fs = FlexSensor(36,3000);

    public:
    StateMachine();
    void changeState(int state);
    void work();
    void init();
};
#endif