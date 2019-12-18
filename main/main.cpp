#include <M5Stack.h>
#include <Arduino.h>
#include <MPU9250.h>
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
}

// The loop routine runs over and over again forever
void loop() {

  M5.update();
      static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        mpu.print();

        Serial.print("roll  (x-forward (north)) : ");
        Serial.println(mpu.getRoll());
        Serial.print("pitch (y-right (east))    : ");
        Serial.println(mpu.getPitch());
        Serial.print("yaw   (z-down (down))     : ");
        Serial.println(mpu.getYaw());

        prev_ms = millis();
    }
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
