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
    Serial.println("MoveTimes tmElements_t Constructor");
    //delay(500);
  }
  MoveTimes(uint8_t openHour, uint8_t openMin, uint8_t closeHour, uint8_t closeMin)
  {
    openTime.Hour = openHour; openTime.Minute = openMin; 
    closeTime.Hour = closeHour; closeTime.Minute = closeMin;
    Serial.println("MoveTimes uint8_t Constructor");
  }
  //MoveTimes(){Serial.println("MoveTimes def Constructor");delay(500);};
  
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
    Serial.println("ChickenDoorInterface");
    //delay(500);
  }
  ChickenDoorInterface(){Serial.println("ChickenDoorInterface def Constructor");};
  std::function<MoveTimes()> getTimes;
  std::function<void(MoveTimes )> updateTimes;
  std::function<void(tmElements_t )> updateCurrentTime;
  std::function<tmElements_t()> getCurrentTime;
  std::function<Motor*()> getMotor;
};


struct DisplayUiConfig
{
  DisplayUiConfig(uint8_t clk, uint8_t dio, uint8_t btn1, uint8_t btn2)
  {
    clkPin = clk;
    dioPin = dio;
    btn1Pin = btn1;
    btn2Pin = btn2;
    Serial.println("DisplayUiConfig");
    //delay(500);
  }
  uint8_t clkPin, dioPin,  btn1Pin,  btn2Pin;
};

struct MotorCalibrationState
{
  MotorCalibrationState(bool upIsClocwise, long movementLengthInSteps)
  {
    this->upIsClocwise = upIsClocwise;
    this->movementLengthInSteps = movementLengthInSteps;
  }
  MotorCalibrationState(){};
  bool upIsClocwise = true;
  long movementLengthInSteps=0;
};


struct MotorInterface
{
MotorInterface(std::function<uint()> getStateFunc,std::function<void(uint)> setStateFunc,std::function<MotorCalibrationState()> getCalibrationStateFunc,std::function<void(MotorCalibrationState )> setCalibrationStateFunc,std::function<void()> settingStateClosedFunc,std::function<void()> settingStateOpenFunc,std::function<void()>finishedCalibratingfunc)
{
  getState = getStateFunc;
  setState = setStateFunc;
  getCalibrationState = getCalibrationStateFunc;
  setCalibrationState = setCalibrationStateFunc;
  settingStateOpen=settingStateOpenFunc;
  settingStateClosed=settingStateClosedFunc;
  finishedCalibrating=finishedCalibratingfunc;
}
std::function<uint()> getState;
std::function<void(uint)> setState;
std::function<MotorCalibrationState()> getCalibrationState;
std::function<void(MotorCalibrationState )> setCalibrationState;
std::function<void()> settingStateOpen, settingStateClosed, finishedCalibrating;
};

struct MotorConfig
{
  MotorConfig(uint8_t stepsPin ,uint8_t dirPin, uint8_t stepPin, uint8_t resetPin, uint8_t enablePin)
  {
    dir = dirPin;
    step = stepPin;
    steps = stepsPin;
    enable = enablePin;
  }
uint8_t steps, dir, step,   enable;
};



#endif