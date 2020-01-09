#include <M5Stack.h>
#include <Arduino.h>
#include "modeSelector.h"
#include "stateMachine.h"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/*! \file main.cpp */ 

StateMachine sm;                                                     /*!< create a statemachine object */
const int indexfinger = 2;                                           /*!< ESP32 pin for the indexfinger */
const int middlefinger = 5;                                          /*!< ESP32 pin for the middlefinger */
const int ringfinger = 16;                                           /*!< ESP32 pin for the ringfinger */
const int pinkyfinger = 17;                                          /*!< ESP32 pin for the pinkyfinger */
ModeSelector ms(indexfinger, middlefinger, ringfinger, pinkyfinger); /*!< create a modeselector object with the right pins attached */
void index();
void middle();
void ring();
void pinky();
//! First function to get called and initializes the programm */
void setup()
{
  Serial.begin(115200);
  M5.begin();
  sm.init();
  ms.registerIndexfinger_CB(index);
  ms.registerMiddlefinger_CB(middle);
  ms.registerRingfinger_CB(ring);
  ms.registerPinkyfinger_CB(pinky);
}
//! Main loop function
/*! */
void loop()
{
  sm.work();
}
//! Callbackfunction that changes the state to presentationmode if the indexfinger is pressed
/*! */
void index()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(presentation);
  }
}
//! Callbackfunction that changes the state to multimediamode if the middlefinger is pressed
/*! */
void middle()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(multimedia);
  }
}
//! Callbackfunction that changes the state to browsermode if the ringfinger is pressed
/*! */
void ring()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(browser);
  }
}
//! Callbackfunction that changes the state to laserpointermode if the pinkyfinger is pressed
/*! */
void pinky()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(laserpointer);
  }
}
//! Function to call setup once and loop in a loop
/*! */
void loopTask(void *pvParameters)
{
  setup();
  for (;;)
  {
    micros();
    loop();
  }
}

//! Free rtos task initalized
/*! */
extern "C" void app_main()
{
  initArduino();
  xTaskCreatePinnedToCore(loopTask, "loopTask", 8192, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}
