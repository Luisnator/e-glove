#include <M5Stack.h>
#include <Arduino.h>
#include <MPU9250.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "bluetooth.h"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

MPU9250 mpu;
// The setup routine runs once when M5Stack starts up
void setup(){

	//
	Serial.begin(115200);
  // Initialize the M5Stack object
  M5.begin();
    Wire.begin();
	 mpu.setup();
  // LCD display
  M5.Lcd.print("Hello World");
    setupBluetooth();
}

// The loop routine runs over and over again forever
void loop() {
  if(M5.BtnA.wasPressed()) {
    Serial.println("btnA pressed");
    sendInt(7);
  }
  if(M5.BtnB.wasPressed()) {
    Serial.println("btnB pressed");
    sendInt(8);
  }
  if(M5.BtnC.wasPressed()) {
    Serial.println("btnC pressed");
    sendInt(9);
  }
  M5.update();
	
}

// The arduino task
void loopTask(void *pvParameters)
{
    setup();
    for(;;) {
        micros(); //update overflow
        loop();
    }
}

extern "C" void app_main()
{
    initArduino();
    xTaskCreatePinnedToCore(loopTask, "loopTask", 8192, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}
