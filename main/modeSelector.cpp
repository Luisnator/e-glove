#include "modeSelector.h"
void blub(){
    Serial.println("BLUB");
}
ModeSelector::ModeSelector(const int pinIndex, const int pinMiddle, const int pinRing, const int pinPinky){
    pinMode(pinIndex,INPUT);
    pinMode(pinMiddle,INPUT);
    pinMode(pinRing,INPUT);
    pinMode(pinPinky,INPUT);
    this->pinIndex = pinIndex;
    this->pinMiddle = pinMiddle;
    this->pinRing = pinRing;
    this->pinPinky = pinPinky;
}
void ModeSelector::registerIndexFinger_CB(callback_function f){
    indexfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinIndex),indexfinger,RISING);
}
void ModeSelector::registermiddleFinger_CB(callback_function f){
    middlefinger = f;
    attachInterrupt(digitalPinToInterrupt(pinMiddle),middlefinger,RISING);
}
void ModeSelector::registerringFinger_CB(callback_function f){
    ringfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinRing),ringfinger,RISING);
}
void ModeSelector::registerpinkyfinger_CB(callback_function f){
    pinkyfinger = f;
    attachInterrupt(digitalPinToInterrupt(pinPinky),pinkyfinger,RISING);
}
