#include "custom_display_behavior.hpp"
#include <functional>

CustomDisplayBehavior::CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO)
  : TM1637Display(pinClk, pinDIO) {}

void CustomDisplayBehavior::blinkCheck() {
  if (millis() - blinkStartInMillis >= _offTime && isBlinking) {
    isBlinking = false;
    setSegments(currentSegments);
    blinkEnd = millis();
    timesBlinked++;
  }
  
  if (isContinuouslyBlinking && millis() - blinkEnd >= _onTime && !isBlinking) {
    blinkSegments(segmentsThatBlink, _offTime);
  }
  
  if (timesToBlink > 0 && timesBlinked == timesToBlink) {
    blinkSegmentsContinuouslyOff();
    timesToBlink = -1;
    bilinkSegmentsAnAmountOnEndFunc();
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
  _offTime = offTime;
  setSegments(segments);
  memcpy(currentSegments, beforeBlinkSegments, segmentsLength);
}

void CustomDisplayBehavior::blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime) {
  isContinuouslyBlinking = true;
  segmentsThatBlink = segmentsToBlink;
  _onTime = onTime;
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

void CustomDisplayBehavior::check() {
  blinkCheck();
}
