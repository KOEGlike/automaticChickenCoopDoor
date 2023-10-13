#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include<map>
#include <vector>
#include "../async_handler.hpp"

class ButtonManager;
class Button {
protected:
    int m_pin;
    bool* m_globalPressed, wasHighBefore=true;
    std::function<void()> m_longPress, m_press;
    bool pressed = false;
    unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies=0;
public:
    Button(int pin, std::function<void()> press , std::function<void()> longPress , bool* globalPressed);
    ~Button();
    uint32_t asyncId;
    void check();
    void begin();
    friend class ButtonManager;
};

struct ButtonLinkStruct{
std::vector<Button*> buttonPtrs;
std::function<void()> onPress;
std::function<void()> onLongPress;
};

class ButtonManager {
    public:
        void link(std::vector<Button*> buttons, std::function<void()> onPress, std::function<void()> onLongPress);
        void addButton(Button* button);
        void check();
        void begin();
    protected:
    	std::map<int, Button*> m_buttons;
        std::map<int, ButtonLinkStruct> buttonLinks;
};

inline ButtonManager buttonManager;

#endif