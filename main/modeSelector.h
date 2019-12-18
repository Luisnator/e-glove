#ifndef MODESELECTOR_H
#define MODESELECTOR_H
#include <Arduino.h>
typedef void (*callback_function)(void);
class ModeSelector
{
private:
    callback_function indexfinger;
    callback_function middlefinger;
    callback_function ringfinger;
    callback_function pinkyfinger;
    int pinIndex;
    int pinMiddle;
    int pinRing;
    int pinPinky;
public:
    ModeSelector(const int pinIndex, const int pinMiddle, const int pinRing, const int pinPinky); 
    void registerIndexFinger_CB(callback_function f);
    void registermiddleFinger_CB(callback_function f);
    void registerringFinger_CB(callback_function f);
    void registerpinkyfinger_CB(callback_function f);
};
#endif