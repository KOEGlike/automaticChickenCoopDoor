#ifndef STATE_COUNTER_HPP
#define STATE_COUNTER_HPP
#include <cstdint>
#include <functional>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}

#include<Arduino.h>
class StateCounter
{
private:
    int state;
    int m_amountOfStates;
    std::function<void(uint8_t times)> m_onMutate=[](int a){};
public:
    StateCounter(int amountOfStates, std::function<void(uint8_t amount)> onMutate = [](uint8_t amount){});
    void add(uint8_t amount = 1);
    void subtract(uint8_t amount = 1);
    void mutate(uint8_t amount = 1);
    uint8_t getState();
    uint8_t getStateInBitMask();
    int getAmountOfStates();
    void setState(uint8_t counterState);
    void setAmountOfStates(int amountOfStates);
    void resetState();
};

#endif