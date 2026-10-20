#include "ButtonInput.h"
#include "BoardConfig.h"

void ButtonInput::begin() {
    pinMode(Board::BUTTON_B, INPUT_PULLUP);
    pinMode(Board::BUTTON_A, INPUT_PULLUP);
    pinMode(Board::BUTTON_X, INPUT_PULLUP);
    pinMode(Board::BUTTON_Y, INPUT_PULLUP);
    pinMode(Board::BUTTON_SELECT, INPUT_PULLUP);
    pinMode(Board::BUTTON_START, INPUT_PULLUP);
}

bool ButtonInput::isBPressed() const      { return digitalRead(Board::BUTTON_B) == LOW; }
bool ButtonInput::isAPressed() const      { return digitalRead(Board::BUTTON_A) == LOW; }
bool ButtonInput::isXPressed() const      { return digitalRead(Board::BUTTON_X) == LOW; }
bool ButtonInput::isYPressed() const      { return digitalRead(Board::BUTTON_Y) == LOW; }
bool ButtonInput::isSelectPressed() const { return digitalRead(Board::BUTTON_SELECT) == LOW; }
bool ButtonInput::isStartPressed() const  { return digitalRead(Board::BUTTON_START) == LOW; }