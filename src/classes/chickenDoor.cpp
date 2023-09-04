#include "chickenDoor.hpp"

ChickenDoor::ChickenDoor(uint8_t clkPin,uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin)
{
  clk=clkPin;
  dio=dioPin;
  btn1=btn1Pin;
  btn2=btn2Pin;
  preferences.begin("times", false); 
  openTime=preferences.getUChar("openTime",0);
  closeTime=preferences.getUChar("closeTime", 0);
}

void ChickenDoor::checks()
{
  button1.check();
  button2.check();
  display.check();
}

void ChickenDoor::defalutForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b11100000, true);
}

int ChickenDoor::digitValueRouter(int state)
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

void ChickenDoor::setTimeRouter(int didgets, int state)
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

void ChickenDoor::addToCurrentSegment()
{
  if(isEditing==false){
  return;
  }

  digits.mutateOneDigit(currentSelectedSegment.getState(), 1,false);
  defalutForShowNumber(digits.getDigits());
}

void ChickenDoor::editingTogle()
{
  if(isEditing){
    isEditing=false;
    preferences.putUChar("openTime",openTime);
    preferences.putUChar("closeTime",closeTime);
    display.blinkSegmentsContinuouslyOff();
    display.setBrightness(0);
    display.clear();
    return;
    }
    isEditing=true;
    display.setBrightness(7);
    currentSelectedSegment.add();
    currentChangingTime.add();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
}

void ChickenDoor::moveCursorForward()
{
  currentSelectedSegment.add();
  display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
}


void ChickenDoor::changeCurrentChangingTime()
{
  if(isEditing==false){
  return;
  }

  setTimeRouter(digits.getDigits(), currentChangingTime.getState());
  currentChangingTime.add();
  currentSelectedSegment.setState(0);
  digits.setDigits(digitValueRouter(currentChangingTime.getState()));
  defalutForShowNumber(digits.getDigits());
  display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
}