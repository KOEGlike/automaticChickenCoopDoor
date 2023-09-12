#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO)
  : TM1637Display(pinClk, pinDIO) {
  }


void CustomDisplayBehavior::blinkSegments(uint8_t segmentsToBlink, unsigned long offTime) {
  uint8_t beforeBlinkSegments[4];
  memcpy(beforeBlinkSegments, currentSegments, segmentsLength);
  uint8_t segments[4];
  memcpy(segments, currentSegments, segmentsLength);
  
  if (segmentsToBlink & 0b1000) {
    segments[0] = 0;
  }
  if (segmentsToBlink & 0b0100) {
    segments[1] = 0;
  }
  if (segmentsToBlink & 0b0010) {
    segments[2] = 0;
  }
  if (segmentsToBlink & 0b0001) {
    segments[3] = 0;
  }
  
  setSegments(segments);
  memcpy(currentSegments, beforeBlinkSegments, segmentsLength);
  Async.registerCallback(offTime, 1, [&](){
    setSegments(currentSegments);}, [](){}, true);
}

void CustomDisplayBehavior::blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime) {
  segmentsThatBlink = segmentsToBlink;
  m_onTime = onTime;
continouslyBlinkingAsyncId=Async.registerCallback(offTime+onTime, -1, [&](){blinkSegments(segmentsThatBlink, offTime);});
}
void CustomDisplayBehavior::blinkSegmentsContinuouslyOff() {
  Async.deleteCallBack(continouslyBlinkingAsyncId);
}

void CustomDisplayBehavior::bilinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  Async.registerCallback(offTime+onTime, amount, [&](){blinkSegments(segmentsThatBlink, offTime);}, onEnd);
}

void CustomDisplayBehavior::blinkDots(unsigned long offTime)
{
  if(dotBlink)
  {
    return;
  }
  dotBlink=true;
  
  
}


