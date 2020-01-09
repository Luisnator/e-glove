#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <M5Stack.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

/*! \file bleHandler.h*/ 

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
//!  Class to handle the communication via bluetooth
/*!*/
class BleHandler : public BLEServerCallbacks, public BLECharacteristicCallbacks
{
private:
    BLEServer *pServer = NULL;                 /*!< Bluetooth server the target computer will connect to */
    BLECharacteristic *pCharacteristic = NULL; /*!< Characteristic where the data is stored in*/
    bool deviceConnected = false;              /*!< boolean wether the device is connected or not*/
    //! Constructor for BleHandler class
    /*!*/
    BleHandler();

public:
    //! Configure all the necessary bluetooth settings
    /*!*/
    void setupBluetooth();
    //! Sends an integer code to the target computer
    /*!
      \param val an integer code for the computer to interpret
    */
    void sendInt(int val);
    //! Callbackfunction for when a connection is established
    /*!
      \param pServer pointer to the server object
    */
    void onConnect(BLEServer *pServer);
    //! Callbackfunction for when a connection is canceled
    /*!
      \param pServer pointer to the server object
    */
    void onDisconnect(BLEServer *pServer);
    //! Callbackfunction for when the characteristic is read
    /*!
      \param pCharacteristic pointer to the characteristic object
    */
    void onRead(BLECharacteristic *pCharacteristic);
    //! Callbackfunction for when the caracteristic is written to 
    /*!
      \param pCharacteristic pointer to the characteristic object
    */
    void onWrite(BLECharacteristic *pCharacteristic);
    //! Singelton-Pattern function to receive an object
    /*!
      \return Refrence to the BleHandler object
    */
    static BleHandler &getBleHandler();
};

#endif