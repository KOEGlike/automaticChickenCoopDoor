#include "counter.hpp"
#include <cstdint>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
StateCounter::StateCounter(int amountOfStates)
{
    state = amountOfStates;
    _amountOfStates = amountOfStates;
}

void StateCounter::add(uint8_t amount)
{
    state = (amount + state) % _amountOfStates;
}

void StateCounter::subtract(uint8_t amount)
{
    state = (state - amount) % _amountOfStates;
    if (state < 0)
    {
        state = _amountOfStates + state;
    }
}

uint8_t StateCounter::getState()
{
    return state;
}

uint8_t StateCounter::getStateInBitMask()
{
    return 1 << (_amountOfStates - 1 - state);
}

void StateCounter::setState(uint8_t counterState)
{
    if (counterState > _amountOfStates - 1)
    {
        resetState();
        return;
    }
    state = counterState;
}

void StateCounter::resetState()
{
    state = _amountOfStates;
}
