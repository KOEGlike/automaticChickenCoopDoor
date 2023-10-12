#include "button.hpp"
#include <Arduino.h>
#include <functional>

Button::Button(int pin, std::function<void()> press, std::function<void()> longPress, bool* globalPressed) {
    m_pin = pin;
    m_globalPressed = globalPressed;
    m_longPress = longPress;
    m_press = press;
    //Serial.println("Button init");
    //delay(500);
    
   // asyncId=
   
}
Button::~Button() {
Async.deleteCallBack(asyncId);

}

void Button::begin() {
pinMode(m_pin, INPUT_PULLUP);

Serial.println("Button begiiin");
Async.registerCallback(0, -1, [&](){check();});
Serial.println("Button begin");
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

void ButtonManager::link(std::vector<Button*> buttons, std::function<void()> onPress, std::function<void()> onLongPress)
{

}

void ButtonManager::addButton(Button* button)
{
    
}

void ButtonManager::check() {

}

void ButtonManager::begin() {

}