#ifndef CUSTOM_DISPLAY_BEHAVIOR_H
#define CUSTOM_DISPLAY_BEHAVIOR_H

#include "../modified_libraries/TM1637/TM1637Display.h"
#include <functional>
#include "async_handler.hpp"

extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
class CustomDisplayBehavior : public TM1637Display {
protected:
    unsigned long blinkStartInMillis, m_offTime, m_onTime, blinkEnd,dotBlinkStartInMillis, m_dotOffTime, m_dotOnTime, dotBlinkEnd;
    int timesBlinked = 0, timesToBlink = -1,timesDotBlinked = 0, timesDotToBlink = -1;
    uint8_t segmentsThatBlink;
    bool isBlinking = false, isContinuouslyBlinking = false, dotIsBlinking=false,dotIsContinuouslyBlinking = false, dotIsOn=false;
    std::function<void()> bilinkSegmentsAnAmountOnEndFunc = []() {},bilinkDotsAnAmountOnEndFunc= []() {};
    void dotBlinkCheck();
    void blinkCheck();

public:
    CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO);
    
    void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime = 50);
    void blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkSegmentsContinuouslyOff();
    void bilinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime = 50, unsigned long onTime = 50, std::function<void()> onEnd = []() {});
    void check();
    void blinkDots(unsigned long offTime = 50);
    void blinkDotsContinuouslyOn(unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkDotsContinuouslyOff();
    void bilinkDotsAnAmount(unsigned int amount, unsigned long offTime = 50, unsigned long onTime = 50, std::function<void()> onEnd = []() {});
    };

#endif