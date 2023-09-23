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
    Serial.println("MoveTimes Constructor");
    //delay(500);
  }
  //MoveTimes(){Serial.println("MoveTimes def Constructor");delay(500);};
  
  tmElements_t  openTime, closeTime;
};

struct ChickenDoorInterface
{
  ChickenDoorInterface(std::function<MoveTimes()> getFunc,
  std::function<void(MoveTimes )> updateFunc,
  std::function<void(tmElements_t)> updateCurrentTimeFunc)
  {
    get = getFunc;
    update = updateFunc;
    updateCurrentTime = updateCurrentTimeFunc;
    Serial.println("ChickenDoorInterface");
    //delay(500);
  }
  ChickenDoorInterface(){Serial.println("ChickenDoorInterface def Constructor");delay(500);};
  std::function<MoveTimes()> get;
  std::function<void(MoveTimes )> update;
  std::function<void(tmElements_t )> updateCurrentTime;
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
  DisplayUiConfig(){
    Serial.println("DisplayUiConfig def Constructor");
    //delay(500);
  };
  uint8_t clkPin, dioPin,  btn1Pin,  btn2Pin;
};

#endif