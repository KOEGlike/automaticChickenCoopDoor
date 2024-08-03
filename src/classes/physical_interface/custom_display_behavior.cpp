#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO): display(pinClk, pinDIO) {}

CustomDisplayBehavior :: ~CustomDisplayBehavior() { 
  Async.deleteCallBack(asyncId);
}

void CustomDisplayBehavior::begin() { 
  Async.registerCallback(0,-1, [=](){check();});
} 

/// @brief this runts in the async loop to check if the display should blink
void CustomDisplayBehavior::blinkCheck() {
  if (millis() - blinkStartInMillis >= m_offTime && isBlinking) {
    blinkEnd = millis();
    isBlinking = false;
    uint8_t segments[4];
    
    memcpy(segments, display.currentSegments, display.segmentsLength);
    if(dotIsBlinking)
    {
      segments[1]&=~0b10000000;
    }
    if(dotIsOn)
    {
      segments[1]|=0b10000000;
    }
    display.setSegments(segments);
    timesBlinked++;
  }
  
  if (isContinuouslyBlinking && millis() - blinkEnd >= m_onTime && !isBlinking) {
    blinkSegments(segmentsThatBlink, m_offTime);
  }
  
  if (timesToBlink > 0 && timesBlinked == timesToBlink) {
    blinkSegmentsContinuouslyOff();
    timesToBlink = -1;
    blinkSegmentsAnAmountOnEndFunc();
  }
}


/// @brief this runts in the async loop to check if the display should blink
void CustomDisplayBehavior::dotBlinkCheck() {
 
  if (millis() - dotBlinkStartInMillis >= m_dotOffTime && dotIsBlinking) {
    dotBlinkEnd = millis();
    dotIsBlinking = false;
    uint8_t segments[4];
    memcpy(segments, display.currentSegments, display.segmentsLength);
    if(isBlinking)
    {
      segments[1]=0;
    }
    dotIsOn=true;
    segments[1]|=0b10000000;
    display.setSegments(display.currentSegments);
    timesDotBlinked++;
  }
  
  if (dotIsContinuouslyBlinking && millis() - dotBlinkEnd >= m_dotOnTime && !dotIsBlinking) {
    blinkDots(m_dotOffTime);
    dotIsOn=false;
  }

  if (timesDotToBlink > 0 && timesDotBlinked >= timesDotToBlink) {
    blinkDotsContinuouslyOff();
    timesDotToBlink = -1;
    blinkDotsAnAmountOnEndFunc();
  }

  if(millis()-dotBlinkAnAmountLongDelayContinuosStart>=dotBlinkAnAmountLongDelayContinuos&&dotBlinkAnAmountLongDelayContinuosAmount>=0&&isDotBlinkAnAmountLongDelayContinuos==true)
  {
    isDotBlinkAnAmountLongDelayContinuos=false;
    blinkDotsAnAmount(dotBlinkAnAmountLongDelayContinuosAmount, blinkDotsAnAmountThenDelayContinuouslyOffTime,blinkDotsAnAmountThenDelayContinuouslyOnTime, [=](){dotBlinkAnAmountLongDelayContinuosStart=millis(); isDotBlinkAnAmountLongDelayContinuos=true;} );
  }
}

/// @brief blink the segments
/// @param segmentsToBlink segments
/// @param offTime the off time 
void CustomDisplayBehavior::blinkSegments(uint8_t segmentsToBlink, unsigned long offTime) {
  if (isBlinking) {
    return;
  }
  isBlinking = true;
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

  if(dotIsOn)
  {
    segments[1]|=0b10000000;
  }
  if(dotIsBlinking)
  {
    segments[1]&=~0b10000000;
  }
  
  blinkStartInMillis = millis();
  m_offTime = offTime;
  display.setSegments(segments);
  segmentsThatBlink=segmentsToBlink;
  memcpy(display.currentSegments, beforeBlinkSegments, display.segmentsLength);
}

/// @brief blink the segments continuously
/// @param segmentsToBlink segments
/// @param offTime the time the light is off
/// @param onTime the time the light is on
void CustomDisplayBehavior::blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime) {
  isContinuouslyBlinking = true;
  segmentsThatBlink = segmentsToBlink;
  m_onTime = onTime;
  blinkSegments(segmentsThatBlink, offTime);
}

/// @brief stop the continuous blinking, but dont lose the configuration
void CustomDisplayBehavior::blinkSegmentsContinuouslyOff() {
  isContinuouslyBlinking = false;
}

/// @brief change the continuous blinking configuration
/// @param segmentsToBlink 
/// @param offTime the time the light is off
/// @param onTime the time the light is on
void CustomDisplayBehavior::changeSegmentsContinuos(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime)
{
  segmentsThatBlink=segmentsToBlink;
  m_offTime=offTime;
  m_onTime=onTime;
}

/// @brief blink the segments a certain amount of times
/// @param segmentsToBlink 
/// @param amount the amount to blink the segments
/// @param offTime the time the light is off
/// @param onTime the time the light is on
/// @param onEnd a function to call when the blinking is done
void CustomDisplayBehavior::blinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  timesBlinked = 0;
  timesToBlink = amount;
  blinkSegmentsAnAmountOnEndFunc = onEnd;
  blinkSegmentsContinuouslyOn(segmentsToBlink, offTime, onTime);
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

/// @brief blink the dots continuously
/// @param offTime the time the light is off
/// @param onTime the time the light is on
void CustomDisplayBehavior::blinkDotsContinuouslyOn( unsigned long offTime, unsigned long onTime) {
  dotIsContinuouslyBlinking = true;
  m_dotOnTime = onTime;
  blinkDots(offTime);
}

/// @brief stop the continuous blinking of the dots, but dont lose the configuration
void CustomDisplayBehavior::blinkDotsContinuouslyOff() {
  dotIsContinuouslyBlinking = false;
}

/// @brief blink the dots a certain amount of times
/// @param amount the amount
/// @param offTime the time the light is off
/// @param onTime the time the light is on
/// @param onEnd a function to call when the blinking is done
void CustomDisplayBehavior::blinkDotsAnAmount( unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  timesDotBlinked = 0;
  timesDotToBlink = amount;
  blinkDotsAnAmountOnEndFunc = onEnd;
  blinkDotsContinuouslyOn(offTime, onTime);
}

/// @brief blink the dots a certain amount of times then delay some time and then start again
/// @param amount the amount
/// @param longOffTime the time to delay
/// @param offTime the time the light is off
/// @param onTime the time the light is on
void CustomDisplayBehavior::blinkDotsAnAmountThenDelayContinuously(unsigned int amount, unsigned long longOffTime ,unsigned long offTime , unsigned long onTime)
{
  dotBlinkAnAmountLongDelayContinuos=longOffTime;
  blinkDotsAnAmountThenDelayContinuouslyOnTime=onTime;
  blinkDotsAnAmountThenDelayContinuouslyOffTime=offTime;
  dotBlinkAnAmountLongDelayContinuosAmount=amount;
  blinkDotsAnAmount(amount, offTime, onTime, [=](){dotBlinkAnAmountLongDelayContinuosStart=millis(); isDotBlinkAnAmountLongDelayContinuos=true; });
}

/// @brief change the amount of times the dots blink then delay
/// @param amount 
void CustomDisplayBehavior::blinkDotsAnAmountThenDelayContinuouslyChangeAmount(unsigned int amount)
{
  dotBlinkAnAmountLongDelayContinuosAmount=amount;
}

/// @brief check if the display should blink
void CustomDisplayBehavior::check() {
  dotBlinkCheck();
  blinkCheck();
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
  scrollAsyncFunc = [=]() 
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