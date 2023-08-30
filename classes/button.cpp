#include "button.hpp"
#include <Arduino.h>

Button::Button(int pin, bool* globalPressed, std::function<void()> press, std::function<void()> longPress) {
    _pin = pin;
    _globalPressed = globalPressed;
    _longPress = longPress;
    _press = press;
    pinMode(_pin, INPUT_PULLUP);
}

void Button::check() {
    if (digitalRead(_pin) == HIGH) {
        if (pressed == true) {
            pressedForMillis = millis() - pressStartInMillies;
        }
        pressed = false;
        *_globalPressed = false;
    } else {
        if (pressed == false) {
            pressStartInMillies = millis();
        }
        if (*_globalPressed == false) {
            pressed = true;
            *_globalPressed = true;
        }
    }

    if (pressed == false && *_globalPressed == false && pressedForMillis >= debounceInMillis) {
        if (pressedForMillis < millisForLongPress) {
            _press();
        } else {
            _longPress();
        }
    }

    if (pressed == false) {
        pressedForMillis = 0;
    }
}