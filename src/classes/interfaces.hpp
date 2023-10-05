#ifndef UI_INTERFACES
#define UI_INTERFACES

#include <functional>
#include <TimeLib.h>
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
   std::function<void()> openDoorFunc,
  std::function<void()> closeDoorFunc,
  std::function<bool()> getDoorStateFunc)
  {
    get = getFunc;
    update = updateFunc;
    updateCurrentTime = updateCurrentTimeFunc;
    getCurrentTime = getCurrentTimeFunc;
    openDoor = openDoorFunc;
    closeDoor = closeDoorFunc;
    getDoorState = getDoorStateFunc;
    Serial.println("ChickenDoorInterface");
    //delay(500);
  }
  ChickenDoorInterface(){Serial.println("ChickenDoorInterface def Constructor");delay(500);};
  std::function<MoveTimes()> get;
  std::function<void(MoveTimes )> update;
  std::function<void(tmElements_t )> updateCurrentTime;
  std::function<tmElements_t()> getCurrentTime;
  std::function<void()> openDoor;
  std::function<void()> closeDoor;
  std::function<bool()> getDoorState;
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

struct MotorInterface
{
MotorInterface(std::function<void()> getStateFunc,std::function<void()> setStateFunc,std::function<void()> getCalibrationStateFunc)
{
  getState = getStateFunc;
  setState = setStateFunc;
  getCalibrationState = getCalibrationStateFunc;
}
std::function<void()> getState;
std::function<void()> setState;
std::function<void()> getCalibrationState;
};

struct MotorConfig
{
  MotorConfig(uint8_t dirPin, uint8_t stepPin, uint8_t resetPin, uint8_t enablePin, uint8_t ms1Pin, uint8_t ms2Pin, uint8_t ms3Pin)
  {
    dir = dirPin;
    step = stepPin;
    reset = resetPin;
    enable = enablePin;
    ms1 = ms1Pin;
    ms2 = ms2Pin;
    ms3 = ms3Pin;
  }
uint8_t dir, step, reset,  enable, ms1, ms2, ms3;
};

#endif