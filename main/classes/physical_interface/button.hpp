#pragma once
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"
#include <inttypes.h>
#include <memory>



class ButtonManager_t {
    public:
        ~ButtonManager_t();
        void link(std::vector<uint> buttonIDs, std::function<void()> onPress, int maxDelta=40);
        uint addButton(int pin, std::function<void()> press, std::function<void()> longPress);
        void removeButton(uint id);
        void check();
        void begin();
        uint64_t timeFromLastPress();
    protected:
        class Button {
            public:
                Button(int pin, std::function<void()> press , std::function<void()> longPress);
                void begin();
          
                std::vector<uint> linkIds;
                int m_pin;
                std::function<void()> m_longPress, m_press;
                bool pressed = false;
                unsigned long millisForLongPress = 300, debounceInMillis = 10, pressedForMillis = 0, pressStartInMillies=0;
        };

        struct ButtonLinkStruct{
            ButtonLinkStruct() : maxDelta(0) {}
            ButtonLinkStruct(std::vector<uint> buttonIDs, std::function<void()> onPress,int maxDelta)
            {
                this->buttonIDs = buttonIDs;
                this->onPress = onPress;
                this->maxDelta = maxDelta;
            }
            std::vector<uint> buttonIDs;
            std::function<void()> onPress;
            int maxDelta;
        };

        TaskHandle_t asyncId;

        std::map<uint, std::shared_ptr<Button>> buttons;
        std::map<uint, ButtonLinkStruct> buttonLinks;
        uint currentMaxButtonId=0,currentMaxLinkId=0;
        std::vector<uint>  sortVectorOfIntsThatAreLinkIdsByTheNumberOfButtonsInTheLinks(std::vector<uint> linkIds);
        uint64_t lastPress=0;
};

inline ButtonManager_t ButtonManager;


