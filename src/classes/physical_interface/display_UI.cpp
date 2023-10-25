#include "display_UI.hpp"
#include <vector>

DisplayUI::DisplayUI(ChickenDoorInterface *interface,DisplayUiConfig *config): 
    button1(config->btn1Pin, [&]() {btn1ShortFunc();},[&]() {btn1LongFunc();}),
    button2(config->btn2Pin, [&]() {btn2ShortFunc();},[&]() {btn2LongFunc();}), 
    buttonPwr{config->btn3Pin, [&](){btnPwrShortFunc();}, [&](){btnPwrLongFunc();}},
    display(config->clkPin, config->dioPin),
    currentSelectedSegment(4), 
    currentChangingTime(3),
    times(interface->getTimes())
{
  m_interface=interface;
}

void DisplayUI::begin()
{
  display.begin();
  button1.begin();
  button2.begin();
  buttonPwr.begin();
  ButtonManager.link(std::vector<Button*>{&button1, &buttonPwr}, [&](){startCaibration();Serial.println("btn 1 pwr");});
  ButtonManager.link(std::vector<Button*>{&button2, &buttonPwr}, [&](){editingTogle();Serial.println("btn 2 pwr");});
  ButtonManager.link(std::vector<Button*>{&button2, &buttonPwr, &button1}, [&](){Serial.println("triple pead");}, 50);
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
    m_interface->updateTimes(times);
    break;
  case 2:
    times.closeTime.Minute=didgets%100;
    times.closeTime.Hour=didgets/100;
    m_interface->updateTimes(times);
    break;
  }
}

void DisplayUI::dotTimeingRouter(int state)
{
  display.blinkDotsAnAmountThenDelayContinuouslyChangeAmount(state+1);
}

void DisplayUI::mutateCurrentSegment(int amount)
{
  if(isOn==false||!isEditing)return;

  digits.mutateOneDigit(currentSelectedSegment.getState(), amount,false);
  defalutForShowNumber(digits.getDigits());
}

void DisplayUI::onOffTogle()
{
  if(m_interface->getMotor()->calibrator.isCalibrating()||isEditing)return;
  
  if(isOn){
    isOn=false;
    display.setBrightness(0);
    display.stopAllActivities();
    display.clear();
    return;
    }
    isOn=true;
    display.setBrightness(7);
    display.scrollSegmentsAnAmount(std::vector<uint8_t>{SEG_G, SEG_G,SEG_F|SEG_E|SEG_G|SEG_B|SEG_C, SEG_A|SEG_F|SEG_G|SEG_E|SEG_D, SEG_F|SEG_E|SEG_D, SEG_F|SEG_E|SEG_D, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F, SEG_G, SEG_G}, 1000, -1);
}

void DisplayUI::editingTogle()
{
  Serial.println("editingTogle");
  if(m_interface->getMotor()->calibrator.isCalibrating()||!isOn)return;

  if(isEditing)
  {
    isEditing=false;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    m_interface->updateTimes(times);
    display.stopAllActivities();
    display.clear();
    return;
  }
    isEditing=true;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    times=m_interface->getTimes();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    dotTimeingRouter(currentChangingTime.getState()); 
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
    display.blinkDotsAnAmountThenDelayContinuously(1, offTime*offLongMult,offTime*offShortMult,onTime*onTimeMult)  ; 
    
}

void DisplayUI::moveCursor(bool forward)
{
  if(isOn==false||!isEditing||m_interface->getMotor()->calibrator.isCalibrating())return;
  
  currentSelectedSegment.add(forward?1:-1);
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
}


void DisplayUI::changeCurrentChangingTime()
{
  if(isOn==false||m_interface->getMotor()->calibrator.isCalibrating()||!isEditing)return;
  
  setTimeRouter(digits.getDigits(), currentChangingTime.getState());
  currentChangingTime.add();
  dotTimeingRouter(currentChangingTime.getState());    
  currentSelectedSegment.setState(0);
  digits.setDigits(digitValueRouter(currentChangingTime.getState()));
  defalutForShowNumber(digits.getDigits());
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);

}

void DisplayUI::setCalobrationState()
{
  if(!isOn||!m_interface->getMotor()->calibrator.isCalibrating()||isEditing)return;
  m_interface->getMotor()->calibrator.setState();
}

void DisplayUI::startCaibration()
{
  Serial.println("startCaibration");
  if(!isOn||!m_interface->getMotor()->calibrator.isCalibrating()||isEditing);
  m_interface->getMotor()->calibrator.start();
}

void DisplayUI::switchDoorState()
{
  if(!isOn)return;
  if(m_interface->getMotor()->calibrator.isCalibrating())return;
  m_interface->getMotor()->changeState(m_interface->getMotor()->getState()>=0.5?0:1);
}


void DisplayUI::btn1ShortFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    m_interface->getMotor()->calibrator.turn(5, false);
    return;
  }
  if(isEditing)
  {
    mutateCurrentSegment(-1);
    return;
  }
}

void DisplayUI::btn1LongFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    m_interface->getMotor()->calibrator.turn(10, false);
    return;
  }
  if(isEditing)
  {
    mutateCurrentSegment(1);
    return;
  }
}

void DisplayUI::btn2ShortFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    m_interface->getMotor()->calibrator.turn(5, true);
    return;
  }
  if(isEditing)
  {
    moveCursor(false);
    return;
  }
}

void DisplayUI::btn2LongFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    m_interface->getMotor()->calibrator.turn(10, true);
    return;
  }
  if(isEditing)
  {
    moveCursor(true);
    return;
  }
}

void DisplayUI::btnPwrShortFunc()
{
  if(isEditing)
  {
    changeCurrentChangingTime();
  }
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    setCalobrationState();
  }
  switchDoorState();
}

void DisplayUI::btnPwrLongFunc()
{
  onOffTogle();
}