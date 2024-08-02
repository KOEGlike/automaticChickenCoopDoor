#ifndef STATE_COUNTER_HPP
#define STATE_COUNTER_HPP
#include <cstdint>
#include <functional>
extern "C"
{
#include <stdlib.h>
#include <inttypes.h>
}

#include <Arduino.h>
class StateCounter
{
  private:
    /// @brief the current state of the counter
    int state;
    /// @brief the amount of states the counter can be in
    int m_amountOfStates;
    /// @brief the function to call when the counter is mutated
    std::function<void(uint8_t times)> m_onMutate = [](int a) {};

  public:
    /// @brief the constructor for the StateCounter class
    /// @param amountOfStates the amount of states the counter can be in
    /// @param onMutate a function to call when the counter is mutated by a certain amount
    StateCounter(int amountOfStates, std::function<void(uint8_t amount)> onMutate = [](uint8_t amount) {});
    void add(uint8_t amount = 1);
    void subtract(uint8_t amount = 1);
    void mutate(int8_t amount = 1);
    uint8_t getState();
    uint8_t getStateInBitMask();
    int getAmountOfStates();
    void setState(uint8_t counterState);
    void setAmountOfStates(int amountOfStates);
    void resetState();
};

#endif