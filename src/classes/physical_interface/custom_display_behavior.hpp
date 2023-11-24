#ifndef CUSTOM_DISPLAY_BEHAVIOR_H
#define CUSTOM_DISPLAY_BEHAVIOR_H

#include <TM1637Display.h>
#include <functional>
#include "../async_handler.hpp"
#include <vector>

extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
class CustomDisplayBehavior : public TM1637Display {
  public:
    CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO);
    ~CustomDisplayBehavior() ;
    void begin();

    void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime = 50);
    void blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkSegmentsContinuouslyOff();
    void blinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime = 50, unsigned long onTime = 50, std::function<void()> onEnd = []() {});
    void changeSegmentsContinuos(uint8_t segmentsToBlink, unsigned long offTime = 50, unsigned long onTime = 50);
   
    void blinkDots(unsigned long offTime = 50);
    void blinkDotsContinuouslyOn(unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkDotsContinuouslyOff();
    void blinkDotsAnAmount(unsigned int amount, unsigned long offTime = 50, unsigned long onTime = 50, std::function<void()> onEnd = []() {});
    void blinkDotsAnAmountThenDelayContinuously(unsigned int amount, unsigned long longOffTime = 50,unsigned long offTime = 50, unsigned long onTime = 50);
    void blinkDotsAnAmountThenDelayContinuouslyChangeAmount(unsigned int amount);

    void scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount,  std::function<void()> onEnd = []() {});
    void scrollSegmentsContinuouslyOff();

    

    void stopAllActivities();
  protected:
    unsigned long blinkStartInMillis, m_offTime, m_onTime, blinkEnd,dotBlinkStartInMillis, m_dotOffTime, m_dotOnTime, dotBlinkEnd, dotBlinkAnAmountLongDelayContinuos=-1,dotBlinkAnAmountLongDelayContinuosStart, blinkDotsAnAmountThenDelayContinuouslyOffTime, blinkDotsAnAmountThenDelayContinuouslyOnTime,dotBlinkAnAmountLongDelayContinuosAmount ;
    int timesBlinked = 0, timesToBlink = -1,timesDotBlinked = 0, timesDotToBlink = -1, scrollCycles=0, scrollAmount=0;
    bool isBlinking = false, isContinuouslyBlinking = false, dotIsBlinking=false,dotIsContinuouslyBlinking = false, dotIsOn=false,isDotBlinkAnAmountLongDelayContinuos=false;
    uint8_t segmentsThatBlink;
    std::function<void()> blinkSegmentsAnAmountOnEndFunc = []() {},blinkDotsAnAmountOnEndFunc= []() {}, scrollSegmentsOnEnd=[](){};
    std::vector<uint8_t> segmentsToScroll;
    void dotBlinkCheck();
    void blinkCheck();
    uint32_t asyncId, scrollAsyncId;
    void check();
    };

#endif