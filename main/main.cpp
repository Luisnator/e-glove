#include <M5Stack.h>
#include <Arduino.h>
#include "modeSelector.h"
#include "stateMachine.h"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
StateMachine sm;
const int indexfinger = 2;
const int middlefinger = 5;
const int ringfinger = 16;
const int pinkyfinger = 17;
ModeSelector ms(indexfinger, middlefinger, ringfinger, pinkyfinger);
void index();
void middle();
void ring();
void pinky();
// The setup routine runs once when M5Stack starts up
void setup()
{
  //
  Serial.begin(115200);
  M5.begin();
  sm.init();
  // Initialize the M5Stack object

  //M5.Lcd.print("E-Glove!");
  ms.registerIndexFinger_CB(index);
  ms.registermiddleFinger_CB(middle);
  ms.registerringFinger_CB(ring);
  ms.registerpinkyfinger_CB(pinky);
}

// The loop routine runs over and over again forever
void loop()
{
  sm.work();
}

void index()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(presentation);
  }
}
void middle()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(multimedia);
  }
}

void ring()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(browser);
  }
}
void pinky()
{
  if (!FlexSensor::getFlexSensor().isFlexed())
  {
    sm.changeState(laserpointer);
  }
}

// The arduino task
void loopTask(void *pvParameters)
{
  setup();
  for (;;)
  {
    micros(); //update overflow
    loop();
  }
}

extern "C" void app_main()
{
  initArduino();
  xTaskCreatePinnedToCore(loopTask, "loopTask", 8192, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}
