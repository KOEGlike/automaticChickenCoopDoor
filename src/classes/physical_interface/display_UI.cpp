#include "display_UI.hpp"

DisplayUI::DisplayUI(ChickenDoorInterface *interface,DisplayUiConfig *config): 
    button1(config->btn1Pin, [&]() {   addToCurrentSegment();},[&]() {editingTogle();}, &globalPressed),
    button2 (config->btn2Pin, [&]() {moveCursorForward();},[&]() {changeCurrentChangingTime();}, &globalPressed), 
    display(config->clkPin, config->dioPin),
    currentSelectedSegment(4), 
    currentChangingTime(3),
    times(interface->get())
{
  m_interface=interface;
  //Serial.println("DisplayUi constructor");
  //delay(500);
}

void DisplayUI::begin()
{
  display.begin();
  button1.begin();
  button2.begin();
}

void DisplayUI::defalutForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b01000000, true);
}

int DisplayUI::digitValueRouter(int state)
{tmElements_t currrentTime= m_interface->getCurrentTime();
  switch(state) {
  case 0:
     
    return currrentTime.Hour*100+currrentTime.Minute; 
  case 1:
   return times.openTime.Hour*100+times.openTime.Minute;
  case 2:
    return times.closeTime.Hour*100+times.closeTime.Minute;
  default:
    return 0;
  }
}

void DisplayUI::setTimeRouter(int didgets, int state)
{
  switch(state) {
  case 0:
  tmElements_t currentTime;
    currentTime.Hour=didgets/100;
    currentTime.Minute=didgets%100;
    m_interface->updateCurrentTime(currentTime);
    break;
  case 1:
    times.openTime.Minute=didgets%100;
    times.openTime.Hour=didgets/100;
    m_interface->update(times);
    break;
  case 2:
    times.closeTime.Minute=didgets%100;
    times.closeTime.Hour=didgets/100;
    m_interface->update(times);
    break;
  }
}

void DisplayUI::dotTimeingRouter(int state)
{
  display.blinkDotsAnAmountThenDelayContinuouslyChangeAmount(state+1);
}

void DisplayUI::addToCurrentSegment()
{
  if(isEditing==false){
  return;
  }
  digits.mutateOneDigit(currentSelectedSegment.getState(), 1,false);
  defalutForShowNumber(digits.getDigits());
}

void DisplayUI::editingTogle()
{
  Serial.println("editingToglewew");
  if(isEditing){
    isEditing=false;
    Serial.println("editingTogle");
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    m_interface->update(times);
    display.blinkSegmentsContinuouslyOff();
    display.blinkDotsContinuouslyOff();
    display.setBrightness(0);
    display.clear();
    return;
    }
    isEditing=true;
    display.setBrightness(7);
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    times=m_interface->get();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    dotTimeingRouter(currentChangingTime.getState()); 
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
    display.blinkDotsAnAmountThenDelayContinuously(1, offTime*offLongMult,offTime*offShortMult,onTime*onTimeMult)  ; 
    
}

void DisplayUI::moveCursorForward()
{
  currentSelectedSegment.add();
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
}


void DisplayUI::changeCurrentChangingTime()
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

