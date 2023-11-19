#ifndef CHICKEN_DOOR_HPP
#define CHICKEN_DOOR_HPP

#include "physical_interface/display_UI.hpp"
#include "interfaces.hpp"
#include "motor.hpp"
#include <TimeLib.h>
#include <functional>
#include <Arduino.h>
#include <TimeAlarms.h>

class ChickenDoor{
  public:
    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig);
    void begin();
  protected:
  bool isOpen=false;
    std::function<MoveTimes()> getTimes=[&](){return moveTimes; };
    std::function<void(MoveTimes )> updateTimes= [&](MoveTimes m_moveTimes){moveTimes=m_moveTimes; };
    std::function<void(tmElements_t )> updateCurrentTime=[&](tmElements_t time){setTime(makeTime(time));};
    std::function<tmElements_t( )> getCurrentTime=[&](){tmElements_t t; breakTime(now(), t); return t ;};
    std::function<Motor*()> getMotor=[&](){return &motor;};
    
    std::function<MotorState*()> getMotorStatePtr=[&](){return &motorState;};
    std::function<void()> settingStateOpen=[](){}, settingStateClosed=[](){}, finishedCalibrating=[](){};

    MoveTimes moveTimes;
    MotorState motorState;
    ChickenDoorInterface interface;
    MotorInterface motorInterface;

    Motor motor;

    DisplayUI displayUI;

    
};

#endif