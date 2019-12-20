#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <M5Stack.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class BleHandler : public BLEServerCallbacks, public BLECharacteristicCallbacks
{
    private:
    BLEServer *pServer = NULL;
    BLECharacteristic *pCharacteristic = NULL;
    bool deviceConnected = false;
    BleHandler();
    public:
    void setupBluetooth();
    void sendInt(int val);
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
    void onRead(BLECharacteristic *pCharacteristic);
    void onWrite(BLECharacteristic *pCharacteristic);
    static BleHandler& getBleHandler();
};

#endif