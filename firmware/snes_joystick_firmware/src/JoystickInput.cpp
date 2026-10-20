#include "JoystickInput.h"
#include "BoardConfig.h"

void JoystickInput::begin() {
    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);
    pinMode(Board::ANALOG_VRX, INPUT);
    pinMode(Board::ANALOG_VRY, INPUT);
}

void JoystickInput::update(bool& up, bool& down, bool& left, bool& right) const {
    int rawX = analogRead(Board::ANALOG_VRX);
    int rawY = analogRead(Board::ANALOG_VRY);

    up    = true;
    down  = true;
    left  = true;
    right = true;

    if (rawY < Board::THRESHOLD_LOW)       up = false;
    else if (rawY > Board::THRESHOLD_HIGH) down = false;

    if (rawX < Board::THRESHOLD_LOW)       left = false;
    else if (rawX > Board::THRESHOLD_HIGH) right = false;

    if (!up && !down) {
        up = true;
        down = true;
    }
    if (!left && !right) {
        left = true;
        right = true;
    }
}