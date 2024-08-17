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
}

/// @brief add the amount to the state
/// @param amount the amount to add to the state
void StateCounter::add(uint8_t amount)
{
    state = (amount + state) % m_amountOfStates;
    
}

/// @brief subtract the amount from the state
/// @param amount the amount to subtract from the state
void StateCounter::subtract(uint8_t amount)
{
    state = (state - amount) % m_amountOfStates;
    if (state < 0)
    {
        state = m_amountOfStates + state;
    }
}


/// @brief add or subtract the amount from the state
/// @param amount the amount to add or subtract from the state
void StateCounter::mutate(int8_t amount)
{    
    m_onMutate(amount);
    if(amount<0)
    {
        subtract(amount);
    }
    else
    {
        add(amount);
    }
}

/// @brief get the current state of the counter
/// @return the current state of the counter
uint8_t StateCounter::getState()
{
    return state;
}

/// @brief get the current state of the counter in a bit mask
/// @return the current state of the counter in a bit mask
uint8_t StateCounter::getStateInBitMask()
{
    return 1 << (m_amountOfStates - 1 - state);
}

/// @brief get the amount of states the counter can be in
/// @return the amount of states the counter can be in
int StateCounter::getAmountOfStates()
{
    return m_amountOfStates;
}

/// @brief set the state of the counter
/// @param counterState the state to set the counter to
void StateCounter::setState(uint8_t counterState)
{
    if (counterState > m_amountOfStates - 1)
    {
        resetState();
        return;
    }
    state = counterState;
}

/// @brief set the amount of states the counter can be in
/// @param amountOfStates the amount of states the counter can be in
void StateCounter::setAmountOfStates(int amountOfStates)
{
    m_amountOfStates = amountOfStates;
    if(state>m_amountOfStates-1)
    {
        state = m_amountOfStates-1;
    }
}

/// @brief reset the state of the counter
void StateCounter::resetState()
{
    state = m_amountOfStates;
}
