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
                bool wasMultiplePress=false;
                for(auto linkId : buttonEle.second->linkIds)
                {
                    bool allPressed=true;
                    for(auto button: buttonLinks[linkId].buttonPtrs)
                    {
                        if(button->pressStartInMillies-button->pressedForMillis<=5&&button->pressed==true)
                        {
                            allPressed=true;
                        }
                        else
                        {
                            allPressed=false;
                        }

                        if(allPressed==false)
                        {
                            break;
                        }
                    }
                    if(allPressed==true)
                    {
                        buttonLinks[linkId].onPress();
                        wasMultiplePress=true;
                        break;
                    }
                }
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

std::vector<uint> ButtonManager_t::sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds)
{
    std::sort(linkIds.begin(), linkIds.end(),[&](uint linkId1,uint linkId2){return( buttonLinks[linkId1].buttonPtrs.size()>buttonLinks[linkId2].buttonPtrs.size());});
    return linkIds;
}

bool ButtonManager_t::ButtonLinkStructComparasainForSort(uint linkId1,uint linkId2)
{
    
}