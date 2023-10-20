#include "button.hpp"
#include <Arduino.h>
#include <functional>

Button::Button(int pin, std::function<void()> press, std::function<void()> longPress, bool* globalPressed) {
    m_pin = pin;
    m_longPress = longPress;
    m_press = press;
}

void Button::begin() {
    pinMode(m_pin, INPUT_PULLUP);
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

void ButtonManager_t::link(std::vector<Button*> buttons, std::function<void()> onPress)
{
    buttonLinks[currentMaxLinkId] = ButtonLinkStruct{std::vector<Button*>(buttons), onPress};
    for(auto button : buttons)
    {
        button->linkIds.push_back(currentMaxLinkId);
        button->linkIds=sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(button->linkIds);
    }
    
    currentMaxLinkId++;
}

void ButtonManager_t::addButton(Button* button)
{
    buttons[currentMaxButtonId] = button;
    currentMaxButtonId++;
}

void ButtonManager_t::check() 
{
    for(const auto &[id, btnPtr] :buttons)
    {
        checkButtonPress(btnPtr);
        handleButtonPress(btnPtr);
        
        btnPtr->wasHighBefore = digitalRead(btnPtr->m_pin) == HIGH ? true : false;
    }
}



std::vector<uint> ButtonManager_t::sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds)
{
    std::sort(linkIds.begin(), linkIds.end(),[&](uint linkId1,uint linkId2){return( buttonLinks[linkId1].buttonPtrs.size()>buttonLinks[linkId2].buttonPtrs.size());});
    return linkIds;
}

void ButtonManager_t::checkButtonPress(Button *button)
{
    bool pinIsHigh = digitalRead(button->m_pin) == HIGH ? true : false;
    if (pinIsHigh == HIGH) 
    {
        button->pressed = false;
    } 
    else 
    {
        button->pressedForMillis = millis() - button->pressStartInMillies;
        if (button->pressed == false && button->wasHighBefore) 
        {
            button->pressStartInMillies = millis();
            button->pressedForMillis = 0;
            button->pressed = true;
        }
    }
}

void ButtonManager_t::checkMultiplePress(Button *button)
{
    bool wasMultiplePress = false;
    for(auto linkId : button->linkIds)
    {
        bool allPressed = true;
        for(auto linkedButton: buttonLinks[linkId].buttonPtrs)
        {
            if(linkedButton->pressStartInMillies - linkedButton->pressedForMillis <= 15 && linkedButton->pressed == true)
            {
                allPressed = true;
                Serial.println(button->m_pin);
            }
            else
            {
                allPressed = false;
                Serial.println("no simal");
            }

            if(allPressed == false)
            {
                Serial.println("no siiimal");
                break;
            }
        }
        if(allPressed == true)
        {
            buttonLinks[linkId].onPress();
            Serial.println("simal");
            wasMultiplePress = true;
            break;
        }
    }
    
    if(wasMultiplePress)
    {
        button->pressed = false;
    }
}

void ButtonManager_t::handleButtonPress(Button *button)
{
    if (button->pressedForMillis >= button->debounceInMillis) 
    {
        if (button->pressedForMillis < button->millisForLongPress && button->pressed == false) 
        { 
            button->m_press();
            Serial.println("m_press");
        } 
        else if(button->pressed == true && button->pressedForMillis >= button->millisForLongPress)
        {
            checkMultiplePress(button);
            if(!button->pressed)
            {
                button->m_longPress();
                Serial.println("m_longPress");
            }
        }
    }

    if (button->pressed == false) 
    {
        button->pressedForMillis = 0;
    }
}