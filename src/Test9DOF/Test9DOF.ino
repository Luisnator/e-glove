#include "MPU9250.h"
#include <M5Stack.h>
MPU9250 mpu;
void setup()
{
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("Display Test!");
  Wire.begin();
  delay(2000);
  mpu.setup();
}

void loop()
{
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
  if (M5.BtnA.isPressed() && mpu.getGyro(0) < -100) {
    M5.Speaker.beep();
  }
  if (M5.BtnA.isPressed() && mpu.getGyro(0) > 100) {
    M5.Speaker.tone(100, 200);
  }
  if (M5.BtnA.isPressed() && mpu.getGyro(2) < -100) {
    M5.Speaker.tone(500, 200);
  }
  if (M5.BtnA.isPressed() && mpu.getGyro(2) > 100) {
    M5.Speaker.tone(300, 200);
  }
  if(mpu.getPitch() > 60){
    M5.Lcd.fillScreen(GREEN);
  }
  else if(mpu.getPitch() < -60)
  {
    M5.Lcd.fillScreen(RED);
  }
  else
  {
    M5.Lcd.fillScreen(BLACK);
  }
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(10);
  M5.Lcd.print(mpu.getGyro(0));
}
