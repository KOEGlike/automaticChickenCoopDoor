#include "button.hpp"
#include <Arduino.h>
#include <functional>

Button::Button(int pin, std::function<void()> press, std::function<void()> longPress, bool* globalPressed) {
    m_pin = pin;
    m_globalPressed = globalPressed;
    m_longPress = longPress;
    m_press = press;
    pinMode(m_pin, INPUT_PULLUP);
    Serial.println("Button init");
    std::function<void()> check = std::bind(&Button::check, this);
   asyncId=
   Async.registerCallback(0, -1, check);
}
Button::~Button() {
Async.deleteCallBack(asyncId);
}

void Button::check() {
    //Serial.println("check");
    if (digitalRead(m_pin) == HIGH) {
        if (pressed == true) {
            pressedForMillis = millis() - pressStartInMillies;
        }
        pressed = false;
        *m_globalPressed = false;
    } else {
        if (pressed == false) {
            pressStartInMillies = millis();
        }
        if (*m_globalPressed == false) {
            pressed = true;
            *m_globalPressed = true;
        }
    }

    if (pressed == false && *m_globalPressed == false && pressedForMillis >= debounceInMillis) {
        if (pressedForMillis < millisForLongPress) {
            m_press();
             Serial.println("m_press");
        } else {
            m_longPress();
             Serial.println("m_longPress");
        }
    }

    if (pressed == false) {
        pressedForMillis = 0;
    }
}