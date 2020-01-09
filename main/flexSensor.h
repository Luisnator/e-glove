#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <M5Stack.h>
#include <Arduino.h>

/*! \file flexSensor.h*/

//!  Class to handle the state of the flexsensor
/*!*/
class FlexSensor
{
private:
    int pin;             /*!< ESP32 pin of the flexsensor */
    int accuracy = 2850; /*!< threshold after the function isFlexed returns true */
    //! Constructor for FlexSensor class
    /*!
      \param pin ESP32 pin of the flexsensor
      \param accuracy threshold after the function isFlexed returns true
    */
    FlexSensor(int pin, int accuracy);

public:
    //! Singelton-Pattern function to receive an object
    /*!
      \param pin ESP32 pin of the flexsensor
      \param accuracy threshold after the function isFlexed returns true 
      \return refrence to the FlexSensor object
    */
    static FlexSensor &getFlexSensor(int pin = 36, int accuracy = 2850);
    //! Adjust the accuracy of the flexsensor
    /*!
      \param accuracy threshold after the function isFlexed returns true 
    */
    void setAccuracy(int accuracy = 2850);
    //! Tells if the flexsensor is flexed
    /*!
      \return true if flexed false if not
    */
    bool isFlexed();
};
#endif