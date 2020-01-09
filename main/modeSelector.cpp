#include "modeSelector.h"
ModeSelector::ModeSelector(const int pinIndex, const int pinMiddle, const int pinRing, const int pinPinky)
{
    pinMode(pinIndex, INPUT);
    pinMode(pinMiddle, INPUT);
    pinMode(pinRing, INPUT);
    pinMode(pinPinky, INPUT);
    this->pinIndex = pinIndex;
    this->pinMiddle = pinMiddle;
    this->pinRing = pinRing;
    this->pinPinky = pinPinky;
    indexfinger = NULL;
    middlefinger = NULL;
    ringfinger = NULL;
    pinkyfinger = NULL;
}
void ModeSelector::registerIndexfinger_CB(callback_function f)
{
    indexfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinIndex), indexfinger, RISING);
}
void ModeSelector::registerMiddlefinger_CB(callback_function f)
{
    middlefinger = f;
    attachInterrupt(digitalPinToInterrupt(pinMiddle), middlefinger, RISING);
}
void ModeSelector::registerRingfinger_CB(callback_function f)
{
    ringfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinRing), ringfinger, RISING);
}
void ModeSelector::registerPinkyfinger_CB(callback_function f)
{
    pinkyfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinPinky), pinkyfinger, RISING);
}
