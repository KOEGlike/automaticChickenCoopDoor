#include "counter.hpp"
#include <cstdint>
#include <functional>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
StateCounter::StateCounter(int amountOfStates, std::function<void()> onStepOver=[](){},std::function<void()> onStepDown=[](){})
{
    state = amountOfStates;
    m_amountOfStates = amountOfStates;
    m_onStepOver=onStepOver;
    m_onStepDown=onStepDown;
}

void StateCounter::add(uint8_t amount)
{
    if(amount + state>=m_amountOfStates)
    {
        m_onStepOver();
    }
    state = (amount + state) % m_amountOfStates;
}

void StateCounter::subtract(uint8_t amount)
{
    state = (state - amount) % m_amountOfStates;
    if (state < 0)
    {
        state = m_amountOfStates + state;
        m_onStepDown();
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
