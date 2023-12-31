#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO)
  : TM1637Display(pinClk, pinDIO) 
  {
  }
  CustomDisplayBehavior :: ~CustomDisplayBehavior() {
  Async.deleteCallBack(asyncId);
  }

void CustomDisplayBehavior::begin() { 

Async.registerCallback(0,-1, [&](){check();});

} 

void CustomDisplayBehavior::blinkCheck() {
  if (millis() - blinkStartInMillis >= m_offTime && isBlinking) {
    blinkEnd = millis();
    isBlinking = false;
    uint8_t segments[4];
    
    memcpy(segments, currentSegments, segmentsLength);
    if(dotIsBlinking)
    {
      segments[1]&=~0b10000000;
    }
    if(dotIsOn)
    {
      segments[1]|=0b10000000;
    }
    setSegments(segments);
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

void CustomDisplayBehavior::dotBlinkCheck() {
 
  if (millis() - dotBlinkStartInMillis >= m_dotOffTime && dotIsBlinking) {
    dotBlinkEnd = millis();
    dotIsBlinking = false;
    uint8_t segments[4];
    memcpy(segments, currentSegments, segmentsLength);
    if(isBlinking)
    {
      segments[1]=0;
    }
    dotIsOn=true;
    segments[1]|=0b10000000;
    setSegments(currentSegments);
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
    blinkDotsAnAmount(dotBlinkAnAmountLongDelayContinuosAmount, blinkDotsAnAmountThenDelayContinuouslyOffTime,blinkDotsAnAmountThenDelayContinuouslyOnTime, [&](){dotBlinkAnAmountLongDelayContinuosStart=millis(); isDotBlinkAnAmountLongDelayContinuos=true;} );
  }
}

void CustomDisplayBehavior::blinkSegments(uint8_t segmentsToBlink, unsigned long offTime) {
  if (isBlinking) {
    return;
  }
  isBlinking = true;
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
  setSegments(segments);
  segmentsThatBlink=segmentsToBlink;
  memcpy(currentSegments, beforeBlinkSegments, segmentsLength);
}

void CustomDisplayBehavior::blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime) {
  isContinuouslyBlinking = true;
  segmentsThatBlink = segmentsToBlink;
  m_onTime = onTime;
  blinkSegments(segmentsThatBlink, offTime);
}

void CustomDisplayBehavior::blinkSegmentsContinuouslyOff() {
  isContinuouslyBlinking = false;
}

void CustomDisplayBehavior::changeSegmentsContinuos(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime)
{
  segmentsThatBlink=segmentsToBlink;
  m_offTime=offTime;
  m_onTime=onTime;
}

void CustomDisplayBehavior::blinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  timesBlinked = 0;
  timesToBlink = amount;
  blinkSegmentsAnAmountOnEndFunc = onEnd;
  blinkSegmentsContinuouslyOn(segmentsToBlink, offTime, onTime);
}

void CustomDisplayBehavior::blinkDots(unsigned long offTime){

  if (dotIsBlinking) {
    return;
  }
  
  
  uint8_t beforeBlinkSegments[4];
  memcpy(beforeBlinkSegments, currentSegments, segmentsLength);
  uint8_t segments[4];
  
memcpy(segments, currentSegments, segmentsLength);
  m_dotOffTime = offTime;
  dotIsBlinking = true;
  dotIsOn=false;
  segments[1]&=~0b10000000;
  dotBlinkStartInMillis = millis();
  setSegments(segments);
  memcpy(currentSegments, beforeBlinkSegments, segmentsLength);
  
}

void CustomDisplayBehavior::blinkDotsContinuouslyOn( unsigned long offTime, unsigned long onTime) {
  dotIsContinuouslyBlinking = true;
  m_dotOnTime = onTime;
  blinkDots(offTime);
}

void CustomDisplayBehavior::blinkDotsContinuouslyOff() {
  dotIsContinuouslyBlinking = false;
}

void CustomDisplayBehavior::blinkDotsAnAmount( unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  timesDotBlinked = 0;
  timesDotToBlink = amount;
  blinkDotsAnAmountOnEndFunc = onEnd;
  blinkDotsContinuouslyOn(offTime, onTime);
}

void CustomDisplayBehavior::blinkDotsAnAmountThenDelayContinuously(unsigned int amount, unsigned long longOffTime ,unsigned long offTime , unsigned long onTime)
{
  dotBlinkAnAmountLongDelayContinuos=longOffTime;
  blinkDotsAnAmountThenDelayContinuouslyOnTime=onTime;
  blinkDotsAnAmountThenDelayContinuouslyOffTime=offTime;
  dotBlinkAnAmountLongDelayContinuosAmount=amount;
  blinkDotsAnAmount(amount, offTime, onTime, [&](){dotBlinkAnAmountLongDelayContinuosStart=millis(); isDotBlinkAnAmountLongDelayContinuos=true; });
}

void CustomDisplayBehavior::blinkDotsAnAmountThenDelayContinuouslyChangeAmount(unsigned int amount)
{
  dotBlinkAnAmountLongDelayContinuosAmount=amount;
}

void CustomDisplayBehavior::check() {
  dotBlinkCheck();
  blinkCheck();
}

void CustomDisplayBehavior::scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount, std::function<void()> onEnd)
{
  scrollCycles=0;
  segmentsToScroll=segments;
  scrollAmount=amount;
  scrollSegmentsOnEnd=onEnd;
  std::function<void()> 
  scrollAsyncFunc = [&]() 
  {
   if(scrollCycles>segmentsToScroll.size()-1) {scrollCycles=0;}
   if(scrollCycles/scrollAmount>=scrollAmount-1&&scrollAmount>=0&&scrollCycles>segmentsToScroll.size()-4) {scrollSegmentsOnEnd(); scrollSegmentsContinuouslyOff(); return;}
    uint8_t segmentsToDisplay[4];
    for(int i=0;i<4;i++)
    {
      segmentsToDisplay[i]=segmentsToScroll[scrollCycles+i<segmentsToScroll.size()?scrollCycles+i:((scrollCycles+i)-segmentsToScroll.size())];
    }
    setSegments(segmentsToDisplay);
    scrollCycles++;
  };
  scrollAsyncId= Async.registerCallback(millisForOneMove, -1, scrollAsyncFunc);
}

void CustomDisplayBehavior::scrollSegmentsContinuouslyOff()
{
  
  Async.deleteCallBack(scrollAsyncId);
}

void CustomDisplayBehavior::stopAllActivities()
{
  dotBlinkAnAmountLongDelayContinuos=-1;dotBlinkAnAmountLongDelayContinuosStart; 
  timesBlinked = 0; timesToBlink = -1;timesDotBlinked = 0; timesDotToBlink = -1;
  isBlinking = false; isContinuouslyBlinking = false; dotIsBlinking=false;dotIsContinuouslyBlinking = false; dotIsOn=false;isDotBlinkAnAmountLongDelayContinuos=false;
  scrollSegmentsContinuouslyOff();
}