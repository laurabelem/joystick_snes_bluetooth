#include <Arduino.h>
#include "InputManager.h"
#include "SnesEngine.h"
#include "BleService.h"

InputManager inputManager;
SnesEngine   snesEngine;
BleService   bleService;

void setup() {
    Serial.begin(115200);
    delay(500); 

    inputManager.begin();
    snesEngine.begin();
    bleService.begin();

    Serial.println("[Setup] Inicializacao concluida."); 
}

void loop() {
    const uint16_t state = inputManager.readState();

    snesEngine.sendFrame(state);
    bleService.update(state);

    delay(8);
}