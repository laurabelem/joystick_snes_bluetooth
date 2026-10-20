#pragma once
#include <Arduino.h>

class JoystickInput {
public:
    void begin();
    void update(bool& up, bool& down, bool& left, bool& right) const;
};              