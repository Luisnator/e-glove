#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H
#include <M5Stack.h>
#include <Arduino.h>
#include <MPU9250.h>

/*! \file gestureRecognition.h */ 

/*! enum for different gestures */
enum gestures
{
    NONE,       /*!< no gesture */
    LeftSwipe,  /*!< swipe to the left */
    RightSwipe, /*!< swipe to the right */
    UpSwipe,    /*!< swipe upwards */
    DownSwipe,  /*!< swipe downwards */
    LeftRoll,   /*!< hand roll to the left */
    RightRoll   /*!< hand roll to the right */
};
//!  Class to handle the 9DOF and gesture recognition
/*!*/
class GestureRecognition
{
private:
    MPU9250 mpu;                          /*!< 9DOF sensor object */
    const int confirmtime = 300;          /*!< the time after the first gesture presumtion is confirmed */
    const int vertical_threshold = 150;   /*!< vertical accelerator threshold */
    const int horizontal_threshold = 100; /*!< horizontal accelerator threshold */
    const int leftpitch_threshold = 60;   /*!< left pitch threshold(handroll to the left) */
    const int rightpitch_threshold = 60;  /*!< right pitch threshold(handroll to the right) */
    const int z = 0;                      /*!< accelerator z index */
    const int x = 2;                      /*!< accelerator x index */

public:
    //! Constructor for GestureRecognition class
    /*! */
    GestureRecognition();
    //! Singelton-Pattern function to receive an object
    /*!
      \return Refrence to the GestureRecognition object
    */
    static GestureRecognition &getGestureRecognition();
    //! Recognize whether and which gesture is being made
    /*!
      \return The gesture code
    */
    int getGesture();
    //! Update the values of the 9DOF sensor
    /*!*/
    void updateMPU();
    //! Initializes the needed components
    /*! */
    void init();
};
#endif