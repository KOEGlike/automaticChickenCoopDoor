#pragma once

#include <functional>
#include <TimeLib.h>



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
  MotorCalibrationState(int bottomStep, int topStep)
  {
   
    this->bottomStep = bottomStep;
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

struct TimeState
{
  TimeState(MoveTimes movetimes, bool sunsetMode, bool autoTime, int offset):moveTimes{movetimes}
  {
    this->offset = offset;
    this->sunsetMode = sunsetMode;
    this->autoTime = autoTime;
  }

  MoveTimes moveTimes;
  bool sunsetMode, autoTime;
  int offset;
};