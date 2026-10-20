#include "BleService.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLE2902.h>

namespace {
    constexpr const char* DEVICE_NAME              = "SNES-BT-Controller"; 
    constexpr const char* SERVICE_UUID             = "8b7e0001-5a9d-4c31-9f20-7d6a8e42b101"; 
    constexpr const char* STATE_CHARACTERISTIC_UUID = "8b7e0002-5a9d-4c31-9f20-7d6a8e42b101"; 
}

class ServerCallbacks : public BLEServerCallbacks {
public:
    explicit ServerCallbacks(BleService* owner) : owner(owner) {}

    void onConnect(BLEServer* server) override {
        owner->connected = true;
        Serial.println("[BLE] Cliente conectado."); 
    }

    void onDisconnect(BLEServer* server) override {
        owner->connected = false;
        Serial.println("[BLE] Cliente desconectado. Reiniciando advertising..."); 
        server->startAdvertising(); 
    }

private:
    BleService* owner;
};

void BleService::begin() {
    BLEDevice::init(DEVICE_NAME); 
    server = BLEDevice::createServer(); 
    server->setCallbacks(new ServerCallbacks(this)); 

    BLEService* service = server->createService(SERVICE_UUID); 
    stateCharacteristic = service->createCharacteristic( 
        STATE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY 
    );

    stateCharacteristic->addDescriptor(new BLE2902()); 

    const uint16_t initialState = 0xFFFF; 
    uint8_t data[2] = { uint8_t(initialState & 0xFF), uint8_t((initialState >> 8) & 0xFF) }; 
    stateCharacteristic->setValue(data, sizeof(data)); 

    service->start(); 

    BLEAdvertising* advertising = BLEDevice::getAdvertising(); 
    advertising->addServiceUUID(SERVICE_UUID); 
    advertising->setScanResponse(true); 
    advertising->setMinPreferred(0x06); 
    advertising->setMaxPreferred(0x12); 
    BLEDevice::startAdvertising(); 
}

void BleService::update(uint16_t state) {
    if (!connected || stateCharacteristic == nullptr) return; 
    uint8_t data[2] = { uint8_t(state & 0xFF), uint8_t((state >> 8) & 0xFF) }; 
    stateCharacteristic->setValue(data, sizeof(data)); 
    stateCharacteristic->notify(); 
}

bool BleService::isConnected() const {
    return connected; 
}