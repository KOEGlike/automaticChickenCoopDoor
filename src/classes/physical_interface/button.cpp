#include "button.hpp"
#include <Arduino.h>
#include <functional>

Button::Button(int pin, std::function<void()> press, std::function<void()> longPress, bool* globalPressed) {
    m_pin = pin;
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
    //Async.registerCallback(0, -1, [&](){check();});
    ButtonManager.addButton(this);
}



ButtonManager_t::~ButtonManager_t() 
{
    Async.deleteCallBack(asyncId);
}

void ButtonManager_t::begin() 
{
    asyncId = Async.registerCallback(0, -1, [&](){check();});
}

void ButtonManager_t::link(std::vector<Button*> buttons, std::function<void()> onPress, std::function<void()> onLongPress)
{
    buttonLinks[currentMaxLinkId] = ButtonLinkStruct{std::vector<Button*>(buttons), onPress, onLongPress};
    currentMaxLinkId++;
}

void ButtonManager_t::addButton(Button* button)
{
    buttons[currentMaxButtonId] = button;
    currentMaxButtonId++;
}

void ButtonManager_t::check() 
{
    for(const auto &buttonEle :buttons)
    {
        bool pinIsHigh=digitalRead(buttonEle.second->m_pin)==HIGH?true:false;
        if (pinIsHigh == HIGH) 
        {
            buttonEle.second->pressed = false;
        } 
        else 
        {
            buttonEle.second->pressedForMillis = millis() - buttonEle.second->pressStartInMillies;
            if (buttonEle.second->pressed == false&&buttonEle.second->wasHighBefore) 
            {
                buttonEle.second->pressStartInMillies = millis();
                buttonEle.second->pressedForMillis=0;
                buttonEle.second->pressed = true;
            }
        }

        if ( buttonEle.second->pressedForMillis >= buttonEle.second->debounceInMillis) 
        {
            if (buttonEle.second->pressedForMillis < buttonEle.second->millisForLongPress&&buttonEle.second->pressed==false) 
            { 
                buttonEle.second->m_press();
                Serial.println("m_press");
            } 
            else if(buttonEle.second->pressed == true&&buttonEle.second->pressedForMillis >= buttonEle.second->millisForLongPress)
            {
                buttonEle.second->m_longPress();
                buttonEle.second->pressed = false;
                Serial.println("m_longPress");
            }
        }

        if (buttonEle.second->pressed == false) 
        {
            buttonEle.second->pressedForMillis = 0;
        }

        buttonEle.second->wasHighBefore=pinIsHigh;
    }

}