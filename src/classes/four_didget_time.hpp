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
    protected:
      bool m_stepOver=true;
      
      void H1OnMutate(int times);
      void H2OnMutate(int times);
      void M1OnMutate(int times);
      void M2OnMutate(int times);
        
      
        
      StateCounter H1{3,[&](int times){H1OnMutate(times);}};
      StateCounter H2{10,[&](int times){H2OnMutate(times);}};
      StateCounter M1{6,[&](int times){M1OnMutate(times);}};
      StateCounter M2{10,[&](int times){M2OnMutate(times);}};
        
      void addMinutes(uint16_t minutes);
      void subtractMinutes(uint16_t minutes);

    public:
        void setTime(int hours, int minutes);
        void setDigits(int digits);
        int getDigits();
        void mutateMinutes(int minutes);
        void mutateOneDigit(int placement, int mutate,bool stepOver=true);
};

#endif