#include <M5Stack.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "bluetooth.h"

void setup() {
  Serial.begin(115200);
  M5.begin();
  Wire.begin();
  m5.Speaker.mute();
  //M5.setWakeupButton(BUTTON_A_PIN);
  setupBluetooth();
  Serial.println("Setup complete.");
}

void loop() {
  if(M5.BtnA.wasPressed()) {
    Serial.println("btnA pressed");
    sendInt(12);
  }
  if(M5.BtnB.wasPressed()) {
    Serial.println("btnB pressed");
    sendInt(13);
  }
  if(M5.BtnC.wasPressed()) {
    Serial.println("btnC pressed");
    sendInt(6);
  }

  M5.update();
  //testfun();
}