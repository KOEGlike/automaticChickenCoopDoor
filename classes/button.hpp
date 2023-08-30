#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>

class Button {
protected:
    int _pin;
    bool* _globalPressed;
    std::function<void()> _longPress, _press;
    bool pressed = false;
    unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies;

public:
    Button(int pin, bool* globalPressed, std::function<void()> press = []() {}, std::function<void()> longPress = []() {});
    void check();

};

#endif