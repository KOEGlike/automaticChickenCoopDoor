#ifndef CHICKEN_DOOR_HPP
#define CHICKEN_DOOR_HPP

#include "physical_interface/display_UI.hpp"
#include "UI_interfaces.hpp"
#include <TimeLib.h>
#include <functional>

class ChickenDoor{
  public:
    ChickenDoor();
  protected:
    MoveTimes moveTimes;
    ChickenDoorInterface interface;

    DisplayUiConfig displayUiConfig;
    DisplayUI displayUI;

    std::function<MoveTimes()> get=[&](){return moveTimes; };
    std::function<void(MoveTimes )> update= [&](MoveTimes m_moveTimes){moveTimes=m_moveTimes; };
    std::function<void(tmElements_t )> updateCurrentTime=[&](tmElements_t time){setTime(makeTime(time));};


};

#endif