#include "button.hpp"
#include <Arduino.h>
#include <functional>

Button::Button(int pin, std::function<void()> press, std::function<void()> longPress) {
    m_pin = pin;
    m_longPress = longPress;
    m_press = press;
}

Button::~Button() {
    ButtonManager.removeButton(this);
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
    asyncId = Async.registerCallback(0, -1, [=](){check();});
}

void ButtonManager_t::link(std::vector<Button*> buttons, std::function<void()> onPress, int maxDelta)
{
    ButtonLinkStruct link{buttons, onPress, maxDelta};
    buttonLinks[currentMaxLinkId] = link;
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
        bool pinIsHigh=digitalRead(btnPtr->m_pin)==HIGH?true:false;
        if (pinIsHigh == HIGH) 
        {
            btnPtr->pressed = false;
        } 
        else 
        {
            if (btnPtr->pressed == false&&btnPtr->wasHighBefore) 
            {
                btnPtr->pressStartInMillies = millis();
                btnPtr->pressedForMillis=0;
                btnPtr->pressed = true;
            }
        }
        if(btnPtr->pressed) {btnPtr->pressedForMillis = millis() - btnPtr->pressStartInMillies;}

        if ( btnPtr->pressedForMillis >= btnPtr->debounceInMillis) 
        {
            
            if (btnPtr->pressedForMillis < btnPtr->millisForLongPress&&btnPtr->pressed==false) 
            { 
                lastPress=millis();
                btnPtr->m_press();
            } 
            else if(btnPtr->pressed == true&&btnPtr->pressedForMillis >= btnPtr->millisForLongPress)
            {
                bool wasMultiplePress=true;
                for(auto linkId : btnPtr->linkIds)
                {
                    for(auto button: buttonLinks[linkId].buttonPtrs)
                    {   
                        if(button->millisForLongPress-button->pressedForMillis<=buttonLinks[linkId].maxDelta&&button->pressed==true)
                        {
                            wasMultiplePress=true;                        
                        }
                        else
                        {
                            wasMultiplePress=false;
                        }

                        if(wasMultiplePress==false) break;
                    }
                    if(wasMultiplePress==true) 
                    {
                        lastPress=millis();
                        buttonLinks[linkId].onPress();
                        for(auto button: buttonLinks[linkId].buttonPtrs)
                        {
                            button->pressed=false;
                            button->pressedForMillis=0;
                        } 
                        break;
                    }
                }
                if(wasMultiplePress==false)
                {
                    lastPress=millis();
                    btnPtr->m_longPress();
                    btnPtr->pressed = false;
                }
            }
        }

        if (btnPtr->pressed == false) 
        {
            btnPtr->pressedForMillis = 0;
        }

        btnPtr->wasHighBefore=pinIsHigh;
    }

}

uint64_t ButtonManager_t::timeFromLastPress()
{
    return millis()-lastPress;
}

std::vector<uint> ButtonManager_t::sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds)
{
    std::sort(linkIds.begin(), linkIds.end(),[=](uint linkId1,uint linkId2){return( buttonLinks[linkId1].buttonPtrs.size()>buttonLinks[linkId2].buttonPtrs.size());});
    return linkIds;
}

int getIndex(std::vector<uint> v, uint K) 
{ 
    auto it = find(v.begin(), v.end(), K); 
    int index = it - v.begin();
    return  index ;
} 


void ButtonManager_t::removeButton(Button* button)
{
    std::vector<uint> links=button->linkIds;
    for(auto link : links)
    {
        for(auto button : buttonLinks[link].buttonPtrs)
        {
            int index=getIndex(button->linkIds, link);
            button->linkIds.erase(button->linkIds.begin()+index);
        }
        buttonLinks.erase(link);
    }
}