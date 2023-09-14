#include "custom_display_behavior.hpp"
#include <functional>
#include <Arduino.h>
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO)
  : TM1637Display(pinClk, pinDIO) {
    Async.registerCallback(0,-1, [&](){check();});
  }

void CustomDisplayBehavior::blinkCheck() {
  if (millis() - blinkStartInMillis >= m_offTime && isBlinking) {
    isBlinking = false;
    uint8_t segments[4];
    memcpy(segments, currentSegments, segmentsLength);
    if(dotIsBlinking)
    {
      segments[1]&=~0b10000000;
    }
    setSegments(segments);
    blinkEnd = millis();
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
    dotIsBlinking = false;
    setSegments(currentSegments);
    dotBlinkEnd = millis();
    Serial.println("dotBlinkCheck");
  }
  
  if (dotIsContinuouslyBlinking && millis() - dotBlinkEnd >= m_dotOnTime && !dotIsBlinking) {
    blinkDots(m_dotOffTime);
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
  
  blinkStartInMillis = millis();
  m_offTime = offTime;
  setSegments(segments);
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

void CustomDisplayBehavior::check() {
  blinkCheck();
  dotBlinkCheck();
}