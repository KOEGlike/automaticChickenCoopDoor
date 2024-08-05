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

// current txt
const std::vector<uint8_t> CURRENT_txt{
SEG_D|SEG_E|SEG_G,//c
SEG_E|SEG_D|SEG_C,//U
SEG_G|SEG_E,//r
SEG_G|SEG_E,//r
SEG_A|SEG_F|SEG_G|SEG_E|SEG_D,//E
SEG_E|SEG_G|SEG_C,//n
SEG_F|SEG_G|SEG_E|SEG_D,//T
};

// txt for open time
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
    customDisplay(config->clkPin, config->dioPin),
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
  customDisplay.begin();
  button1.begin();
  button2.begin();
  buttonPwr.begin();
  ButtonManager.link(std::vector<Button*>{&button1, &buttonPwr}, [&](){Serial.println("1, pw"); startCalibration();});
  ButtonManager.link(std::vector<Button*>{&button2, &buttonPwr}, [&](){Serial.println("2, pw"); editingToggle();});
  asyncIdForClock = Async.registerCallback(1*1000, -1, [&](){TimeElements tm; breakTime(now(), tm);  customDisplay.display.showNumberDecEx(tm.Hour*100+ tm.Minute, 0b01000000);});
  Async.disableCallBack(asyncIdForClock);
  customDisplay.display.clear();
  sleepHandler->addGPIOWakeupSource(config->btn3Pin, LOW);
  }

void DisplayUI::defaultForShowNumber(int num)
{
  customDisplay.display.showNumberDecEx(num, 0b01000000, true);
}

/// @brief gets the time of : current time(0), open time(1), close time(2) 
/// in a format of HHMM
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

/// @brief sets the time of : current time(0), open time(1), close time(2) on the display
/// in a format of HHMM
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

/// @brief  change how many times the dots blink then delay
void DisplayUI::dotTimingRouter(int state)
{
  customDisplay.blinkDotsPeriodically(0b01000000,-1,offTime*offShortMult,onTime*onTimeMult,offTime*offLongMult,1);
}

/// @brief change the current segment
void DisplayUI::mutateCurrentSegment(int amount)
{
  if(isOn==false||!isEditing)return;

  digits.mutateOneDigit(currentSelectedSegment.getState(), amount,false);
  defaultForShowNumber(digits.getDigits());
}


/// @brief turn on or off the display
void DisplayUI::onOffToggle()
{
  if(motor->calibrator.isCalibrating()||isEditing)return;

  if(isOn)
  {
    isOn=false;
    customDisplay.display.setBrightness(0);
    customDisplay.stopAllActivities();
    Async.disableCallBack(asyncIdForClock);
    customDisplay.display.clear();
    sleepHandler->sleepUntilNextAction();
    return;
  }
    isOn=true;
    customDisplay.display.setBrightness(7);
    Async.enableCallBack(asyncIdForClock);
}

/// @brief edits the open && close && current time
void DisplayUI::editingToggle()
{
  if(motor->calibrator.isCalibrating()||!isOn)return;

  if(isEditing)
  {
    isEditing=false;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    timesManager->updateMoveTimes(times);
    customDisplay.stopAllActivities();
    customDisplay.display.clear();
    Async.enableCallBack(asyncIdForClock);
    return;
  }
    Async.disableCallBack(asyncIdForClock);
    customDisplay.stopAllActivities();
    isEditing=true;
    currentChangingTime.setState(0);
    currentSelectedSegment.setState(0);
    times=timesManager->getTimeState().moveTimes;
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defaultForShowNumber(digits.getDigits());
    dotTimingRouter(currentChangingTime.getState());  
    textValueRouter(currentChangingTime.getState());
}

/// @brief display the text for the current time(0), open time(1), close time(2)
void DisplayUI::textValueRouter(int state)
{
  customDisplay.stopAllActivities();
  std::vector<uint8_t> txt;
  switch(state) {

    case 0:txt=CURRENT_txt;
      break;
    case 1:txt=OPEN_txt;
      break;
    case 2:txt=CLOSE_txt;
     break;
  }
  customDisplay.scrollSegmentsAnAmount(txt, 300, 1, [&](){
    dotTimingRouter(currentChangingTime.getState());currentSelectedSegment.setState(0);
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defaultForShowNumber(digits.getDigits());
    customDisplay.blinkSegments(currentSelectedSegment.getStateInBitMask(), offTime, onTime, -1);
    dotTimingRouter(0);
    });
}

/// @brief move the cursor
/// forward is true if the cursor is moving forward
/// forward is false if the cursor is moving backward
void DisplayUI::moveCursor(bool forward)
{
  if(isOn==false||!isEditing||motor->calibrator.isCalibrating())return;
  
  currentSelectedSegment.mutate(forward?1:-1);
  customDisplay.blinkSegments(currentSelectedSegment.getStateInBitMask(), offTime, onTime, -1);
}

/// @brief change the current type time
void DisplayUI::changeCurrentChangingTime()
{
  if(isOn==false||motor->calibrator.isCalibrating()||!isEditing)return;
  
  setTimeRouter(digits.getDigits(), currentChangingTime.getState());
  currentChangingTime.add();
  textValueRouter(currentChangingTime.getState());
  if(currentChangingTime.getState()==0) editingToggle();

}

/// @brief set the calibration state
void DisplayUI::setCalibrationState()
{
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing)return;
  motor->calibrator.setState();
}

/// @brief turn the motor a amount of steps for calibration
/// @param steps the amount of steps to turn
/// @param isClockwise true if the motor is turning clockwise, false if the motor is turning counter clockwise
void DisplayUI::calibrationTurn(uint steps, bool isClockwise)
{
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing)return;
  motor->calibrator.turn(steps, isClockwise);
  customDisplay.display.showNumberDec(motor->calibrator.getCurrentStep());
}

/// @brief start the motor calibration
void DisplayUI::startCalibration()
{
  bool firstIsBottom=true;
  Async.disableCallBack(asyncIdForClock);
  if(!isOn||!motor->calibrator.isCalibrating()||isEditing);
  motor->calibrator.start(firstIsBottom); 
  customDisplay.stopAllActivities();
  customDisplay.scrollSegmentsAnAmount(LOWER_txt, 300, 1);
}

/// @brief switch the door state, open/close it
void DisplayUI::switchDoorState()
{
  if(!isOn)return;
  if(motor->calibrator.isCalibrating())return;
  motor->changeState(motor->getState() >=0.5?0:1);
}


/// @brief what happens when btn1 is pressed a single time shortly
void DisplayUI::btn1ShortFunc()
{
  if (!isOn){
    return;
  }
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
  editingToggle();
}

/// @brief what happens when btn1 is pressed a single time for a long time
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

/// @brief what happens when btn2 is pressed a single time shortly
void DisplayUI::btn2ShortFunc()
{
  if (!isOn){
    return;
  }
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
  startCalibration();
}

/// @brief what happens when btn2 is pressed a single time for a long time
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

/// @brief what happens when pwr-btn is pressed a single time shortly
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
    if(motor->calibrator.firstIsSet())
      customDisplay.scrollSegmentsAnAmount(UPPER_txt, 300, 1);
    if(!motor->calibrator.isCalibrating())
      customDisplay.scrollSegmentsAnAmount(FINISHED_txt, 300, 1, [&](){Async.enableCallBack(asyncIdForClock);});
    return;
  }
  switchDoorState();
}

/// @brief what happens when pwr-btn is pressed a single time for a long time
void DisplayUI::btnPwrLongFunc()
{
  onOffToggle();
  Serial.println("onOffToggle");
}

tmElements_t DisplayUI::getTimeInElements()
{
  tmElements_t time;
  breakTime(now(), time);
  return time;
}