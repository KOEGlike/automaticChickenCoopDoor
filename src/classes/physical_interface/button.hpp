#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"

class ButtonManager_t;
class Button {
    public:
        Button(int pin, std::function<void()> press , std::function<void()> longPress);
        void begin();
        friend class ButtonManager_t;
    protected:
        std::vector<uint> linkIds;
        int m_pin;
        std::function<void()> m_longPress, m_press;
        bool pressed = false,wasHighBefore=true;
        unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies=0;
};

struct ButtonLinkStruct{
    ButtonLinkStruct() : maxDelta(0) {}
    ButtonLinkStruct(std::vector<Button*> buttonPtrs, std::function<void()> onPress,int maxDelta)
    {
        this->buttonPtrs = buttonPtrs;
        this->onPress = onPress;
        this->maxDelta = maxDelta;
    }
    std::vector<Button*> buttonPtrs;
    std::function<void()> onPress;
    int maxDelta;
};

class ButtonManager_t {
    public:
        ~ButtonManager_t();
        void link(std::vector<Button*> buttons, std::function<void()> onPress, int maxDelta);
        void addButton(Button* button);
        void check();
        void begin();
    protected:
    	std::map<uint, Button*> buttons;
        std::map<uint, ButtonLinkStruct> buttonLinks;
        uint currentMaxButtonId=0,currentMaxLinkId=0, asyncId;
        std::vector<uint>  sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds);
        
        // New methods
        void checkButtonPress(Button* button);
        void handleButtonPress(Button* button);
        void checkMultiplePress(Button* button);
};

inline ButtonManager_t ButtonManager;

#endif
