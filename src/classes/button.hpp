#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include "async_handler.hpp"

class Button {
protected:
    int m_pin;
    bool* m_globalPressed;
    std::function<void()> m_longPress, m_press;
    bool pressed = false;
    unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies;

public:
    Button(int pin, std::function<void()> press , std::function<void()> longPress , bool* globalPressed);
    void check();

};

#endif