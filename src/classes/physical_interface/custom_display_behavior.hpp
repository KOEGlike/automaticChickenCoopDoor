#pragma once

#include <TM1637Display.h>
#include <functional>
#include "../async_handler.hpp"
#include <vector>

extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}

struct id{
  uint32_t on,off;
  
};
class CustomDisplayBehavior {
  public:
    CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO);
    ~CustomDisplayBehavior() ;

    TM1637Display display;

    void begin();

    void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime=0, uint32_t timesToBlink=1, std::function<void()> onEnd = []() {});
    void blinkDots(unsigned long offTime = 50);
  
    void scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount,  std::function<void()> onEnd = []() {});
    void scrollSegmentsContinuouslyOff();

    

    void stopAllActivities();
  protected:
    std::vector<uint8_t> segmentsToScroll;
    
    id segmentsAsyncId;
    id dotsAsyncId;
    uint32_t scrollAsyncId;
};


