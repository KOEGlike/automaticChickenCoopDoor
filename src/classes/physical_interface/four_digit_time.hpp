#ifndef FOURDIGITTIME_HPP
#define FOURDIGITTIME_HPP

extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
#include <cmath>
#include <functional>
#include "counter.hpp"

class FourDigitTime {
    public:
      FourDigitTime();
      void setTime(int hours, int minutes);
      void setDigits(int digits);
      int getDigits();
      void mutateMinutes(int minutes);
      void mutateOneDigit(int placement, int mutate,bool stepOver=true);
  
    protected:
      /// @brief whether to step over the next digit when mutating
      bool m_stepOver=true;
      
      void H1OnMutate(int times);
      void H2OnMutate(int times);
      void M1OnMutate(int times);
      void M2OnMutate(int times);
         
      /// @brief the first digit of the hour
      StateCounter H1;
      /// @brief the second digit of the hour
      StateCounter H2;
      /// @brief the first digit of the minute
      StateCounter M1;
      /// @brief the second digit of the minute
      StateCounter M2;
        
      void addMinutes(uint16_t minutes);
      void subtractMinutes(uint16_t minutes);
};

#endif