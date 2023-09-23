#include "counter.hpp"
#include <cstdint>
#include <functional>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
StateCounter::StateCounter(int amountOfStates, std::function<void(uint8_t amount)> onMutate)
{
    state = amountOfStates;
    m_amountOfStates = amountOfStates;
    m_onMutate = onMutate;
    Serial.println("StateCounter created");
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

void StateCounter::mutate(uint8_t amount)
{    
    m_onMutate(amount);
    if(amount<0)
    {
        subtract(-amount);
    }
    else
    {
        add(amount);
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

int StateCounter::getAmountOfStates()
{
    return m_amountOfStates;
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

void StateCounter::setAmountOfStates(int amountOfStates)
{
    m_amountOfStates = amountOfStates;
    if(state>m_amountOfStates-1)
    {
        state = m_amountOfStates-1;
    }
}

void StateCounter::resetState()
{
    state = m_amountOfStates;
}
