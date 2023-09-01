#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>

#include "src/classes/button.hpp"
#include "src/classes/custom_display_behavior.hpp"
#include "src/classes/four_didget_time.hpp"
#include "src/classes/counter.hpp"

#define CLK 21
#define DIO 22
#define BTN1 19
#define BTN2 18

A4988 lol(128, 2,3);


unsigned char openTime=0, closeTime=0;
bool globalPressed = false, isEditing=false;

CustomDisplayBehavior display(CLK, DIO);
Preferences preferences;
FourDigitTime digits;
StateCounter currentSelectedSegment(4);
StateCounter currentChangingTime(3);

void defalutForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b11100000, true);
}

int  digitValueRouter(int state)
{
  switch(state) {
  case 0:
    return hour(now())*100+minute(now());
  case 1:
    return openTime;
  case 2:
    return closeTime;
  default:
    return 0;
  }
}

void setTimeRouter(int didgets, int state)
{
  switch(state) {
  case 0:
    setTime(didgets/100, didgets%100, 0, 0, 0, 0);
    break;
  case 1:
     openTime=didgets;
     break;
  case 2:
     closeTime=didgets;
    break;
  }
}

Button button1
(
  BTN1, &globalPressed, []() {   
    digits.mutateOneDigit(currentSelectedSegment.getState(), 1);
    defalutForShowNumber(digits.getDigits());
  },
  []() {
    if(isEditing==false){
    isEditing=true;
    display.setBrightness(7);
    currentSelectedSegment.add();
    currentChangingTime.add();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
    }
    else
    {
      isEditing=false;
      preferences.putUChar("openTime",openTime);
      preferences.putUChar("closeTime",closeTime);
      display.blinkSegmentsContinuouslyOff();
      display.setBrightness(0);
      display.clear();
    }
  });

Button button2(
  BTN2, &globalPressed, []() {
    currentSelectedSegment.add();
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
  },
  []() {
    setTimeRouter(digits.getDigits(), currentChangingTime.getState());
    currentChangingTime.add();
    currentSelectedSegment.setState(0);
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
  });



void setup() {
  Serial.begin(9600);
  preferences.begin("times", false); 
  
  openTime=preferences.getUChar("openTime",0);
  closeTime=preferences.getUChar("closeTime", 0);

}

void checks() {
  button1.check();
  button2.check();
  display.check();
}

void loop() {
  checks();
}
