#include "display_UI.hpp"
#include <vector>
#include <array>


//lower txt
const std::vector<uint8_t>LOWER_txt{
SEG_F|SEG_E|SEG_D,//L
SEG_C|SEG_D|SEG_E|SEG_G,//o
SEG_E|SEG_D|SEG_C, SEG_E|SEG_D|SEG_C, //w
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_G|SEG_E//r
};

//upper txt
const std::vector<uint8_t> UPPER_txt{
SEG_F|SEG_E|SEG_D|SEG_C|SEG_B,//U
SEG_A|SEG_B|SEG_E|SEG_F|SEG_G,//P
SEG_A|SEG_B|SEG_E|SEG_F|SEG_G,//P
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_G|SEG_E//r
};

//finished txt
const std::vector<uint8_t> FINISHED_txt{
SEG_A|SEG_F|SEG_G|SEG_E,//F
SEG_F|SEG_E,//I
SEG_E|SEG_G|SEG_C,//n
SEG_F|SEG_E,//I
SEG_A|SEG_F|SEG_G|SEG_C|SEG_D,//S
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_E|SEG_G|SEG_C|SEG_D|SEG_B//d
};

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
  ButtonManager.link(std::vector<Button*>{&button1, &buttonPwr}, [&](){startCalibration();});
  ButtonManager.link(std::vector<Button*>{&button2, &buttonPwr}, [&](){editingToggle();});
}

void DisplayUI::defaultForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b01000000, true);
}

int DisplayUI::digitValueRouter(int state)
{tmElements_t currentTime= m_interface->getCurrentTime();
  switch(state) {
  case 0:
    return currentTime.Hour*100+currentTime.Minute; 
  case 1:
   return times.openTime.Hour*100+times.openTime.Minute;
  case 2:
    return times.closeTime.Hour*100+times.closeTime.Minute;
  default:
    return 0;
  }
}

void DisplayUI::setTimeRouter(int digits, int state)
{
  switch(state) {
  case 0:
  tmElements_t currentTime;
    currentTime.Hour=digits/100;
    currentTime.Minute=digits%100;
    m_interface->updateCurrentTime(currentTime);
    break;
  case 1:
    times.openTime.Minute=digits%100;
    times.openTime.Hour=digits/100;
    m_interface->updateTimes(times);
    break;
  case 2:
    times.closeTime.Minute=digits%100;
    times.closeTime.Hour=digits/100;
    m_interface->updateTimes(times);
    break;
  }
}

void DisplayUI::dotTimingRouter(int state)
{
  display.blinkDotsAnAmountThenDelayContinuouslyChangeAmount(state+1);
}

void DisplayUI::mutateCurrentSegment(int amount)
{
  if(isOn==false||!isEditing)return;

  digits.mutateOneDigit(currentSelectedSegment.getState(), amount,false);
  defaultForShowNumber(digits.getDigits());
}

void DisplayUI::onOffToggle()
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

void DisplayUI::editingToggle()
{
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
    display.stopAllActivities();
    isEditing=true;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    times=m_interface->getTimes();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defaultForShowNumber(digits.getDigits());
    dotTimingRouter(currentChangingTime.getState()); 
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
  dotTimingRouter(currentChangingTime.getState());    
  currentSelectedSegment.setState(0);
  digits.setDigits(digitValueRouter(currentChangingTime.getState()));
  defaultForShowNumber(digits.getDigits());
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);

}

void DisplayUI::setCalibrationState()
{
  if(!isOn||!m_interface->getMotor()->calibrator.isCalibrating()||isEditing)return;
  m_interface->getMotor()->calibrator.setState();
}

void DisplayUI::calibrationTurn(uint steps, bool isClockwise)
{
  if(!isOn||!m_interface->getMotor()->calibrator.isCalibrating()||isEditing)return;
  m_interface->getMotor()->calibrator.turn(steps, isClockwise);
  display.showNumberDec(m_interface->getMotor()->calibrator.getCurrentStep());
}

void DisplayUI::startCalibration()
{
  bool firstIsBottom=true;
  if(!isOn||!m_interface->getMotor()->calibrator.isCalibrating()||isEditing);
  m_interface->getMotor()->calibrator.start(firstIsBottom); 
  display.stopAllActivities();
  std::vector<uint8_t> txtVec;
  txtVec=firstIsBottom?LOWER_txt:UPPER_txt;
  display.scrollSegmentsAnAmount(txtVec, 300, 1, [&](){display.showNumberDec(m_interface->getMotor()->calibrator.getCurrentStep());});
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
    calibrationTurn(5, false);
    return;
  }
  if(isEditing)
  {
    mutateCurrentSegment(1);
    return;
  }
}

void DisplayUI::btn1LongFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
   calibrationTurn(10, false);
    return;
  }
  if(isEditing)
  {
    mutateCurrentSegment(-1);
    return;
  }
}

void DisplayUI::btn2ShortFunc()
{
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    calibrationTurn(5, true);
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
    calibrationTurn(10, true);
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
    return;
  }
  if(m_interface->getMotor()->calibrator.isCalibrating())
  {
    setCalibrationState();
    return;
  }
  switchDoorState();
}

void DisplayUI::btnPwrLongFunc()
{
  onOffToggle();
}