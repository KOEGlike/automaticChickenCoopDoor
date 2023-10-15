#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"

class ButtonManager;
class Button {
    public:
        Button(int pin, std::function<void()> press , std::function<void()> longPress , bool* globalPressed);
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
std::vector<Button*> buttonPtrs;
std::function<void()> onPress;
};

class ButtonManager_t {
    public:
        ~ButtonManager_t();
        void link(std::vector<Button*> buttons, std::function<void()> onPress);
        void addButton(Button* button);
        void check();
        void begin();
    protected:
    	std::map<uint, Button*> buttons;
        std::map<uint, ButtonLinkStruct> buttonLinks;
        uint currentMaxButtonId=0,currentMaxLinkId=0, asyncId;
        static bool ButtonLinkStructComparasainForSort(uint linkId1,uint linkId2, std::vector<Button*> buttonLinks);
        std::vector<uint>  sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds);
};

inline ButtonManager_t ButtonManager;

#endif