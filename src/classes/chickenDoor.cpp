#include "chickenDoor.hpp"

ChickenDoor::ChickenDoor(uint8_t clkPin,uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin)
{
  clk=clkPin;
  dio=dioPin;
  btn1=btn1Pin;
  btn2=btn2Pin;
  preferences.begin("times", false); 
  openTime=preferences.getUInt("openTime",0);
  closeTime=preferences.getUInt("closeTime", 0);
}

void ChickenDoor::defalutForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b01000000, true);
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
    //Serial.println(openTime);
    break;
  case 2:
    closeTime=didgets;
    //Serial.println(closeTime);
    break;
  }
}

void ChickenDoor::dotTimeingRouter(int state)
{
  display.blinkDotsAnAmountThenDelayContinuouslyChangeAmount(state+1);
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
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    //Serial.println(openTime);
    //Serial.println(closeTime);
    preferences.putUInt("openTime",openTime);
    preferences.putUInt("closeTime",closeTime);
    display.blinkSegmentsContinuouslyOff();
    display.setBrightness(0);
    display.clear();
    return;
    }
    isEditing=true;
    display.setBrightness(7);
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    openTime=preferences.getUInt("openTime",0);
    closeTime=preferences.getUInt("closeTime", 0);
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    dotTimeingRouter(currentChangingTime.getState()); 
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
    display.blinkDotsAnAmountThenDelayContinuously(2, offTime*offLongMult,offTime*offShortMult,onTime*onTimeMult)  ; 
    
}

void ChickenDoor::moveCursorForward()
{
  currentSelectedSegment.add();
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
}


void ChickenDoor::changeCurrentChangingTime()
{
  if(isEditing==false){
  return;
  }

  setTimeRouter(digits.getDigits(), currentChangingTime.getState());
  currentChangingTime.add();
  dotTimeingRouter(currentChangingTime.getState());    
  currentSelectedSegment.setState(0);
  digits.setDigits(digitValueRouter(currentChangingTime.getState()));
  defalutForShowNumber(digits.getDigits());
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
}