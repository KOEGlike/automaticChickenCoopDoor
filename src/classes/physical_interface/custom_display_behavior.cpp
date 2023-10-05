#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO)
  : TM1637Display(pinClk, pinDIO) {
    //Serial.println("CustomDisplayBehavior constuct");
    //delay(500);
    
  }
  CustomDisplayBehavior :: ~CustomDisplayBehavior() {
  Async.deleteCallBack(asyncId);
  }

void CustomDisplayBehavior::begin() { 
Serial.println("CustomDisplayBehavior begin");
Async.registerCallback(0,-1, [&](){check();});
Serial.println("CustomDisplayBehavior begin check");
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
    bilinkSegmentsAnAmountOnEndFunc();
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
    bilinkDotsAnAmountOnEndFunc();
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

void CustomDisplayBehavior::bilinkSegmentsAnAmount(uint8_t segmentsToBlink, unsigned int amount, unsigned long offTime, unsigned long onTime, std::function<void()> onEnd) {
  timesBlinked = 0;
  timesToBlink = amount;
  bilinkSegmentsAnAmountOnEndFunc = onEnd;
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
  bilinkDotsAnAmountOnEndFunc = onEnd;
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