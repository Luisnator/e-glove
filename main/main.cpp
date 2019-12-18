#include <M5Stack.h>
#include <Arduino.h>
#include <MPU9250.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "bluetooth.h"
#include "modeSelector.h"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
const int indexfinger = 2;
const int middlefinger = 5;
const int ringfinger = 17;
const int pinkyfinger = 16;
const int laserpointer = 19;

MPU9250 mpu;
ModeSelector ms(indexfinger,middlefinger,ringfinger,pinkyfinger);
void testPrint();
void testPrint1();
void testPrint2();
void testPrint3();
// The setup routine runs once when M5Stack starts up
void setup()
{

  //
  Serial.begin(115200);
  // Initialize the M5Stack object
  M5.begin();
  Wire.begin();
  mpu.setup();
  // LCD display
  M5.Lcd.print("Hello World");
  setupBluetooth();
  ms.registerIndexFinger_CB(testPrint);
  ms.registermiddleFinger_CB(testPrint1);
  ms.registerringFinger_CB(testPrint2);
  ms.registerpinkyfinger_CB(testPrint3);
  pinMode(laserpointer,OUTPUT);
  digitalWrite(laserpointer,LOW);
}

// The loop routine runs over and over again forever
void loop()
{
  if (M5.BtnA.wasPressed())
  {
    //Serial.println("btnA pressed");
    sendInt(7);
  }
  if (M5.BtnB.wasPressed())
  {
    Serial.println("btnB pressed");
    sendInt(8);
  }
  if (M5.BtnC.wasPressed())
  {
    Serial.println("btnC pressed");
    sendInt(9);
  }
  M5.update();
}

void testPrint()
{
  Serial.println("ICH WURDE AUSGELÖST!!");
  digitalWrite(laserpointer,HIGH);
}
void testPrint1()
{
  Serial.println("ICH WURDE AUSGELÖST1111!!");
  digitalWrite(laserpointer,LOW);
}
void testPrint2()
{
  Serial.println("ICH WURDE AUSGELÖST2222!!");
}
void testPrint3()
{
  Serial.println("ICH WURDE AUSGELÖST3333!!");
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
