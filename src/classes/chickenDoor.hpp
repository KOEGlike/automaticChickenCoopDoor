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

class Motor;
class MoveTimes;
class DisplayUiConfig;
class MotorConfig;
class MotorState;
class MotorCalibrator;
class DisplayUI;

class ChickenDoor{
  

  public:
    friend class Motor;

    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig);

    void changeDoorState(float percentage);
    float getDoorOpennessInPercentage();
    MotorState getMotorState();

    MoveTimes getMoveTimes();
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);
    
    void addToCurrentStep(int step); 
    void updateMotorState(MotorState motorState);

    bool getSunsetMode();
    bool getAutoTime();

    time_t syncFunc();
    void begin();

    MotorCalibrator calibrator;

    
  protected:
   
    bool sunsetMode=true, autoTime=true;
    uint8_t offset=0;

    MoveTimes moveTimes;
    MotorState motorState;

    Motor motor;
    Preferences pref;
    DisplayUI displayUI;

    void saveMoveTimesToMemory();
    void loadMoveTimesFromMemory();
    void saveMotorStateToMemory();
    void loadMotorStateFromMemory();
    
};

#endif