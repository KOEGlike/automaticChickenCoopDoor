#ifndef CHICKEN_DOOR_HPP
#define CHICKEN_DOOR_HPP

#include "physical_interface/display_UI.hpp"
#include "UI_interfaces.hpp"
#include <TimeLib.h>
#include <functional>
#include <Arduino.h>

class ChickenDoor{
  public:
    ChickenDoor();
    void begin();
  protected:
  bool isOpen=false;
    std::function<MoveTimes()> get=[&](){return moveTimes; };
    std::function<void(MoveTimes )> update= [&](MoveTimes m_moveTimes){moveTimes=m_moveTimes; };
    std::function<void(tmElements_t )> updateCurrentTime=[&](tmElements_t time){setTime(makeTime(time));};
    std::function<tmElements_t( )> getCurrentTime=[&](){tmElements_t t; breakTime(now(), t); Serial.println(t.Hour); Serial.println(t.Minute); 
      return t ;};
    MoveTimes moveTimes;
    ChickenDoorInterface interface;
    DisplayUiConfig displayUiConfig;
    DisplayUI displayUI;

    
};

#endif