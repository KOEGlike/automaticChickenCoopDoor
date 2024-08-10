#include "button.hpp"
#include <Arduino.h>
#include <functional>
#include <memory>

ButtonManager_t::Button::Button(int pin, std::function<void()> press, std::function<void()> longPress) {
    m_pin = pin;
    m_longPress = longPress;
    m_press = press;
}

ButtonManager_t::~ButtonManager_t() 
{
    Async.deleteCallBack(asyncId);
}

void ButtonManager_t::begin() 
{
    asyncId = Async.registerCallback("button check",0, -1, [&](){check();});
}

void ButtonManager_t::link(std::vector<uint> buttonIDs, std::function<void()> onPress, int maxDelta)
{
    ButtonLinkStruct link{buttonIDs, onPress, maxDelta};
    buttonLinks[currentMaxLinkId] = link;
    for(auto id : buttonIDs)
    {
        buttons[id]->linkIds.push_back(currentMaxLinkId);
        buttons[id]->linkIds=sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(buttons[id]->linkIds);
    }
    
    currentMaxLinkId++;
}

uint ButtonManager_t::addButton(int pin, std::function<void()> press, std::function<void()> longPress)
{
    buttons[currentMaxButtonId] = std::make_shared<Button>(pin, press, longPress);
    return currentMaxButtonId++;
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
                    for(auto id: buttonLinks[linkId].buttonIDs)
                    {   
                        if(buttons[id]->millisForLongPress-buttons[id]->pressedForMillis<=buttonLinks[linkId].maxDelta&&buttons[id]->pressed==true)
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
                        for(auto button: buttonLinks[linkId].buttonIDs)
                        {
                            buttons[id]->pressed=false;
                            buttons[id]->pressedForMillis=0;
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
    std::sort(linkIds.begin(), linkIds.end(),[&](uint linkId1,uint linkId2){return( buttonLinks[linkId1].buttonIDs.size()>buttonLinks[linkId2].buttonIDs.size());});
    return linkIds;
}

int getIndex(std::vector<uint> v, uint K) 
{ 
    auto it = find(v.begin(), v.end(), K); 
    int index = it - v.begin();
    return  index ;
} 


void ButtonManager_t::removeButton(uint id)
{
    std::vector<uint> links=buttons[id]->linkIds;
    for(auto link : links)
    {
        for(auto id : buttonLinks[link].buttonIDs)
        {
            int index=getIndex(buttons[id]->linkIds, link);
            buttons[id]->linkIds.erase(buttons[id]->linkIds.begin()+index);
        }
        buttonLinks.erase(link);
    }
}