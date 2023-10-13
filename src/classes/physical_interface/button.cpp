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
        pressed = false;
        *m_globalPressed = false;
    } else {
        pressedForMillis = millis() - pressStartInMillies;
        if (pressed == false&&wasHighBefore) {
            pressStartInMillies = millis();
            pressedForMillis=0;
            pressed = true;
        }

        /*if (*m_globalPressed == false) {
            pressed = true;
            *m_globalPressed = true;
        }*/
    }

    if ( pressedForMillis >= debounceInMillis) {
        if (pressedForMillis < millisForLongPress&&pressed==false) { 
            m_press();
            Serial.println("m_press");
        } else if(pressed == true&&pressedForMillis >= millisForLongPress){
            m_longPress();
            pressed = false;
            Serial.println("m_longPress");
        }
    }

    if (pressed == false) {
        pressedForMillis = 0;
    }

    wasHighBefore=digitalRead(m_pin)==HIGH?true:false;
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