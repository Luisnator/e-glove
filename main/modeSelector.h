#ifndef MODESELECTOR_H
#define MODESELECTOR_H
#include <Arduino.h>

/*! \file modeSelector.h*/ 

typedef void (*callback_function)(void);
//!  Class to handle the input of the capacitive sensors and call callbackfunctions accordingly
/*!*/
class ModeSelector
{
private:
    callback_function indexfinger;  /*!< Callbackfunction when the indexfinger is pressed */
    callback_function middlefinger; /*!< Callbackfunction when the middlefinger is pressed */
    callback_function ringfinger;   /*!< Callbackfunction when the ringfinger is pressed */
    callback_function pinkyfinger;  /*!< Callbackfunction when the pinkyfinger is pressed */
    int pinIndex;                   /*!< ESP32 pin for the indexfinger */
    int pinMiddle;                  /*!< ESP32 pin for the middelfinger */
    int pinRing;                    /*!< ESP32 pin for the ringfinger */
    int pinPinky;                   /*!< ESP32 pin for the pinkyfinger */

public:
    //! Constructor for ModeSelector class
    /*!
      \param pinIndex ESP32 pin for the indexfinger
      \param pinMiddle ESP32 pin for the middelfinger
      \param pinRing ESP32 pin for the ringfinger
      \param pinPinky ESP32 pin for the pinkyfinger
    */
    ModeSelector(const int pinIndex, const int pinMiddle, const int pinRing, const int pinPinky);
    //! Register a callbackfunction for the indexfinger 
    /*!
      \param f a callbackfunction
    */
    void registerIndexfinger_CB(callback_function f);
    //! Register a callbackfunction for the middlefinger 
    /*!
      \param f a callbackfunction
    */
    void registerMiddlefinger_CB(callback_function f);
    //! Register a callbackfunction for the ringfinger 
    /*!
      \param f a callbackfunction
    */
    void registerRingfinger_CB(callback_function f);
    //! Register a callbackfunction for the pinkyfinger 
    /*!
      \param f a callbackfunction
    */
    void registerPinkyfinger_CB(callback_function f);
};
#endif