#ifndef CHICKEN_DOOR_HPP
#define CHICKEN_DOOR_HPP

#include "physical_interface/display_UI.hpp"
#include "interfaces.hpp"
#include "motor.hpp"
#include <TimeLib.h>
#include <functional>
#include <Arduino.h>
#include <TimeAlarms.h>
#include <Preferences.h>
#include <TimeAlarms.h>
#include "WiFiHandler.hpp"

class ChickenDoor{
  public:
    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig);

    void changeDoorState(float percentage);
    MoveTimes getMoveTimes();
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);

    MotorCalibrator getMotorCalibrator();
    MotorState getMotorState();
    void updateMotorState(MotorState motorState);

    bool getSunsetMode();
    bool getAutoTime();

    time_t syncFunc();
    void begin();
  protected:
  bool isOpen=false;
    std::function<MoveTimes()> getTimes=[&](){return moveTimes; };
    std::function<void(MoveTimes )> updateTimes= [&](MoveTimes m_moveTimes){moveTimes=m_moveTimes; saveMoveTimesToMemory(moveTimes);};
    
    std::function<void(tmElements_t )> updateCurrentTime=[&]
    (tmElements_t time)
    {
    setTime(makeTime(time)); 
    if(time.Hour==0&&time.Minute==0)
    {
      pref.putBool("autoTime", true);
      autoTime=true;
    }
    else
    {
      autoTime=false;
      offset=time.Hour-WiFiHandler.UTCTime().Hour;
      pref.putBool("autoTime", false);
      pref.putInt("offset", offset);
    }
    };
    
    std::function<tmElements_t( )> getCurrentTime=[&](){tmElements_t t; breakTime(now(), t); return t ;};
    
    std::function<Motor*()> getMotor=[&](){return &motor;};
    std::function<void()> updateMotorState=[&](){saveMotorStateToMemory(motorState);};

    std::function<MotorState*()> getMotorStatePtr=[&](){return &motorState;};
    std::function<void()> settingStateOpen=[](){}, settingStateClosed=[](){}, finishedCalibrating=[&](){saveMotorStateToMemory(motorState);};

    bool sunsetMode=true, autoTime=true;
    uint8_t offset=0;

    MoveTimes moveTimes;
    MotorState motorState;
    ChickenDoorInterface interface;
    MotorInterface motorInterface;

    Motor motor;
    Preferences pref;
    DisplayUI displayUI;

    void saveMoveTimesToMemory(MoveTimes moveTimes);
    void loadMoveTimesFromMemory();
    void saveMotorStateToMemory(MotorState motorState);
    void loadMotorStateFromMemory();

    
};

#endif