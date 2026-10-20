#pragma once
#include <Arduino.h>

namespace Board {
    // digital pins
    constexpr uint8_t BUTTON_B      = 4;   
    constexpr uint8_t BUTTON_A      = 16; 
    constexpr uint8_t BUTTON_X      = 17;  
    constexpr uint8_t BUTTON_Y      = 5;   
    constexpr uint8_t BUTTON_SELECT = 13;  
    constexpr uint8_t BUTTON_START  = 14;  

    // analoogic pins
    constexpr uint8_t ANALOG_VRX    = 34; 
    constexpr uint8_t ANALOG_VRY    = 35;  

    constexpr int THRESHOLD_LOW     = 1200; 
    constexpr int THRESHOLD_HIGH    = 2900; 

    // snes wire
    constexpr uint8_t SNES_LATCH    = 18;  
    constexpr uint8_t SNES_CLOCK    = 19; 
    constexpr uint8_t SNES_DATA     = 23;  
}