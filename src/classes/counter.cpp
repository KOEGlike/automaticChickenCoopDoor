#include "counter.hpp"
#include <cstdint>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
StateCounter::StateCounter(int amountOfStates)
{
    state = amountOfStates;
    m_amountOfStates = amountOfStates;
}

void StateCounter::add(uint8_t amount)
{
    state = (amount + state) % m_amountOfStates;
}

void StateCounter::subtract(uint8_t amount)
{
    state = (state - amount) % m_amountOfStates;
    if (state < 0)
    {
        state = m_amountOfStates + state;
    }
}

uint8_t StateCounter::getState()
{
    return state;
}

uint8_t StateCounter::getStateInBitMask()
{
    return 1 << (m_amountOfStates - 1 - state);
}

void StateCounter::setState(uint8_t counterState)
{
    if (counterState > m_amountOfStates - 1)
    {
        resetState();
        return;
    }
    state = counterState;
}

void StateCounter::resetState()
{
    state = m_amountOfStates;
}
