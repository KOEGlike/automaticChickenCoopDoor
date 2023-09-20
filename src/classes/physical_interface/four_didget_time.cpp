#include "four_didget_time.hpp"
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
#include <cmath>
#include <functional>
#include "../counter.hpp"
#include "Arduino.h"
using namespace std::placeholders;


void FourDigitTime::H1OnMutate(int amount)
{
    
    if(H2.getState()>4&&H1.getAmountOfStates()>2)
    {
        H1.setAmountOfStates(2);
        //Serial.println("H1OnMutate");
    }
     else if(H2.getState()<=4&&H1.getAmountOfStates()!=3)
    {
        H1.setAmountOfStates(3);
        //Serial.println("H1OnMutttttate");
    }
    
}

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

void FourDigitTime::M1OnMutate(int amount)
{
    if (m_stepOver)
    {
        H2.mutate((M1.getState()+amount)/M1.getAmountOfStates());
    }
}

void FourDigitTime::M2OnMutate(int amount)
{
    if (m_stepOver)
    {
        M1.mutate((M2.getState()+amount)/M2.getAmountOfStates());
    }
}


void FourDigitTime::setTime(int hours, int minutes) {
    H1.setState(hours / 10);
    H2.setState(hours % 10);
    M1.setState(minutes / 10);
    M2.setState(minutes % 10);
}

void FourDigitTime::setDigits(int digits) {
    H1.setState(digits / 1000);
    H2.setState((digits / 100) % 10);
    M1.setState((digits / 10) % 10);
    M2.setState(digits % 10);
}

int FourDigitTime::getDigits() {
    return H1.getState() * 1000 + H2.getState() * 100 + M1.getState() * 10 + M2.getState();
}

void FourDigitTime::mutateMinutes(int minutes) {
    if (minutes < 0) {
    M2.subtract(-minutes);
} else {
        M2.add(minutes);
    }
}

void FourDigitTime::mutateOneDigit(int placement, int mutate,bool stepover) {
     m_stepOver=stepover;
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



