#include "four_digit_time.hpp"
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
#include <cmath>
#include <functional>
#include "Arduino.h"
using namespace std::placeholders;

/// @brief the constructor for the FourDigitTime class
FourDigitTime::FourDigitTime():H1(3,[&](int times){H1OnMutate(times);}),
 H2(10,[&](int times){H2OnMutate(times);}), 
 M1(6,[&](int times){M1OnMutate(times);}), 
 M2(10,[&](int times){M2OnMutate(times);})
{}

/// @brief what happens when H1 is mutated
/// @param amount the amount to mutate (add/subtract) by
void FourDigitTime::H1OnMutate(int amount)
{
    
    if(H2.getState()>4&&H1.getAmountOfStates()>2)
    {
        H1.setAmountOfStates(2);
    }
     else if(H2.getState()<=4&&H1.getAmountOfStates()!=3)
    {
        H1.setAmountOfStates(3);
    }
    
}

/// @brief what happens when H2 is mutated
/// @param amount the amount to mutate (add/subtract) by
void FourDigitTime::H2OnMutate(int amount)
{
    if(H1.getState()>1&&H2.getAmountOfStates()>4)
    {
        H2.setAmountOfStates(4);
    }
     else if(H1.getState()<=1&&H2.getAmountOfStates()!=10)
    {
        H2.setAmountOfStates(10);
    }
    if (m_stepOver)
    {
        H1.mutate((H1.getState()+amount)/H1.getAmountOfStates());
    }
}

/// @brief what happens when M1 is mutated
/// @param amount the amount to mutate (add/subtract) by
void FourDigitTime::M1OnMutate(int amount)
{
    if (m_stepOver)
    {
        H2.mutate((M1.getState()+amount)/M1.getAmountOfStates());
    }
}

/// @brief what happens when M2 is mutated
/// @param amount the amount to mutate (add/subtract) by
void FourDigitTime::M2OnMutate(int amount)
{
    if (m_stepOver)
    {
        M1.mutate((M2.getState()+amount)/M2.getAmountOfStates());
    }
}

/// @brief sets the time
/// @param hours how many hours
/// @param minutes how many minutes
void FourDigitTime::setTime(int hours, int minutes) {
    H1.setState(hours / 10);
    H2.setState(hours % 10);
    M1.setState(minutes / 10);
    M2.setState(minutes % 10);
}

/// @brief sets the digits HHMM
/// @param digits the digits to set
void FourDigitTime::setDigits(int digits) {
    H1.setState(digits / 1000);
    H2.setState((digits / 100) % 10);
    M1.setState((digits / 10) % 10);
    M2.setState(digits % 10);
}

/// @brief gets the digits HHMM
int FourDigitTime::getDigits() {
    return H1.getState() * 1000 + H2.getState() * 100 + M1.getState() * 10 + M2.getState();
}

/// @brief mutates M2 by the amount of minutes
/// @param minutes the amount of minutes to mutate by
void FourDigitTime::mutateMinutes(int minutes) {
    if (minutes < 0) {
    M2.subtract(-minutes);
} else {
        M2.add(minutes);
    }
}

/// @brief placement is the digit to mutate, mutate is the amount to mutate by
/// mutate means add or subtract the amount from the digit
void FourDigitTime::mutateOneDigit(int placement, int mutate,bool stepOver) {
    m_stepOver=stepOver;
    switch (placement)
    {
    case 0:
    H1.mutate(mutate);
        break;
    case 1:
    H2.mutate(mutate);
        break;
    case 2:
    M1.mutate(mutate);
        break;
    case 3:
    M2.mutate(mutate);
        break;
    }
    m_stepOver=true;

}