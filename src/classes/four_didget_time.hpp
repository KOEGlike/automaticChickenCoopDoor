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
      std::function<void()> H1Up;
      std::function<void()> H2Up;
      std::function<void()> M1Up;
      std::function<void()> M2Up;
        
      std::function<void()> H1Down;
      std::function<void()> H2Down;
      std::function<void()> M1Down;
      std::function<void()> M2Down;
        
      StateCounter H1{3,H1Up,H1Down};
      StateCounter H2{10,H2Up,H2Down};
      StateCounter M1{7,M1Up,M1Down};
      StateCounter M2{10, M2Up,M2Down};
        
      void addMinutes(uint16_t minutes);
      void subtractMinutes(uint16_t minutes);
      void mutateMinutesWithoutStepover(uint16_t minutes, uint8_t placement);

    public:
        void setTime(int hours, int minutes);
        void setDigits(int digits);
        int getDigits();
        void mutateMinutes(int minutes);
        void mutateOneDigit(int placement, int mutate,bool stepover=true);
};

#endif