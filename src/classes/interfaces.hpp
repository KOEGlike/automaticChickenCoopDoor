#ifndef UI_INTERFACES
#define UI_INTERFACES

#include <functional>
#include <TimeLib.h>
#include "motor.hpp"

class Motor;

struct MoveTimes
{
  MoveTimes(tmElements_t openDoorTime, tmElements_t closeDoorTime)
  {
    openTime = openDoorTime;
    closeTime = closeDoorTime ;
  }
  MoveTimes(uint8_t openHour, uint8_t openMin, uint8_t closeHour, uint8_t closeMin)
  {
    openTime.Hour = openHour; openTime.Minute = openMin; 
    closeTime.Hour = closeHour; closeTime.Minute = closeMin;
  }
  tmElements_t  openTime, closeTime;
};



struct ChickenDoorInterface
{
  ChickenDoorInterface(std::function<MoveTimes()> getFunc,
  std::function<void(MoveTimes )> updateFunc,
  std::function<void(tmElements_t)> updateCurrentTimeFunc,
  std::function<tmElements_t()> getCurrentTimeFunc,
  std::function<Motor*()> getMotorFunc)
  {
    getTimes = getFunc;
    updateTimes = updateFunc;
    updateCurrentTime = updateCurrentTimeFunc;
    getCurrentTime = getCurrentTimeFunc;
    getMotor = getMotorFunc;
  }
  std::function<MoveTimes()> getTimes;
  std::function<void(MoveTimes )> updateTimes;
  std::function<void(tmElements_t )> updateCurrentTime;
  std::function<tmElements_t()> getCurrentTime;
  std::function<Motor*()> getMotor;
};


struct DisplayUiConfig
{
  DisplayUiConfig(uint8_t clk, uint8_t dio, uint8_t btn1, uint8_t btn2, uint8_t btn3)
  {
    clkPin = clk;
    dioPin = dio;
    btn1Pin = btn1;
    btn2Pin = btn2;
    btn3Pin = btn3;
  }
  uint8_t clkPin, dioPin,  btn1Pin,  btn2Pin,btn3Pin;
};

struct MotorCalibrationState
{
  MotorCalibrationState(int botomStep, int topStep)
  {
   
    this->bottomStep = botomStep;
    this->topStep = topStep;
  }
  MotorCalibrationState(){};
  
  int bottomStep, topStep;
};

struct MotorState
{
  MotorState(MotorCalibrationState calibrationState, int currentStep)
  {
    this->calibrationState = calibrationState;
    this->currentStep = currentStep;
  }
  MotorState(){};
  MotorCalibrationState calibrationState;
  int currentStep;
};

struct MotorInterface
{
MotorInterface(std::function<MotorState*()> getMotorStatePtr,std::function<void()> settingStateClosedFunc,std::function<void()> settingStateOpenFunc,std::function<void()>finishedCalibratingfunc)
{
  this->getMotorStatePtr=getMotorStatePtr;
  settingStateOpen=settingStateOpenFunc;
  settingStateClosed=settingStateClosedFunc;
  finishedCalibrating=finishedCalibratingfunc;
}
std::function<MotorState*()> getMotorStatePtr;
std::function<void()> settingStateOpen, settingStateClosed, finishedCalibrating;
};

struct MotorConfig
{
  MotorConfig(uint8_t stepsAmount ,uint8_t dirPin, uint8_t stepPin, uint8_t enablePin, uint8_t m0, uint8_t m1, uint8_t m2)
  {
    dir = dirPin;
    step = stepPin;
    steps = stepsAmount;
    enable = enablePin;
    this->m0=m0;
    this->m1=m1;
    this->m2=m2;
  }
uint8_t steps, dir, step, enable, m0, m1, m2;
};



#endif