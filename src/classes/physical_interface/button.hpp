#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"
#include <inttypes.h>

class ButtonManager_t;
class Button {
    public:
        Button(int pin, std::function<void()> press , std::function<void()> longPress);
        ~Button();
        void begin();
        friend class ButtonManager_t;
    protected:
        std::vector<uint> linkIds;
        int m_pin;
        std::function<void()> m_longPress, m_press;
        bool pressed = false,wasHighBefore=true;
        unsigned long millisForLongPress = 300, debounceInMillis = 10, pressedForMillis = 0, pressStartInMillies=0;
};

struct ButtonLinkStruct{
    ButtonLinkStruct() : maxDelta(0) {}
    ButtonLinkStruct(std::vector<std::shared_ptr<Button>> buttonPtrs, std::function<void()> onPress,int maxDelta)
    {
        this->buttonPtrs = buttonPtrs;
        this->onPress = onPress;
        this->maxDelta = maxDelta;
    }
    std::vector<std::shared_ptr<Button>> buttonPtrs;
    std::function<void()> onPress;
    int maxDelta;
};

class ButtonManager_t {
    public:
        ~ButtonManager_t();
        void link(std::vector<std::shared_ptr<Button>> buttons, std::function<void()> onPress, int maxDelta=40);
        void addButton(std::shared_ptr<Button> button);
        void removeButton(std::shared_ptr<Button> button);
        void check();
        void begin();
        uint64_t timeFromLastPress();
    protected:
    	std::map<uint, std::shared_ptr<Button>> buttons;
        std::map<uint, ButtonLinkStruct> buttonLinks;
        uint currentMaxButtonId=0,currentMaxLinkId=0, asyncId;
        std::vector<uint>  sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds);
        uint64_t lastPress=0;
};

inline ButtonManager_t ButtonManager;

#endif
