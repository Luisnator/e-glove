#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <M5Stack.h>
#include <Arduino.h>
#include "gestureRecognition.h"
#include "bleHandler.h"
#include "flexSensor.h"
#include "DisplayHandler.h"

/*! \file stateMachine.h*/ 

/*! Enum for the diffrent modes*/
enum mode
{
    laserpointer, /*!< mode for laserpointer control */
    browser,      /*!< mode for browser control */
    multimedia,   /*!< mode for multimedia control */
    presentation  /*!< mode for presentation control */
};

/*! Enum for the diffrent keyboard functionalities*/
enum functions
{
    nextpage = 1,        /*!< Continue to the next slide */
    previouspage,        /*!< Go back to the previous slide */
    startpresentation,   /*!< Start a presentation */
    endpresentation,     /*!< End a presentation */
    nexttrack,           /*!< Continue to the next track */
    previoustrack,       /*!< Go back to the previous track */
    playpause,           /*!< Toogle play and pause */
    volumeup,            /*!< Turn the volume up */
    volumedown,          /*!< Turn the volume down */
    browsernextpage,     /*!< Continue to the next browser page */
    browserpreviouspage, /*!< Go Back to the previous browser page */
    scrollup,            /*!< Scroll up on a document or website */
    scrolldown           /*!< Scroll down on a document or website */
};
//!  Main class to simulate a statemachine and control the e-glove
/*!*/
class StateMachine
{
private:
    unsigned long previousMillis = 0;                                     /*!< Needed for interval control */
    const int long_pause = 800;                                           /*!< Minimal pause between swipe gestures */
    const int short_pause = 100;                                          /*!< Minimal pause between handroll gestures */
    const int no_pause = 0;                                               /*!< If no pause is needed */
    int w_interval = 0;                                                   /*!< Variable interval */
    const int laserpointer_pin = 26;                                      /*!< ESP32 laserpointer pin */
    const int flexsensor_pin = 36;                                        /*!< ESP32 flexsensor pin */
    const int scrollrepeat = 12;                                          /*!< Tells how often the scroll signal is send for better usability*/
    int state = 0;                                                        /*!< State of the statemachine */
    GestureRecognition &gr = GestureRecognition::getGestureRecognition(); /*!< Object that handles gesture recognition */
    BleHandler &bh = BleHandler::getBleHandler();                         /*!< Object that handles bluetooth signals */
    DisplayHandler &dh = DisplayHandler::getDisplayHandler();             /*!< Object that handles the m5stack display */
    FlexSensor &fs = FlexSensor::getFlexSensor();                         /*!< Object that handles the flex sensor */

public:
    //! Constructor for Statemachine class
    /*! */
    StateMachine();
    //! Change to the state given in the argument
    /*!
      \param state the new state
    */
    void changeState(int state);
    //! Main function should be called in a loop
    /*!*/
    void work();
    //! Initializes the needed components
    /*! */
    void init();
};
#endif