#pragma once

#include <cstdint>

class StateCounter
{
private:
    int state;
    int _amountOfStates;

public:
    StateCounter(int amountOfStates);
    void add(uint8_t amount = 1);
    void subtract(uint8_t amount = 1);
    uint8_t getState();
    uint8_t getStateInBitMask();
    void setState(uint8_t counterState);
    void resetState();
};