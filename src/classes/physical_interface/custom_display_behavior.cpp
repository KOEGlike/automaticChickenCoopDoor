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

/// @brief blink the segments, if another blink is already happening it will override it
/// @param segmentsToBlink segments
/// @param offTime the off time 
void CustomDisplayBehavior::blinkSegments(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime, uint32_t timesToBlink, std::function<void()> onEnd){
  uint32_t onId=Async.registerCallback(
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
      display.setSegments(segments);
      memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength);
    },
    onEnd
  );

  uint32_t offId;
  Async.registerCallback(
    onTime, 
    timesToBlink, 
    [offId](){
      
    },
    onEnd
  );
}


/// @brief blink the dots
void CustomDisplayBehavior::blinkDots(unsigned long offTime){

  if (dotIsBlinking) {
    return;
  }
  
  
  uint8_t beforeBlinkSegments[4];
  memcpy(beforeBlinkSegments, display.currentSegments, display.segmentsLength);
  uint8_t segments[4];
  
memcpy(segments, display.currentSegments, display.segmentsLength);
  m_dotOffTime = offTime;
  dotIsBlinking = true;
  dotIsOn=false;
  segments[1]&=~0b10000000;
  dotBlinkStartInMillis = millis();
  display.setSegments(segments);
  memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength); 
}




/// @brief scroll the segments
/// @param segments segments to scroll
/// @param millisForOneMove the time it takes for on segment to move
/// @param amount the amount to scroll, if 0 or less it will scroll forever
/// @param onEnd a function to call when the scrolling is done
void CustomDisplayBehavior::scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount, std::function<void()> onEnd)
{
  scrollCycles=0;
  scrollCurrentCycle=0;
  segmentsToScroll=segments;
  scrollAmount=amount;
  scrollSegmentsOnEnd=onEnd;
  std::function<void()> 
  scrollAsyncFunc = [&]() 
  {
   if(scrollCurrentCycle>segmentsToScroll.size()-1) {scrollCurrentCycle=0; scrollCycles++;}
   if(scrollCycles>=scrollAmount&&scrollAmount>=0) {scrollSegmentsOnEnd(); scrollSegmentsContinuouslyOff(); return;}
    uint8_t segmentsToDisplay[4];
    for(int i=0;i<4;i++)
    {
      segmentsToDisplay[i]=segmentsToScroll[scrollCurrentCycle+i<segmentsToScroll.size()?scrollCurrentCycle+i:((scrollCurrentCycle+i)-segmentsToScroll.size())];
    }
    display.setSegments(segmentsToDisplay);
    scrollCurrentCycle++;
  };
  scrollAsyncId= Async.registerCallback(millisForOneMove, -1, scrollAsyncFunc);
}

/// @brief stop the scrolling
void CustomDisplayBehavior::scrollSegmentsContinuouslyOff()
{
  
  Async.deleteCallBack(scrollAsyncId);
}

/// @brief stop all activities, including blinking and scrolling
void CustomDisplayBehavior::stopAllActivities()
{
  dotBlinkAnAmountLongDelayContinuos=-1;dotBlinkAnAmountLongDelayContinuosStart; 
  timesBlinked = 0; timesToBlink = -1;timesDotBlinked = 0; timesDotToBlink = -1;
  isBlinking = false; isContinuouslyBlinking = false; dotIsBlinking=false;dotIsContinuouslyBlinking = false; dotIsOn=false;isDotBlinkAnAmountLongDelayContinuos=false;
  scrollSegmentsContinuouslyOff();
}