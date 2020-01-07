#include "bleHandler.h"
BleHandler::BleHandler()
{
}
void BleHandler::setupBluetooth()
{
    static int flag = 0;
    if (!flag)
    {
        BLEDevice::init("E-Glove");
        BLEServer *pServer = BLEDevice::createServer();
        pServer->setCallbacks(this);
        BLEService *pService = pServer->createService(SERVICE_UUID);
        pCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_WRITE |
                BLECharacteristic::PROPERTY_NOTIFY |
                BLECharacteristic::PROPERTY_INDICATE);
        pCharacteristic->setCallbacks(this);
        pCharacteristic->addDescriptor(new BLE2902());

        pService->start();
        BLEAdvertising *pAdvertising = pServer->getAdvertising();
        pAdvertising->start();
        flag = 1;
    }
}

BleHandler &BleHandler::getBleHandler()
{
    static BleHandler bh;
    return bh;
}

// Maximum 1 Byte großer Integer-Wert
void BleHandler::sendInt(int val)
{
    if (deviceConnected)
    {
        pCharacteristic->setValue(val);
        pCharacteristic->notify();
    }
}
void BleHandler::onConnect(BLEServer *pServer)
{
    //connect
    deviceConnected = true;
}

void BleHandler::onDisconnect(BLEServer *pServer)
{
    //disconnect
    deviceConnected = false;
}
void BleHandler::onRead(BLECharacteristic *pCharacteristic)
{
}

void BleHandler::onWrite(BLECharacteristic *pCharacteristic)
{
}