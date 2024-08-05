#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO): display(pinClk, pinDIO) {}

void CustomDisplayBehavior::begin() { 
  display.begin();
} 


void CustomDisplayBehavior::blinkSegments(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime, uint32_t timesToBlink, std::function<void()> onEnd){
  uint32_t offId=Async.registerCallback(
    offTime+onTime, 
    timesToBlink, 
    [this, segmentsToBlink](){
      uint8_t beforeBlinkSegments[4];
      memcpy(beforeBlinkSegments, display.currentSegments, display.segmentsLength);
      uint8_t segments[4];
      
      memcpy(segments, display.currentSegments, display.segmentsLength);
      
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
      Serial.print(millis());
      Serial.println(" off");
      display.setSegments(segments);
      memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength);
    }
  );
  this->segmentsAsyncId.off=offId;
  Async.registerCallback(
    offTime, 
    1, 
    [=](){
        Serial.print(millis());
        Serial.println(" onTime");
        this->segmentsAsyncId.on = Async.registerCallback(
        offTime+onTime, 
        timesToBlink,
        [this, offId](){
          Serial.print(millis());
          Serial.println(" on");
          if (offId != this->segmentsAsyncId.off) {
            return;
          }
          display.setSegments(display.currentSegments);
        },
        onEnd);
    },
    [](){},
    true
  );
}

void CustomDisplayBehavior::blinkSegmentsOff(){
  Async.deleteCallBack(this->segmentsAsyncId.off);
  Async.deleteCallBack(this->segmentsAsyncId.on);
}

void CustomDisplayBehavior::blinkDots(uint8_t dots, unsigned long offTime, unsigned long onTime, uint32_t timesToBlink, std::function<void()> onEnd){
  uint32_t offId=Async.registerCallback(
    offTime+onTime, 
    timesToBlink, 
    [=](){
      Serial.print(millis());
      Serial.println(" off dots");
      uint8_t beforeBlinkSegments[4];
      memcpy(beforeBlinkSegments, display.currentSegments, display.segmentsLength);
      uint8_t beforeBlinkDisplayedSegments[4];
      memcpy(beforeBlinkDisplayedSegments, display.displayedSegments, display.segmentsLength);
      uint8_t segments[4];
      memcpy(segments, display.displayedSegments, display.segmentsLength);
      display.removeDots(dots, segments);
      display.setSegments(segments);
      memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength);
      memcpy(display.displayedSegments, beforeBlinkDisplayedSegments, display.segmentsLength);
    }
  );
  this->dotsAsyncId.off=offId;
  Async.registerCallback(
    onTime, 
    1, 
    [=](){
      Serial.print(millis());
      Serial.println(" onTime dots");
      this->dotsAsyncId.on = Async.registerCallback(
        offTime+onTime, 
        timesToBlink,
        [this, offId, dots](){
          if (offId != this->dotsAsyncId.off) {
            return;
          }
          uint8_t beforeBlinkSegments[4];
          memcpy(beforeBlinkSegments, display.displayedSegments, display.segmentsLength);
          uint8_t beforeBlinkDisplayedSegments[4];
          memcpy(beforeBlinkDisplayedSegments, display.displayedSegments, display.segmentsLength);
          uint8_t segments[4];
          memcpy(segments, display.displayedSegments, display.segmentsLength);
          display.showDots(dots, segments);
          Serial.print(millis());
          Serial.println(" on dots");
          display.setSegments(segments);
          memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength);
          memcpy(display.displayedSegments, beforeBlinkDisplayedSegments, display.segmentsLength);
        },
        onEnd);
    },
    [](){},
    true
  );
}

void CustomDisplayBehavior::blinkDotsPeriodically(uint8_t dots, uint32_t periods, unsigned long offTime, unsigned long onTime, unsigned long timeBetween, uint32_t timesToBlinkInOnePeriod, std::function<void()> onEnd){
  this->dotsAsyncIdPeriodically=Async.registerCallback(
    timesToBlinkInOnePeriod*(offTime+onTime)+timeBetween, 
    periods, 
    [=](){
      this->blinkDots(dots, offTime, onTime, timesToBlinkInOnePeriod);
    },
    onEnd
  );
}

void CustomDisplayBehavior::blinkDotsOff(){
  Async.deleteCallBack(this->dotsAsyncId.off);
  Async.deleteCallBack(this->dotsAsyncId.on);
  Async.deleteCallBack(this->dotsAsyncIdPeriodically);
}


void CustomDisplayBehavior::scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount, std::function<void()> onEnd)
{
  scrollData.cycles=0;
  scrollData.currentCycle=0;
  scrollData.segments=segments;
  scrollData.amount=amount;
  scrollData.onEnd=onEnd;
  std::function<void()> 
  scrollAsyncFunc = [&]() 
  {
   if(scrollData.currentCycle>segments.size()-1) {scrollData.currentCycle=0; scrollData.cycles++;}
   if(scrollData.cycles>=scrollData.amount&&scrollData.amount>=0) {scrollData.onEnd(); scrollSegmentsOff(); return;}
    uint8_t segmentsToDisplay[4];
    for(int i=0;i<4;i++)
    {
      segmentsToDisplay[i]=segments[scrollData.currentCycle+i<segments.size()?scrollData.currentCycle+i:((scrollData.currentCycle+i)-segments.size())];
    }
    display.setSegments(segmentsToDisplay);
    scrollData.currentCycle++;
  };
  scrollData.asyncId= Async.registerCallback(millisForOneMove, -1, scrollAsyncFunc);
}

void CustomDisplayBehavior::scrollSegmentsOff()
{
  Async.deleteCallBack(scrollData.asyncId);
}

void CustomDisplayBehavior::stopAllActivities()
{
  blinkSegmentsOff();
  blinkDotsOff();
  scrollSegmentsOff();
}