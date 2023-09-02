#include "ChickenDoor.hpp"

ChickenDoor::ChickenDoor(uint8_t clkPin, uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin)
{
    preferences.begin("times", false);
    openTime = preferences.getUChar("openTime", 0);
    closeTime = preferences.getUChar("closeTime", 0);
}

void ChickenDoor::checks()
{
    button1.check();
    button2.check();
    display.check();
}

void ChickenDoor::defalutForShowNumber(int num)
{
    display.showNumberDecEx(num, 0b11100000, true);
}

int ChickenDoor::digitValueRouter(int state)
{
    switch (state)
    {
    case 0:
        return hour(now()) * 100 + minute(now());
    case 1:
        return openTime;
    case 2:
        return closeTime;
    default:
        return 0;
    }
}

void ChickenDoor::setTimeRouter(int didgets, int state)
{
    switch (state)
    {
    case 0:
        setTime(didgets / 100, didgets % 100, 0, 0, 0, 0);
        break;
    case 1:
        openTime = didgets;
        break;
    case 2:
        closeTime = didgets;
        break;
    }
}


