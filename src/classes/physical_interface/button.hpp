#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"

class Button {
protected:
    int m_pin;
    bool* m_globalPressed;
    std::function<void()> m_longPress, m_press;
    bool pressed = false;
    unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies;
public:
    Button(int pin, std::function<void()> press , std::function<void()> longPress , bool* globalPressed);
    ~Button();
    uint32_t asyncId;
    void check();
};

struct ButtonLinkStruct{
std::vector<int> buttonIds;
std::function<void()> onPress;
};

class ButtonManager {
    public:
        void link(std::vector<Button*> buttons, std::function<void()> onPress);
    protected:
    	std::map<int, Button*> m_buttons;
        std::map<int, ButtonLinkStruct> buttonLinks;
        void check();
};

inline ButtonManager buttonManager;

#endif