#ifndef CUSTOM_DISPLAY_BEHAVIOR_H
#define CUSTOM_DISPLAY_BEHAVIOR_H

#include "../modified_libraries/TM1637/TM1637Display.h"
#include <functional>

extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
class CustomDisplayBehavior : public TM1637Display {
protected:
    unsigned long blinkStartInMillis, _offTime, _onTime, blinkEnd;
    int timesBlinked = 0, timesToBlink = -1;
    uint8_t segmentsThatBlink;
    bool isBlinking = false, isContinuouslyBlinking = false;
    std::function<void()> bilinkSegmentsAnAmountOnEndFunc = []() {};

    void blinkCheck();

public:
    CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO);

    void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime = 50);
    void blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkSegmentsContinuouslyOff();
    void bilinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime = 50, unsigned long onTime = 50, std::function<void()> onEnd = []() {});

    void check();
};

#endif