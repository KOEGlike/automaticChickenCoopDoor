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
    ChickenDoor(DisplayUiConfig displayUiConfig);
    void begin();
  protected:
  bool isOpen=false;
    std::function<MoveTimes()> get=[&](){return moveTimes; };
    std::function<void(MoveTimes )> update= [&](MoveTimes m_moveTimes){moveTimes=m_moveTimes; };
    std::function<void(tmElements_t )> updateCurrentTime=[&](tmElements_t time){setTime(makeTime(time));};
    std::function<tmElements_t( )> getCurrentTime=[&](){tmElements_t t; breakTime(now(), t); return t ;};
    std::function<void()> openDoor=[&](){};
    std::function<void()> closeDoor=[&](){};
    std::function<bool()> getDoorState=[&](){return true;};
    
    MoveTimes moveTimes;
    ChickenDoorInterface interface;
    
    DisplayUI displayUI;

    
};

#endif