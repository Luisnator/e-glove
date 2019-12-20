#include "bluetooth.h"
BleHandler::BleHandler()
{

}
void BleHandler::setupBluetooth()
{
    M5.Lcd.println("BLE start.");
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
}

BleHandler& BleHandler::getBleHandler()
{
    static BleHandler bh;
    return bh;
}

// Maximum 1 Byte großer Integer-Wert
void BleHandler::sendInt(int val)
{
    if (deviceConnected)
    {
        M5.Lcd.println(val);
        pCharacteristic->setValue(val);
        pCharacteristic->notify();
    }
}
void BleHandler::onConnect(BLEServer *pServer)
{
    M5.Lcd.println("connect");
    deviceConnected = true;
}

void BleHandler::onDisconnect(BLEServer *pServer)
{
    M5.Lcd.println("disconnect");
    deviceConnected = false;
}
void BleHandler::onRead(BLECharacteristic *pCharacteristic)
{
    M5.Lcd.println("read");
    pCharacteristic->setValue("Hello World!");
}

void BleHandler::onWrite(BLECharacteristic *pCharacteristic)
{
    M5.Lcd.println("write");
    std::string value = pCharacteristic->getValue();
    M5.Lcd.println(value.c_str());
}