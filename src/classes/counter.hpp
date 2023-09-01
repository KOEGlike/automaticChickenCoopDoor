#ifndef STATE_COUNTER_HPP
#define STATE_COUNTER_HPP
#include <cstdint>
#include <functional>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}

class StateCounter
{
private:
    int state;
    int m_amountOfStates;
    std::function<void()> m_onStepOver=[](){}, m_onStepDown=[](){};
public:
    StateCounter(int amountOfStates, std::function<void()> onStepOver=[](){},std::function<void()> onStepDown=[](){});
    void add(uint8_t amount = 1);
    void subtract(uint8_t amount = 1);
    uint8_t getState();
    uint8_t getStateInBitMask();
    void setState(uint8_t counterState);
    void resetState();
};

#endif