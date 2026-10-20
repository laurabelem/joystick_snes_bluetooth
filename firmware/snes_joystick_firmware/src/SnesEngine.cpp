#include "SnesEngine.h"
#include "BoardConfig.h"

void SnesEngine::begin() {
    pinMode(Board::SNES_LATCH, OUTPUT);
    pinMode(Board::SNES_CLOCK, OUTPUT);
    pinMode(Board::SNES_DATA, OUTPUT);
    digitalWrite(Board::SNES_LATCH, LOW); 
    digitalWrite(Board::SNES_CLOCK, LOW);
    digitalWrite(Board::SNES_DATA, HIGH); 
}

void SnesEngine::sendFrame(uint16_t state) {
    digitalWrite(Board::SNES_LATCH, HIGH);
    delayMicroseconds(12); 
    digitalWrite(Board::SNES_LATCH, LOW); 

    for (uint8_t bitIndex = 0; bitIndex < 16; ++bitIndex) { 
        sendBit((state >> bitIndex) & 0x01); 
    }
}

void SnesEngine::sendBit(uint8_t bit) {
    digitalWrite(Board::SNES_DATA, bit ? HIGH : LOW); 
    digitalWrite(Board::SNES_CLOCK, HIGH); 
    delayMicroseconds(6); 
    digitalWrite(Board::SNES_CLOCK, LOW);
    delayMicroseconds(6); 
}