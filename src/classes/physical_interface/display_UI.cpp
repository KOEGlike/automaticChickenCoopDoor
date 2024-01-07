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
SEG_E|SEG_D|SEG_C,//U
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

const std::vector<uint8_t> CURRENT_txt{
SEG_D|SEG_E|SEG_G,//c
SEG_E|SEG_D|SEG_C,//U
SEG_G|SEG_E,//r
SEG_G|SEG_E,//r
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_E|SEG_G|SEG_C,//n
SEG_F|SEG_G|SEG_E|SEG_D,//T
};

const std::vector<uint8_t> OPEN_txt{
SEG_C|SEG_D|SEG_E|SEG_G,//o
SEG_A|SEG_B|SEG_E|SEG_F|SEG_G,//P
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_E|SEG_G|SEG_C//n
};

const std::vector<uint8_t> CLOSE_txt{
SEG_D|SEG_E|SEG_G,//c
SEG_F| SEG_E|SEG_D|SEG_C,//L
SEG_C|SEG_D|SEG_E|SEG_G,//o
SEG_A|SEG_F|SEG_G|SEG_C|SEG_D,//S
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D//E
};

DisplayUI::DisplayUI(TimesManager* timesManager,Motor* motor, DisplayUiConfig *config, SleepHandler* sleepHandler): 
    button1(config->btn1Pin, [&]() {btn1ShortFunc();},[&]() {btn1LongFunc();}),
    button2(config->btn2Pin, [&]() {btn2ShortFunc();},[&]() {btn2LongFunc();}), 
    buttonPwr{config->btn3Pin, [&](){btnPwrShortFunc();}, [&](){btnPwrLongFunc();}},
    display(config->clkPin, config->dioPin),
    currentSelectedSegment(4), 
    currentChangingTime(3),
    times(timesManager->getTimeState().moveTimes)
{
  
  this->motor=motor;
  this->timesManager=timesManager;
  this->sleepHandler=sleepHandler;
  this->config=config;
}

DisplayUiConfig* DisplayUI::getConfig()
{
  return config;
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
{tmElements_t currentTime= getTimeInElements();
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
  tmElements_t currentTime;
  currentTime.Day=1;
  switch(state) {
  case 0:
  
    currentTime.Hour=digits/100;
    currentTime.Minute=digits%100;
    timesManager->updateCurrentTime(currentTime);
    break;
  case 1:
    times.openTime.Minute=digits%100;
    times.openTime.Hour=digits/100;
    timesManager->updateMoveTimes(times);
    break;
  case 2:
    times.closeTime.Minute=digits%100;
    times.closeTime.Hour=digits/100;
    timesManager->updateMoveTimes(times);
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
  if(motor->calibrator.isCalibrating()||isEditing)return;
  
  if(isOn)
  {
    isOn=false;
    display.setBrightness(0);
    display.stopAllActivities();
    display.clear();
    sleepHandler->sleepUntilNextAction();
    return;
  }
    isOn=true;
    display.setBrightness(7);
    display.scrollSegmentsAnAmount(std::vector<uint8_t>{SEG_G, SEG_G,SEG_F|SEG_E|SEG_G|SEG_B|SEG_C, SEG_A|SEG_F|SEG_G|SEG_E|SEG_D, SEG_F|SEG_E|SEG_D, SEG_F|SEG_E|SEG_D, SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F, SEG_G, SEG_G}, 1000, -1);
}

void DisplayUI::editingToggle()
{
  if(motor->calibrator.isCalibrating()||!isOn)return;

  if(isEditing)
  {
    isEditing=false;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
   timesManager->updateMoveTimes(times);
    display.stopAllActivities();
    display.clear();
    return;
  }
    display.stopAllActivities();
    isEditing=true;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    times=timesManager->getTimeState().moveTimes;
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defaultForShowNumber(digits.getDigits());
    dotTimingRouter(currentChangingTime.getState());  
    textValueRouter(currentChangingTime.getState());
}

void DisplayUI::textValueRouter(int state)
{
  display.stopAllActivities();
  std::vector<uint8_t> txt;
  switch(state) {

    case 0:txt=CURRENT_txt;
      break;
    case 1:txt=OPEN_txt;
      break;
    case 2:txt=CLOSE_txt;
     break;
  }
  display.scrollSegmentsAnAmount(txt, 300, 1, [&](){
    dotTimingRouter(currentChangingTime.getState());currentSelectedSegment.setState(0);
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defaultForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
    display.blinkDotsAnAmountThenDelayContinuously(1, offTime*offLongMult,offTime*offShortMult,onTime*onTimeMult)  ;
    });
}

void DisplayUI::moveCursor(bool forward)
{
  if(isOn==false||!isEditing||motor->calibrator.isCalibrating())return;
  
  currentSelectedSegment.add(forward?1:-1);
  display.changeSegmentsContinuos(currentSelectedSegment.getStateInBitMask(), offTime, onTime);
}


void DisplayUI::changeCurrentChangingTime()
{
  if(isOn==false||motor->calibrator.isCalibrating()||!isEditing)return;
  
  setTimeRouter(digits.getDigits(), currentChangingTime.getState());
  currentChangingTime.add();
  textValueRouter(currentChangingTime.getState());
  if(currentChangingTime.getState()==0) editingToggle();

}

void DisplayUI::setCalibrationState()
{
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing)return;
  motor->calibrator.setState();
}

void DisplayUI::calibrationTurn(uint steps, bool isClockwise)
{
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing)return;
  motor->calibrator.turn(steps, isClockwise);
  display.showNumberDec(motor->calibrator.getCurrentStep());
}

void DisplayUI::startCalibration()
{
  bool firstIsBottom=true;
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing);
  motor->calibrator.start(firstIsBottom); 
  display.stopAllActivities();
  display.scrollSegmentsAnAmount(LOWER_txt, 300, 1);
}

void DisplayUI::switchDoorState()
{
  if(!isOn)return;
  if(motor->calibrator.isCalibrating())return;
  motor->changeState(motor->getState() >=0.5?0:1);
}


void DisplayUI::btn1ShortFunc()
{
  if(motor->calibrator.isCalibrating())
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
  if(motor->calibrator.isCalibrating())
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
  if(motor->calibrator.isCalibrating())
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
  if(motor->calibrator.isCalibrating())
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
  if(motor->calibrator.isCalibrating())
  {
    setCalibrationState();
    if(motor->calibrator.firstIsSet())display.scrollSegmentsAnAmount(UPPER_txt, 300, 1);
    if(!motor->calibrator.isCalibrating())display.scrollSegmentsAnAmount(FINISHED_txt, 300, 1);
    return;
  }
  switchDoorState();
}

void DisplayUI::btnPwrLongFunc()
{
  onOffToggle();
}

tmElements_t DisplayUI::getTimeInElements()
{
  tmElements_t time;
  breakTime(now(), time);
  return time;
}